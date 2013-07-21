/*
  PictureFlow - animated image show widget
  http://pictureflow.googlecode.com

  Copyright (C) 2008 Ariya Hidayat (ariya@kde.org)
  Copyright (C) 2007 Ariya Hidayat (ariya@kde.org)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
#include <QProcess>
#include "pictureflow.h"
#include "QDebug"
#include <QFileIconProvider>
#include <QDir>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include <QMutex>
#include <QProgressDialog>
#include <QMessageBox>
#include "paths.h"
// detect Qt version
#if QT_VERSION >= 0x040000
#define PICTUREFLOW_QT4
#elif QT_VERSION >= 0x030000
#define PICTUREFLOW_QT3
#elif QT_VERSION >= 235
#define PICTUREFLOW_QT2
#else
#error PictureFlow widgets need Qt 2, Qt 3 or Qt 4
#endif

#ifdef PICTUREFLOW_QT4
#include <QApplication>
#include <QCache>
#include <QHash>
#include <QImage>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QWidget>
#endif

#ifdef PICTUREFLOW_QT3
#include <qapplication.h>
#include <qcache.h>
#include <qimage.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qdatetime.h>
#include <qtimer.h>
#include <qvaluevector.h>
#include <qwidget.h>

#define qMax(x,y) ((x) > (y)) ? (x) : (y)
#define qMin(x,y) ((x) < (y)) ? (x) : (y)

#define QVector QValueVector

#define toImage convertToImage
#define contains find
#define modifiers state
#define ControlModifier ControlButton
#endif

#ifdef PICTUREFLOW_QT2
#include <qapplication.h>
#include <qarray.h>
#include <qcache.h>
#include <qimage.h>
#include <qintdict.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qdatetime.h>
#include <qtimer.h>
#include <qwidget.h>

#define qMax(x,y) ((x) > (y)) ? (x) : (y)
#define qMin(x,y) ((x) < (y)) ? (x) : (y)

#define QVector QArray

#define toImage convertToImage
#define contains find
#define modifiers state
#define ControlModifier ControlButton
#define flush flushX
#endif
//QString fileTitle;
//QString filePath;
QString strCenter;

// for fixed-point arithmetic, we need minimum 32-bit long
// long long (64-bit) might be useful for multiplication and division
typedef long PFreal;
#define PFREAL_SHIFT 10
#define PFREAL_ONE (1 << PFREAL_SHIFT)

#define IANGLE_MAX 1024
#define IANGLE_MASK 1023

inline PFreal fmul(PFreal a, PFreal b)
{
  return ((long long)(a))*((long long)(b)) >> PFREAL_SHIFT;
}

inline PFreal fdiv(PFreal num, PFreal den)
{
  long long p = (long long)(num) << (PFREAL_SHIFT*2);
  long long q = p / (long long)den;
  long long r = q >> PFREAL_SHIFT;

  return r;
}

inline PFreal fsin(int iangle)
{
  // warning: regenerate the table if IANGLE_MAX and PFREAL_SHIFT are changed!
  static const PFreal tab[] = {
     3,    103,    202,    300,    394,    485,    571,    652,
   726,    793,    853,    904,    947,    980,   1004,   1019,
  1023,   1018,   1003,    978,    944,    901,    849,    789,
   721,    647,    566,    479,    388,    294,    196,     97,
    -4,   -104,   -203,   -301,   -395,   -486,   -572,   -653,
  -727,   -794,   -854,   -905,   -948,   -981,  -1005,  -1020,
 -1024,  -1019,  -1004,   -979,   -945,   -902,   -850,   -790,
  -722,   -648,   -567,   -480,   -389,   -295,   -197,    -98,
  3
  };

  while(iangle < 0)
    iangle += IANGLE_MAX;
  iangle &= IANGLE_MASK;

  int i = (iangle >> 4);
  PFreal p = tab[i];
  PFreal q = tab[(i+1)];
  PFreal g = (q - p);
  return p + g * (iangle-i*16)/16;
}

inline PFreal fcos(int iangle)
{
  return fsin(iangle + (IANGLE_MAX >> 2));
}

/* ----------------------------------------------------------

PictureFlowState stores the state of all slides, i.e. all the necessary
information to be able to render them.

PictureFlowAnimator is responsible to move the slides during the
transition between slides, to achieve the effect similar to Cover Flow,
by changing the state.

PictureFlowSoftwareRenderer (or PictureFlowOpenGLRenderer) is
the actual 3-d renderer. It should render all slides given the state
(an instance of PictureFlowState).

Instances of all the above three classes are stored in
PictureFlowPrivate.

------------------------------------------------------- */

struct SlideInfo
{
  int slideIndex;
  int angle;
  PFreal cx;
  PFreal cy;
  int blend;
};

class PictureFlowState
{
public:
  PictureFlowState();
  ~PictureFlowState();

  void reposition();
  void reset();

  QRgb backgroundColor;
  int slideWidth;
  int slideHeight;
  PictureFlow::ReflectionEffect reflectionEffect;
  QVector<QImage*> slideImages;

  int angle;
  int spacing;
  PFreal offsetX;
  PFreal offsetY;

  SlideInfo centerSlide;
  QVector<SlideInfo> leftSlides;
  QVector<SlideInfo> rightSlides;
  int centerIndex;
};

class PictureFlowAnimator
{
public:
  PictureFlowAnimator();
  PictureFlowState* state;

  void start(int slide);
  void stop(int slide);
  void update();

  int target;
  int step;
  int frame;
  QTimer animateTimer;
};

class PictureFlowAbstractRenderer
{
public:
  PictureFlowAbstractRenderer(): state(0), dirty(false), widget(0) {}
  virtual ~PictureFlowAbstractRenderer() {}

  PictureFlowState* state;
  bool dirty;
  QWidget* widget;
  QString fileTitle;  
  QString filePath;
  QString countstr;
  bool isdrv;
  virtual void init() = 0;
  virtual void paint() = 0;
};

class PictureFlowSoftwareRenderer: public PictureFlowAbstractRenderer
{
public:
  PictureFlowSoftwareRenderer();
  ~PictureFlowSoftwareRenderer();

  virtual void init();
  virtual void paint();

private:

  bool bdrawtext;
  QSize size;
  QRgb bgcolor;
  int effect;
  QImage buffer;
  QVector<PFreal> rays;
  QImage* blankSurface;

#ifdef PICTUREFLOW_QT4
  QCache<int,QImage> surfaceCache;
  QHash<int,QImage*> imageHash;
#endif
#ifdef PICTUREFLOW_QT3
  QCache<QImage> surfaceCache;
  QMap<int,QImage*> imageHash;
#endif
#ifdef PICTUREFLOW_QT2
  QCache<QImage> surfaceCache;
  QIntDict<QImage> imageHash;
#endif

  void render();
  void renderSlides();
  void disableDrawText(){bdrawtext=false;};

  QRect renderSlide(const SlideInfo &slide, int col1 = -1, int col2 = -1);
  QImage* surface(int slideIndex);

};

// ------------- PictureFlowState ---------------------------------------

PictureFlowState::PictureFlowState():
backgroundColor(0), slideWidth(150), slideHeight(200),
reflectionEffect(PictureFlow::BlurredReflection), centerIndex(0)
{
}

PictureFlowState::~PictureFlowState()
{
  for(int i = 0; i < (int)slideImages.count(); i++)
    delete slideImages[i];
}

// readjust the settings, call this when slide dimension is changed
void PictureFlowState::reposition()
{
  angle = 70 * IANGLE_MAX / 360;  // approx. 70 degrees tilted

  offsetX = slideWidth/2 * (PFREAL_ONE-fcos(angle));
  offsetY = slideWidth/2 * fsin(angle);
  offsetX += slideWidth * PFREAL_ONE;
  offsetY += slideWidth * PFREAL_ONE / 4;
  spacing = 40;
}

// adjust slides so that they are in "steady state" position
void PictureFlowState::reset()
{
  centerSlide.angle = 0;
  centerSlide.cx = 0;
  centerSlide.cy = 0;
  centerSlide.slideIndex = centerIndex;
  centerSlide.blend = 256;

  leftSlides.resize(6);
  for(int i = 0; i < (int)leftSlides.count(); i++)
  {
    SlideInfo& si = leftSlides[i];
    si.angle = angle;
    si.cx = -(offsetX + spacing*i*PFREAL_ONE);
    si.cy = offsetY;
    si.slideIndex = centerIndex-1-i;
    si.blend = 256;
    if(i == (int)leftSlides.count()-2)
      si.blend = 128;
    if(i == (int)leftSlides.count()-1)
      si.blend = 0;
  }

  rightSlides.resize(6);
  for(int i = 0; i < (int)rightSlides.count(); i++)
  {
    SlideInfo& si = rightSlides[i];
    si.angle = -angle;
    si.cx = offsetX + spacing*i*PFREAL_ONE;
    si.cy = offsetY;
    si.slideIndex = centerIndex+1+i;
    si.blend = 256;
    if(i == (int)rightSlides.count()-2)
      si.blend = 128;
    if(i == (int)rightSlides.count()-1)
      si.blend = 0;
  }
}

// ------------- PictureFlowAnimator  ---------------------------------------

PictureFlowAnimator::PictureFlowAnimator():
state(0), target(0), step(0), frame(0)
{
}

void PictureFlowAnimator::start(int slide)
{
  target = slide;
  if(!animateTimer.isActive() && state)
  {
    step = (target < state->centerSlide.slideIndex) ? -1 : 1;
    animateTimer.start(10);
  }
}

void PictureFlowAnimator::stop(int slide)
{
  step = 0;
  target = slide;
  frame = slide << 16;
  animateTimer.stop();
}

void PictureFlowAnimator::update()
{
  if(!animateTimer.isActive())
    return;
  if(step == 0)
    return;
  if(!state)
    return;

  int speed = 16384/4;

#if 1
  // deaccelerate when approaching the target
  const int max = 2 * 65536;

  int fi = frame;
  fi -= (target << 16);
  if(fi < 0)
    fi = -fi;
  fi = qMin(fi, max);

  int ia = IANGLE_MAX * (fi-max/2) / (max*2);
  speed = 512 + 16384 * (PFREAL_ONE+fsin(ia))/PFREAL_ONE;
#endif

  frame += speed*step;

  int index = frame >> 16;
  int pos = frame & 0xffff;
  int neg = 65536 - pos;
  int tick = (step < 0) ? neg : pos;
  PFreal ftick = (tick * PFREAL_ONE) >> 16;

  if(step < 0)
    index++;

  if(state->centerIndex != index)
  {
    state->centerIndex = index;
    frame = index << 16;
    state->centerSlide.slideIndex = state->centerIndex;
    for(int i = 0; i < (int)state->leftSlides.count(); i++)
      state->leftSlides[i].slideIndex = state->centerIndex-1-i;
    for(int i = 0; i < (int)state->rightSlides.count(); i++)
      state->rightSlides[i].slideIndex = state->centerIndex+1+i;
  }

  state->centerSlide.angle = (step * tick * state->angle) >> 16;
  state->centerSlide.cx = -step * fmul(state->offsetX, ftick);
  state->centerSlide.cy = fmul(state->offsetY, ftick);

  if(state->centerIndex == target)
  {
    stop(target);
    state->reset();
    return;
  }

  for(int i = 0; i < (int)state->leftSlides.count(); i++)
  {
    SlideInfo& si = state->leftSlides[i];
    si.angle = state->angle;
    si.cx = -(state->offsetX + state->spacing*i*PFREAL_ONE + step*state->spacing*ftick);
    si.cy = state->offsetY;
  }

  for(int i = 0; i < (int)state->rightSlides.count(); i++)
  {
    SlideInfo& si = state->rightSlides[i];
    si.angle = -state->angle;
    si.cx = state->offsetX + state->spacing*i*PFREAL_ONE - step*state->spacing*ftick;
    si.cy = state->offsetY;
  }

  if(step > 0)
  {
    PFreal ftick = (neg * PFREAL_ONE) >> 16;
    state->rightSlides[0].angle = -(neg * state->angle) >> 16;
    state->rightSlides[0].cx = fmul(state->offsetX, ftick);
    state->rightSlides[0].cy = fmul(state->offsetY, ftick);
  }
  else
  {
    PFreal ftick = (pos * PFREAL_ONE) >> 16;
    state->leftSlides[0].angle = (pos * state->angle) >> 16;
    state->leftSlides[0].cx = -fmul(state->offsetX, ftick);
    state->leftSlides[0].cy = fmul(state->offsetY, ftick);
  }

  // must change direction ?
  if(target < index) if(step > 0)
    step = -1;
  if(target > index) if(step < 0)
    step = 1;

  // the first and last slide must fade in/fade out
  int nleft = state->leftSlides.count();
  int nright = state->rightSlides.count();
  int fade = pos / 256;

  for(int index = 0; index < nleft; index++)
  {
    int blend = 256;
    if(index == nleft-1)
      blend = (step > 0) ? 0 : 128-fade/2;
    if(index == nleft-2)
      blend = (step > 0) ? 128-fade/2 : 256-fade/2;
    if(index == nleft-3)
      blend = (step > 0) ? 256-fade/2 : 256;
    state->leftSlides[index].blend = blend;
  }
  for(int index = 0; index < nright; index++)
  {
    int blend = (index < nright-2) ? 256 : 128;
    if(index == nright-1)
      blend = (step > 0) ? fade/2 : 0;
    if(index == nright-2)
      blend = (step > 0) ? 128+fade/2 : fade/2;
    if(index == nright-3)
      blend = (step > 0) ? 256 : 128+fade/2;
    state->rightSlides[index].blend = blend;
  }

}

// ------------- PictureFlowSoftwareRenderer ---------------------------------------

PictureFlowSoftwareRenderer::PictureFlowSoftwareRenderer():
PictureFlowAbstractRenderer(), size(0,0), bgcolor(0), effect(-1), blankSurface(0)
{bdrawtext=true;
    countstr="";
#ifdef PICTUREFLOW_QT3
  surfaceCache.setAutoDelete(true);
#endif
}

PictureFlowSoftwareRenderer::~PictureFlowSoftwareRenderer()
{
  surfaceCache.clear();
  buffer = QImage();
  delete blankSurface;
}

void PictureFlowSoftwareRenderer::paint()
{
  if(!widget)
    return;

  if(widget->size() != size)
    init();

  if(state->backgroundColor != bgcolor)
  {
    bgcolor = state->backgroundColor;
    surfaceCache.clear();
  }

  if((int)(state->reflectionEffect) != effect)
  {
    effect = (int)state->reflectionEffect;
    surfaceCache.clear();
  }

  if(dirty)
    render();

  QPainter painter(this->widget);
  painter.setRenderHints(QPainter::NonCosmeticDefaultPen|QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);
  painter.drawImage(QPoint(0,0), buffer);
  painter.setPen(Qt::white);
if (fileTitle.isEmpty())
  { fileTitle=filePath;
  }
   else
  { //qDebug()<<"paint"<<filePath;
       QFileInfoList list = QDir::drives();

       if (!isdrv)
       {painter.setFont(QFont(painter.font().family(), 10, QFont::Normal));
        int notesWidth = painter.fontMetrics().width(filePath+countstr);
        painter.drawText((size.width()- notesWidth) /2, size.height()*0.70+ painter.fontMetrics().height()+2,filePath +countstr);

       }
     else
       {filePath="";
         painter.setFont(QFont(painter.font().family(), 10, QFont::Normal));
         int notesWidth = painter.fontMetrics().width(filePath);
         painter.drawText((size.width()- notesWidth) /2, size.height()*0.70+ painter.fontMetrics().height()+2,filePath );
       }
 }
   painter.setFont(QFont(painter.font().family(), 10, QFont::Bold));
   int titleWidth = painter.fontMetrics().width(fileTitle);
  //if(!_showpic)
     painter.drawText((size.width()-titleWidth) /2,size.height()*0.17,fileTitle);


    painter.setFont(QFont("Arial", 10));
    painter.drawText(widget->rect(), Qt::AlignCenter, strCenter);

}

void PictureFlowSoftwareRenderer::init()
{
  if(!widget)
    return;

  surfaceCache.clear();
  blankSurface = 0;

  size = widget->size();
  int ww = size.width();
  int wh = size.height();
  int w = (ww+1)/2;
  int h = (wh+1)/2;

#ifdef PICTUREFLOW_QT4
  buffer = QImage(ww, wh, QImage::Format_RGB32);
#endif
#if defined(PICTUREFLOW_QT3) || defined(PICTUREFLOW_QT2)
  buffer.create(ww, wh, 32);
#endif
  buffer.fill(bgcolor);

  rays.resize(w*2);
  for(int i = 0; i < w; i++)
  {
    PFreal gg = ((PFREAL_ONE >> 1) + i * PFREAL_ONE) / (2*h);
    rays[w-i-1] = -gg;
    rays[w+i] = gg;
  }

  dirty = true;
}

// TODO: optimize this with lookup tables
static QRgb blendColor(QRgb c1, QRgb c2, int blend)
{
  int r = qRed(c1) * blend/256 + qRed(c2)*(256-blend)/256;
  int g = qGreen(c1) * blend/256 + qGreen(c2)*(256-blend)/256;
  int b = qBlue(c1) * blend/256 + qBlue(c2)*(256-blend)/256;
  return qRgb(r, g, b);
}


static QImage* prepareSurface(const QImage* slideImage, int w, int h, QRgb bgcolor,
PictureFlow::ReflectionEffect reflectionEffect)
{
#ifdef PICTUREFLOW_QT4
  Qt::TransformationMode mode = Qt::SmoothTransformation;
  QImage img = slideImage->scaled(w, h, Qt::IgnoreAspectRatio, mode);
#endif
#if defined(PICTUREFLOW_QT3) || defined(PICTUREFLOW_QT2)
  QImage img = slideImage->smoothScale(w, h);
#endif

  // slightly larger, to accomodate for the reflection
  int hs = h * 2;
  int hofs = h / 3;

  // offscreen buffer: black is sweet
#ifdef PICTUREFLOW_QT4
  QImage* result = new QImage(hs, w, QImage::Format_RGB32);
#endif
#if defined(PICTUREFLOW_QT3) || defined(PICTUREFLOW_QT2)
  QImage* result = new QImage;
  result->create(hs, w, 32);
#endif
  result->fill(bgcolor);

  // transpose the image, this is to speed-up the rendering
  // because we process one column at a time
  // (and much better and faster to work row-wise, i.e in one scanline)
  for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
      result->setPixel(hofs + y, x, img.pixel(x, y));

  if(reflectionEffect != PictureFlow::NoReflection)
  {
    // create the reflection
    int ht = hs - h - hofs;
    int hte = ht;
    for(int x = 0; x < w; x++)
      for(int y = 0; y < ht; y++)
      {
        QRgb color = img.pixel(x, img.height()-y-1);
        result->setPixel(h+hofs+y, x, blendColor(color,bgcolor,128*(hte-y)/hte));
      }

    if(reflectionEffect == PictureFlow::BlurredReflection)
    {
      // blur the reflection everything first
      // Based on exponential blur algorithm by Jani Huhtanen
      QRect rect(hs/2, 0, hs/2, w);
      rect &= result->rect();

      int r1 = rect.top();
      int r2 = rect.bottom();
      int c1 = rect.left();
      int c2 = rect.right();

      int bpl = result->bytesPerLine();
      int rgba[4];
      unsigned char* p;

      // how many times blur is applied?
      // for low-end system, limit this to only 1 loop
      for(int loop = 0; loop < 2; loop++)
      {
        for(int col = c1; col <= c2; col++)
        {
          p = result->scanLine(r1) + col*4;
          for(int i = 0; i < 3; i++)
            rgba[i] = p[i] << 4;

          p += bpl;
          for(int j = r1; j < r2; j++, p += bpl)
            for(int i = 0; i < 3; i++)
              p[i] = (rgba[i] += (((p[i]<<4)-rgba[i])) >> 1) >> 4;
        }

        for(int row = r1; row <= r2; row++)
        {
          p = result->scanLine(row) + c1*4;
          for(int i = 0; i < 3; i++)
            rgba[i] = p[i] << 4;

          p += 4;
          for(int j = c1; j < c2; j++, p+=4)
            for(int i = 0; i < 3; i++)
              p[i] = (rgba[i] += (((p[i]<<4)-rgba[i])) >> 1) >> 4;
        }

        for(int col = c1; col <= c2; col++)
        {
          p = result->scanLine(r2) + col*4;
          for(int i = 0; i < 3; i++)
            rgba[i] = p[i] << 4;

          p -= bpl;
          for(int j = r1; j < r2; j++, p -= bpl)
            for(int i = 0; i < 3; i++)
              p[i] = (rgba[i] += (((p[i]<<4)-rgba[i])) >> 1) >> 4;
        }

        for(int row = r1; row <= r2; row++)
        {
          p = result->scanLine(row) + c2*4;
          for(int i = 0; i < 3; i++)
            rgba[i] = p[i] << 4;

          p -= 4;
          for(int j = c1; j < c2; j++, p-=4)
            for(int i = 0; i < 3; i++)
              p[i] = (rgba[i] += (((p[i]<<4)-rgba[i])) >> 1) >> 4;
        }
      }

      // overdraw to leave only the reflection blurred (but not the actual image)
      for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++)
          result->setPixel(hofs + y, x, img.pixel(x, y));
    }
  }

  return result;
}

QImage* PictureFlowSoftwareRenderer::surface(int slideIndex)
{
  if(!state)
    return 0;
  if(slideIndex < 0)
    return 0;
  if(slideIndex >= (int)state->slideImages.count())
    return 0;

#ifdef PICTUREFLOW_QT4
  int key = slideIndex;
#endif
#if defined(PICTUREFLOW_QT3) || defined(PICTUREFLOW_QT2)
  QString key = QString::number(slideIndex);
#endif

  QImage* img = state->slideImages.at(slideIndex);
  bool empty = img ? img->isNull() : true;
  if(empty)
  {
    surfaceCache.remove(key);
    imageHash.remove(slideIndex);
    if(!blankSurface)
    {
      int sw = state->slideWidth;
      int sh = state->slideHeight;

#ifdef PICTUREFLOW_QT4
      QImage img = QImage(sw, sh, QImage::Format_RGB32);

      QPainter painter(&img);
      QPoint p1(sw*4/10, 0);
      QPoint p2(sw*6/10, sh);
      QLinearGradient linearGrad(p1, p2);
      linearGrad.setColorAt(0, Qt::black);
      linearGrad.setColorAt(1, Qt::white);
      painter.setBrush(linearGrad);
      painter.fillRect(0, 0, sw, sh, QBrush(linearGrad));

      painter.setPen(QPen(QColor(64,64,64), 4));
      painter.setBrush(QBrush());
      painter.drawRect(2, 2, sw-3, sh-3);
      painter.end();
#endif
#if defined(PICTUREFLOW_QT3) || defined(PICTUREFLOW_QT2)
      QPixmap pixmap(sw, sh, 32);
      QPainter painter(&pixmap);
      painter.fillRect(pixmap.rect(), QColor(192,192,192));
      painter.fillRect(5, 5, sw-10, sh-10, QColor(64,64,64));
      painter.end();
      QImage img = pixmap.convertToImage();
#endif

      blankSurface = prepareSurface(&img, sw, sh, bgcolor, state->reflectionEffect);
    }
    return blankSurface;
  }

#ifdef PICTUREFLOW_QT4
  bool exist = imageHash.contains(slideIndex);
  if(exist)
  if(img == imageHash.find(slideIndex).value())
#endif
#ifdef PICTUREFLOW_QT3
  bool exist = imageHash.find(slideIndex) != imageHash.end();
  if(exist)
  if(img == imageHash.find(slideIndex).data())
#endif
#ifdef PICTUREFLOW_QT2
  if(img == imageHash[slideIndex])
#endif
    if(surfaceCache.contains(key))
        return surfaceCache[key];

  QImage* sr = prepareSurface(img, state->slideWidth, state->slideHeight, bgcolor, state->reflectionEffect);
  surfaceCache.insert(key, sr);
  imageHash.insert(slideIndex, img);

  return sr;
}

// Renders a slide to offscreen buffer. Returns a rect of the rendered area.
// col1 and col2 limit the column for rendering.
QRect PictureFlowSoftwareRenderer::renderSlide(const SlideInfo &slide, int col1, int col2)
{
  int blend = slide.blend;
  if(!blend)
    return QRect();

  QImage* src = surface(slide.slideIndex);
  if(!src)
    return QRect();

  QRect rect(0, 0, 0, 0);

  int sw = src->height();
  int sh = src->width();
  int h = buffer.height();
  int w = buffer.width();

  if(col1 > col2)
  {
    int c = col2;
    col2 = col1;
    col1 = c;
  }

  col1 = (col1 >= 0) ? col1 : 0;
  col2 = (col2 >= 0) ? col2 : w-1;
  col1 = qMin(col1, w-1);
  col2 = qMin(col2, w-1);

  int zoom = 100;
  int distance = h * 100 / zoom;
  PFreal sdx = fcos(slide.angle);
  PFreal sdy = fsin(slide.angle);
  PFreal xs = slide.cx - state->slideWidth * sdx/2;
  PFreal ys = slide.cy - state->slideWidth * sdy/2;
  PFreal dist = distance * PFREAL_ONE;

  int xi = qMax((PFreal)0, (w*PFREAL_ONE/2) + fdiv(xs*h, dist+ys) >> PFREAL_SHIFT);
  if(xi >= w)
    return rect;

  bool flag = false;
  rect.setLeft(xi);
  for(int x = qMax(xi, col1); x <= col2; x++)
  {
    PFreal hity = 0;
    PFreal fk = rays[x];
    if(sdy)
    {
      fk = fk - fdiv(sdx,sdy);
      hity = -fdiv((rays[x]*distance - slide.cx + slide.cy*sdx/sdy), fk);
    }

    dist = distance*PFREAL_ONE + hity;
    if(dist < 0)
      continue;

    PFreal hitx = fmul(dist, rays[x]);
    PFreal hitdist = fdiv(hitx - slide.cx, sdx);

    int column = sw/2 + (hitdist >> PFREAL_SHIFT);
    if(column >= sw)
      break;
    if(column < 0)
      continue;

    rect.setRight(x);
    if(!flag)
      rect.setLeft(x);
    flag = true;

    int y1 = h/2;
    int y2 = y1+ 1;
    QRgb* pixel1 = (QRgb*)(buffer.scanLine(y1)) + x;
    QRgb* pixel2 = (QRgb*)(buffer.scanLine(y2)) + x;
    QRgb pixelstep = pixel2 - pixel1;

    int center = (sh/2);
    int dy = dist / h;
    int p1 = center*PFREAL_ONE - dy/2;
    int p2 = center*PFREAL_ONE + dy/2;

    const QRgb *ptr = (const QRgb*)(src->scanLine(column));
    if(blend == 256)
      while((y1 >= 0) && (y2 < h) && (p1 >= 0))
      {
        *pixel1 = ptr[p1 >> PFREAL_SHIFT];
        *pixel2 = ptr[p2 >> PFREAL_SHIFT];
        p1 -= dy;
        p2 += dy;
        y1--;
        y2++;
        pixel1 -= pixelstep;
        pixel2 += pixelstep;
      }
    else
      while((y1 >= 0) && (y2 < h) && (p1 >= 0))
      {
        QRgb c1 = ptr[p1 >> PFREAL_SHIFT];
        QRgb c2 = ptr[p2 >> PFREAL_SHIFT];
        *pixel1 = blendColor(c1, bgcolor, blend);
        *pixel2 = blendColor(c2, bgcolor, blend);
        p1 -= dy;
        p2 += dy;
        y1--;
        y2++;
        pixel1 -= pixelstep;
        pixel2 += pixelstep;
     }
   }

   rect.setTop(0);
   rect.setBottom(h-1);
   return rect;
}

void PictureFlowSoftwareRenderer::renderSlides()
{
  int nleft = state->leftSlides.count();
  int nright = state->rightSlides.count();

  QRect r = renderSlide(state->centerSlide);
  int c1 = r.left();
  int c2 = r.right();

  for(int index = 0; index < nleft; index++)
  {
    QRect rs = renderSlide(state->leftSlides[index], 0, c1-1);
    if(!rs.isEmpty())
      c1 = rs.left();
  }
  for(int index = 0; index < nright; index++)
  {
    QRect rs = renderSlide(state->rightSlides[index], c2+1, buffer.width());
    if(!rs.isEmpty())
      c2 = rs.right();
  }
}

// Render the slides. Updates only the offscreen buffer.
void PictureFlowSoftwareRenderer::render()
{
  buffer.fill(state->backgroundColor);
  renderSlides();
  dirty = false;
}

// -----------------------------------------

class PictureFlowPrivate
{
public:
  PictureFlowState* state;
  PictureFlowAnimator* animator;
  PictureFlowAbstractRenderer* renderer;
  QPoint lastgrabpos;
  QTimer triggerTimer;
};


PictureFlow::PictureFlow(QWidget* parent): QWidget(parent)
{piccount=0;
lock=false;
  _showpic=false;
 encount=false;
  btnBack=new QPushButton("" ,this);
  btnBack->resize(32,32);
   btnBack->setToolTip(tr("Back"));
    btnBack->setVisible(false);
  btnBack->setStyleSheet("QPushButton {\n"
      "border-image: url(:/images/back.png) 3 10 3 10;\n"
      "border-top: 3px transparent;\n"
     "border-bottom: 3px transparent;\n"
      "border-right: 10px transparent;\n"
      "border-left: 10px transparent;\n"
  "}\n"
  "QPushButton::disabled {\n"
        "border-image: url(:/images/back_disable.png) 3 10 3 10;\n"
       " border-top: 3px transparent;\n"
        "border-bottom: 3px transparent;\n"
        "border-right: 10px transparent;\n"
       "border-left: 10px transparent;}\n"
"QPushButton::hover {\n"
      "border-image: url(:/images/back_hover.png) 3 10 3 10;\n"
     " border-top: 3px transparent;\n"
      "border-bottom: 3px transparent;\n"
      "border-right: 10px transparent;\n"
     "border-left: 10px transparent;}\n"
     "QPushButton:pressed {\n"
      "border-image: url(:/images/back_press.png)3 5 3 5;\n"
      "border-top: 3px transparent;\n"
      "border-bottom: 3px transparent;\n"
      "border-right: 5px transparent;\n"
     "border-left: 5px transparent;}");

  if(!_showpic)
  {
  QObject::connect(btnBack,SIGNAL(clicked()),this,SLOT(back()));
  QObject::connect(btnBack,SIGNAL(pressed()),this,SLOT(backpress()));
  QObject::connect(btnBack,SIGNAL(released()),this,SLOT(backrelease()));

  QFile file(Paths::configPath()+"/fmts");
  if (!QFile(Paths::configPath()+ "/fmts").exists())
 {
      qDebug()<<"Initializing formats.....FAILED";
  }
  file.open(QIODevice::ReadOnly);
  QTextStream stream(&file);
   QString line;
   do {line = stream.readLine();
       if (line.contains("."))
       {filters<<QString("*"+line);
       }

   } while (!line.isNull());
   file.close();
   //filters.clear();

  }


  d = new PictureFlowPrivate;
  d->state = new PictureFlowState;
  d->state->reset();
  d->state->reposition();

  d->renderer = new PictureFlowSoftwareRenderer;

  d->renderer->state = d->state;
  d->renderer->widget = this;
  d->renderer->init();
  d->animator = new PictureFlowAnimator;
  d->animator->state = d->state;
  stopAdd=false;

  QObject::connect(&d->animator->animateTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));

  QObject::connect(&d->triggerTimer, SIGNAL(timeout()), this, SLOT(render()));

#ifdef PICTUREFLOW_QT4
  setAttribute(Qt::WA_StaticContents, true);
  setAttribute(Qt::WA_OpaquePaintEvent, true);
  setAttribute(Qt::WA_NoSystemBackground, true);
#endif
#ifdef PICTUREFLOW_QT3
  setWFlags(getWFlags() | Qt::WStaticContents);
  setWFlags(getWFlags() | Qt::WNoAutoErase);
#endif
#ifdef PICTUREFLOW_QT2
  setWFlags(getWFlags() | Qt::WPaintClever);
  setWFlags(getWFlags() | Qt::WRepaintNoErase);
  setWFlags(getWFlags() | Qt::WResizeNoErase);
#endif
}

PictureFlow::~PictureFlow()
{
  delete d->renderer;
  delete d->animator;
  delete d->state;
  delete d;

}

int PictureFlow::slideCount() const
{
  return d->state->slideImages.count();
}

QColor PictureFlow::backgroundColor() const
{
  return QColor(d->state->backgroundColor);
}

void PictureFlow::setBackgroundColor(const QColor& c)
{
  d->state->backgroundColor = c.rgb();
  triggerRender();
}

QSize PictureFlow::slideSize() const
{
  return QSize(d->state->slideWidth, d->state->slideHeight);
}

void PictureFlow::setSlideSize(QSize size)
{
  d->state->slideWidth = size.width();
  d->state->slideHeight = size.height();
  d->state->reposition();
  triggerRender();
}

PictureFlow::ReflectionEffect PictureFlow::reflectionEffect() const
{
  return d->state->reflectionEffect;
}

void PictureFlow::setReflectionEffect(ReflectionEffect effect)
{
  d->state->reflectionEffect = effect;
  triggerRender();
}

QImage PictureFlow::slide(int index) const
{
  QImage* i = 0;
  if((index >= 0) && (index < slideCount()))
    i = d->state->slideImages[index];
  return i ? QImage(*i) : QImage();
}

void PictureFlow::addSlide(const QImage& image)
{
  int c = d->state->slideImages.count();
  d->state->slideImages.resize(c+1);
  d->state->slideImages[c] = new QImage(image);
  triggerRender();
}

void PictureFlow::addSlide(const QPixmap& pixmap)
{
  addSlide(pixmap.toImage());
}

void PictureFlow::setSlide(int index, const QImage& image)
{
  if((index >= 0) && (index < slideCount()))
  {
    QImage* i = image.isNull() ? 0 : new QImage(image);
    delete d->state->slideImages[index];
    d->state->slideImages[index] = i;
    triggerRender();
  }
}

void PictureFlow::setSlide(int index, const QPixmap& pixmap)
{
  setSlide(index, pixmap.toImage());
}

int PictureFlow::centerIndex() const
{
  return d->state->centerIndex;
}

void PictureFlow::setCenterIndex(int index)
{
  index = qMin(index, slideCount()-1);
  index = qMax(index, 0);
  d->state->centerIndex = index;
  d->state->reset();
  d->animator->stop(index);
  triggerRender();
}

void PictureFlow::clear()
{d->state->centerIndex=0;
  int c = d->state->slideImages.count();
  for(int i = 0; i < c; i++)
    delete d->state->slideImages[i];
  d->state->slideImages.resize(0);

  d->state->reset();
  triggerRender();
}

void PictureFlow::render()
{
  d->renderer->dirty = true;
  update();
}

void PictureFlow::triggerRender()
{
#ifdef PICTUREFLOW_QT4

  d->triggerTimer.setSingleShot(true);
  d->triggerTimer.start(0);

#endif
#if defined(PICTUREFLOW_QT3) || defined(PICTUREFLOW_QT2)
  d->triggerTimer.start(0, true);
#endif
}

void PictureFlow::showPrevious()
{
  int step = d->animator->step;
  int center = d->state->centerIndex;

  if(step > 0)
    d->animator->start(center);

  if(step == 0)
    if(center > 0)
      d->animator->start(center - 1);

  if(step < 0)
    d->animator->target = qMax(0, center - 2);
}

void PictureFlow::showNext()
{
  int step = d->animator->step;
  int center = d->state->centerIndex;
  //qDebug()<<"cent:"<<center;
  if(step < 0)
    d->animator->start(center);

  if(step == 0)
    if(center < slideCount()-1)
      d->animator->start(center + 1);

  if(step > 0)
    d->animator->target = qMin(center + 2, slideCount()-1);
}

void PictureFlow::showSlide(int index)
{
  index = qMax(index, 0);
  index = qMin(slideCount()-1, index);
  if(index == d->state->centerSlide.slideIndex)
    return;

  d->animator->start(index);
}

void PictureFlow::keyPressEvent(QKeyEvent* event)
{
  if(event->key() == Qt::Key_Left)
  {
    if(event->modifiers() == Qt::ControlModifier)
      showSlide(centerIndex()-10);
    else
      showPrevious();
    event->accept();
    return;
  }
  if(event->key() == Qt::Key_Down)
  {if (strCenter.isEmpty())
     if(filelist.at(d->state->centerIndex).isDir())
      {
        this->addFolderContents();
        if (d->state->slideImages.count()>2)
         { setCenterIndex(1);
           showSlide(0);
          }
       }
     
     return;

  }
  if(event->key() == Qt::Key_Up|event->key() == Qt::Key_Back)
  {  strCenter="";
      if(backlist.count()>1)
      {
       this->addFolder(backlist.last());
       if (previousCenterIndex.count()>0)
             setCenterIndex( QString(previousCenterIndex.last()).toLong()-1);

       showSlide( QString(previousCenterIndex.last()).toLong());
       previousCenterIndex.removeLast();
       backlist.removeLast();

      return;
      }
      else if(backlist.count()==1)
      {
        this->addDrives();
        if (previousCenterIndex.count()>0)
              setCenterIndex( QString(previousCenterIndex.last()).toLong()-1);

         showSlide( QString(previousCenterIndex.last()).toLong());
        previousCenterIndex.removeLast();
        backlist.removeLast();
      }
  }
  if(event->key() == Qt::Key_Right)
  {
    if(event->modifiers() == Qt::ControlModifier)
      showSlide(centerIndex()+10);
    else
      showNext();
    event->accept();
    return;
  }

  event->ignore();
}

void PictureFlow::mousePressEvent(QMouseEvent* event)
{//QMutex mutex;
    if(event->button()==Qt::LeftButton)
    {  d->lastgrabpos = event->pos();
     if (event->x()  <(width()/2+(d->state->slideWidth/2)) && event->x() >(width()/2-(d->state->slideWidth/2)))
     {if (event->y()  <(height()/2+(d->state->slideHeight/2)) && event->y() >(height()/2-(d->state->slideHeight/2)))
         {   //mutex.lock();

             addFolderContents();

           // mutex.unlock();
        }
      //You've Clicked on the Central Item
     // qDebug("Central Item Clicked index %d  ",d->state->centerIndex);
     }
  //else if(event->x() > (width()/2+d->state->slideWidth/2))
   //  showNext();
  else
    //showPrevious();
      d->lastgrabpos = event->pos();
}

}
void PictureFlow:: addDrives()
 {  this->btnBack->setEnabled(false);
    lock=true;
    btnBack->setVisible(true);

    clear();
    filelist.clear();
    //PictureFlow();
    //init();
    QDir dir;
    QFileInfoList list = QDir::drives();
    QFileIconProvider ip;
    filelist=list;
    QMutex mutex;
     mutex.lock();
    for (int i = 0; i < list.size(); ++i)
    {
      QFileInfo fileInfo = list.at(i);

      QIcon ic=ip.icon(fileInfo);
      //addSlide( ic.pixmap(48,48,QIcon::Active,QIcon::On));
      d->renderer->fileTitle= list.at(0).absoluteFilePath();
     // d->renderer->filePath=list.at(0).absoluteFilePath();
      d->renderer->isdrv=true;
      addSlide(QIcon(":/images/drive.png").pixmap(128,128,QIcon::Normal,QIcon::On));
     
    }
   mutex.unlock();
  lock=false;
 }
void PictureFlow::addFolder(QString path )
{
    this->btnBack->setEnabled(true);
    d->renderer->isdrv=false;
 QDir dir;
 dir = QDir(qApp->applicationDirPath()+"/covers");
 dir.setFilter(QDir::Hidden|QDir::Files|QDir::AllDirs | QDir::NoSymLinks | QDir::Readable|QDir::NoDotAndDotDot);

 QFileInfoList list = dir.entryInfoList();
 if (list.count())
 {
     for (int i=0;i<list.count();i++)
     {
      dir.remove(list.at(i).filePath());
     }
 }
    clear();
    filelist.clear();
    PictureFlow();

    dir.mkdir(qApp->applicationDirPath()+"/covers");
    filelist.clear();
    dir = QDir();
    dir.setSorting(QDir::Name);
    stopAdd=false;
    //qDebug()<<stopAdd;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(stopAdding()));
    timer->start(10);

 if(!path.isEmpty())
    {dir = QDir(path);

    dir.setFilter(QDir::Hidden|QDir::Files|QDir::AllDirs | QDir::NoSymLinks | QDir::Readable|QDir::NoDotAndDotDot);


    dir.setNameFilters(filters);
    QFileInfoList list = dir.entryInfoList();

    //qDebug()<<"No of files:"<<list.count();
    filelist=list;
    QFileIconProvider ip;
    clear();
if (list.count()==0)
    strCenter="No media file";
else
{ for (int i = 0; i < list.size(); ++i)
    {  //qDebug()<<stopAdd;
        if (stopAdd)
        { stopAdd=false;
            break;
        }

      QFileInfo fileInfo = list.at(i);
      QIcon ic=ip.icon(fileInfo);

      d->renderer->fileTitle=QString("Please Wait...(%1)%").arg((double)(i+1)/list.size()*100,0,'g',2);
      d->renderer->filePath=list.at(i).filePath();


    // paint();
      if( i+1==list.size())
      {
          d->renderer->fileTitle=list.at(0).fileName();

      }

       this->repaint();

      if (list.at(i).isDir())
      {
          addSlide( QIcon(":/images/folder.png").pixmap(128,128,QIcon::Normal,QIcon::On));
          //addSlide( ic.pixmap(48,48,QIcon::Active,QIcon::On));

      }
       else if (list.at(i).fileName().endsWith(".mp2",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".mp3",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".mpc",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".flac",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".wav",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".wave",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".a52",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".m4a",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".snd",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".mka",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".ac3",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".aac",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".aiff",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".aifc",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".ape",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".mpa",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".oga",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".ra",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".ra",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".wma",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".wa",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".ogg",Qt::CaseInsensitive)|
                list.at(i).fileName().endsWith(".amr",Qt::CaseInsensitive))

      {    //QImage img;
           //img.load(list.at(i).filePath());
           //setSlideSize(QSize(128,128));
           // addSlide(QPixmap(list.at(i).filePath(),0,Qt::AutoColor ));
           addSlide(QPixmap(":/images/audiofile.png"));
       }
       else
       {//addSlide(ic.pixmap(32,32,QIcon::Normal,QIcon::Off));
         QProcess *myProcess=new QProcess(this);
         myProcess->start("\""+qApp->applicationDirPath()+"/ffmpeg.exe\" -i "+"\""+shortPathName(d->renderer->filePath)+"\""+" -vframes 1 -r 1 -s 96x54 -f image2 "+ "\""+qApp->applicationDirPath()+ "/covers/cover"+QString::number(i)+".jpeg""\"");
         addSlide(QPixmap(":/images/videofile.png"));

       }


      if (list.count()==1)
      {
          d->renderer->filePath=list.at(0).filePath();
       d->renderer->fileTitle=list.at(0).baseName();
   if(list.at(0).isFile())
       {if(QString(qApp->applicationDirPath()+"/covers/cover"+QString::number(d->state->centerIndex)+".jpeg").contains(QString::number(0)))
          {//QString::number(d->state->centerIndex)
           if (QPixmap(qApp->applicationDirPath()+"/covers/cover0.jpeg").width()>0)
           {d->state->slideImages[d->state->centerIndex] = new QImage(QPixmap(qApp->applicationDirPath()+"/covers/cover0.jpeg").toImage());

               triggerRender();
           }
         //else
            //addSlide(QPixmap(":/images/videofile.png"));
          }
       }
else
       {setCenterIndex(0);
        showSlide(0) ;
    // addSlide( QIcon(":/folder_2").pixmap(128,128,QIcon::Normal,QIcon::On));

       }
      }
     }
}

}
 if (d->state->slideImages.count()>1)
 {setCenterIndex(1);
      showSlide(0) ;
  }



}

void PictureFlow::paintEvent(QPaintEvent* event)
{
    d->renderer->paint();

}

void PictureFlow::resizeEvent(QResizeEvent* event)
{
   // d->state->slideWidth = event->size().width()*.2;
   // d->state->slideHeight =event->size().height()/2.2;
    //d->state->reposition();
    btnBack->move(20,(event->size().height()/2)-20);
    triggerRender();


}

void PictureFlow::updateAnimation()
{
  int old_center = d->state->centerIndex;
  d->animator->update();
  triggerRender();
  d->renderer->filePath=filelist.at(d->state->centerIndex).filePath();
d->renderer->countstr=" ["+QString::number(d->state->centerIndex+1)+"/"+QString::number(d->state->slideImages.count())+"]";
  if (filelist.at(d->state->centerIndex).isDir()||filelist.at(d->state->centerIndex).isFile())
    d->renderer->fileTitle=filelist.at(d->state->centerIndex).completeBaseName();
  else
    d->renderer->fileTitle=filelist.at(d->state->centerIndex).filePath();

  if(filelist.at(d->state->centerIndex).isFile())
  { d->renderer->fileTitle=d->renderer->fileTitle+" ("+d->renderer->filePath.right(d->renderer->filePath.length()-d->renderer->filePath.lastIndexOf(".")-1) +")";
      if (d->renderer->filePath.endsWith(".mp2",Qt::CaseInsensitive)|
              d->renderer->filePath.endsWith(".mp3",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".mpc",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".flac",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".wav",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".wave",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".a52",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".m4a",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".snd",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".mka",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".ac3",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".aac",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".aiff",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".aifc",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".ape",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".mpa",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".oga",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".ra",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".rm",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".wma",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".wa",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".ogg",Qt::CaseInsensitive)|
                      d->renderer->filePath.endsWith(".amr",Qt::CaseInsensitive))
            {
         }
         else
      { //QString::number(d->state->centerIndex)
             QImage g;
             if (_showpic)
             {  g.load(qApp->applicationDirPath()+"/pictures/cover"+QString::number(d->state->centerIndex)+".jpeg",0);
                if (g.width()>0)
                {d->state->slideImages[d->state->centerIndex] = new QImage(qApp->applicationDirPath()+"/pictures/cover"+QString::number(d->state->centerIndex)+".jpeg",0);
              triggerRender();
                }
              }
             else
             {
                 g.load(qApp->applicationDirPath()+"/covers/cover"+QString::number(d->state->centerIndex)+".jpeg",0);
               if (g.width()>0)
                 {d->state->slideImages[d->state->centerIndex] = new QImage(qApp->applicationDirPath()+"/covers/cover"+QString::number(d->state->centerIndex)+".jpeg",0);
                  triggerRender();
                 }
             }
          }
        }




  if(d->state->centerIndex != old_center)
    emit centerIndexChanged(d->state->centerIndex);
}


void PictureFlow::wheelEvent ( QWheelEvent * event )
{if (event->delta()>0)
     showNext();
 else
    showPrevious();


}

void PictureFlow::addFolderContents()
{lock=true;
    d->renderer->isdrv=false;
    if (d->state->slideImages.count()>0)
    { if (filelist.at(d->state->centerIndex).isDir())
    {
      backlist<<filelist.at(d->state->centerIndex).canonicalPath();
      previousCenterIndex<<QString::number(d->state->centerIndex);
      addFolder(filelist.at(d->state->centerIndex).filePath());
    }
    else
    {//emit filename(filelist.at(d->state->centerIndex).filePath());
    }

   }
 //mutex.unlock();
  lock=false;
}
void PictureFlow::stopAdding()
{

    timer->stop();
     stopAdd=true;
 }
void PictureFlow::mouseDoubleClickEvent ( QMouseEvent * event )
{
   if (_showpic)
    { qDebug()<<"click";
        emit dblclick();

   }
   else
   {if (d->state->slideImages.count()>0)
    {if (!lock)
     {if(filelist.at(d->state->centerIndex).isFile())
     emit filename(filelist.at(d->state->centerIndex).filePath());
     emit play();
       }
    }
   }

}
void PictureFlow::contextMenuEvent(QContextMenuEvent *event)
{
  if (_showpic)
    { emit  showctxmenu(event);
    }

    if (!_showpic)
    {  QMenu rmenu;
if (d->state->slideImages.count())
    { if (!filelist.at(d->state->centerIndex).baseName().isEmpty())
{QAction *addAct=rmenu.addAction("Add "+filelist.at(d->state->centerIndex).baseName()+" to playlist");
 QObject::connect(addAct,SIGNAL(triggered()), this, SLOT(addcontentstoplaylist()));
 rmenu.exec(event->globalPos());
} //filename(filelist.at(d->state->centerIndex).filePath());
}
}
}
 void PictureFlow::back()
 {if (!_showpic)
     {
     PictureFlow();
 }
     QDir dir;
     dir = QDir(qApp->applicationDirPath()+"/covers");

  dir.setFilter(QDir::Hidden|QDir::Files|QDir::AllDirs | QDir::NoSymLinks | QDir::Readable|QDir::NoDotAndDotDot);

  QFileInfoList list = dir.entryInfoList();
  if (list.count())
  {
      for (int i=0;i<list.count();i++)
      {
       dir.remove(list.at(i).filePath());
      }
  }
     strCenter="";
     if(this->backlist.count()>1)
     {
      this->addFolder(backlist.last());
      if (this->previousCenterIndex.count()>0)
            setCenterIndex( QString(previousCenterIndex.last()).toLong()-1);

      showSlide( QString(this->previousCenterIndex.last()).toLong());
      this->previousCenterIndex.removeLast();
      this->backlist.removeLast();

     return;
     }
     else if(this->backlist.count()==1)
     {
       this->addDrives();
       if (this->previousCenterIndex.count()==0){
           this->setCenterIndex(0);

           this->showSlide(0);

          }
       else{ this->setCenterIndex( QString(previousCenterIndex.last()).toLong()-1);
           this->showSlide( QString(previousCenterIndex.last()).toLong());

       }

         this->previousCenterIndex.removeLast();
       this->backlist.removeLast();
     }


 }

// This function has been copied (and modified a little bit) from Scribus (program under GPL license):
// http://docs.scribus.net/devel/util_8cpp-source.html#l00112
QString PictureFlow::shortPathName(QString long_path) {
#ifdef Q_OS_WIN
    if ((QSysInfo::WindowsVersion >= QSysInfo::WV_NT) && (QFile::exists(long_path))) {
        QString short_path = long_path;

        const int max_path = 4096;
        WCHAR shortName[max_path];

        QString nativePath = QDir::convertSeparators(long_path);
        int ret = GetShortPathNameW((LPCWSTR) nativePath.utf16(), shortName, max_path);
        if (ret != ERROR_INVALID_PARAMETER && ret < MAX_PATH)
            short_path = QString::fromUtf16((const ushort*) shortName);

        return short_path;
    } else {
        return long_path;
    }
#endif
     return long_path;
}

void PictureFlow::addcontentstoplaylist()
{
    if (filelist.at(d->state->centerIndex).isFile()){
       emit addFiletoPl(filelist.at(d->state->centerIndex).filePath());
    }
    else if(filelist.at(d->state->centerIndex).isDir()){
       emit addFoldertoPl(filelist.at(d->state->centerIndex).filePath());
    }

}
void PictureFlow::mouseMoveEvent(QMouseEvent * event)
{
    int i = (event->pos() - d->lastgrabpos).x() / (d->state->slideWidth / 4);
    if (i > 0)
    {
        showPrevious();
        d->lastgrabpos = event->pos();
    }
    if (i < 0)
    {
        showNext();
        d->lastgrabpos = event->pos();
    }
    QWidget::mouseMoveEvent(event);
}

void PictureFlow::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

}
void PictureFlow::addPictureFolder(QString path )
{_showpic=true;
    d->renderer->isdrv=false;
  piccount=0;
    QDir dir;

    dir = QDir(qApp->applicationDirPath()+"/covers");

 dir.setFilter(QDir::Hidden|QDir::Files|QDir::AllDirs | QDir::NoSymLinks | QDir::Readable|QDir::NoDotAndDotDot);

 QFileInfoList list = dir.entryInfoList();
 if (list.count())
 {
     for (int i=0;i<list.count();i++)
     {
      dir.remove(list.at(i).filePath());
     }
 }
    clear();
    filelist.clear();
    //PictureFlow();
    //init();
    dir.mkdir(qApp->applicationDirPath()+"/pictures");
    filelist.clear();
    dir = QDir();
    dir.setSorting(QDir::Name);


 if(!path.isEmpty())
    {dir = QDir(path);

    dir.setFilter(QDir::Hidden|QDir::Files|QDir::AllDirs | QDir::NoSymLinks | QDir::Readable|QDir::NoDotAndDotDot);


    QStringList picfilters;
    picfilters<<"*.bmp"<<"*.jpg"<<"*.jpeg"<<"*.png"<<"*.pbm"<<"*.pgm"<<"*.ppm"<<"*.tiff"<<"*.gif"<<"*.xbm"<<"*.xpm";
    dir.setNameFilters( picfilters);



    QFileInfoList list = dir.entryInfoList();

    //qDebug()<<"No of files:"<<list.count();
    if (list.count()>0)
    {   myProcess=new QProcess(this);
      QObject::connect(myProcess,SIGNAL(finished(int)),this,SLOT(finished(int)));
}
    filelist=list;
    QFileIconProvider ip;


   this->createThumbnails();
}


}
void PictureFlow::init()
{

    d = new PictureFlowPrivate;
    d->state = new PictureFlowState;
    d->state->reset();
    d->state->reposition();

    d->renderer = new PictureFlowSoftwareRenderer;
    d->renderer->state = d->state;

    d->renderer->widget = this;
    d->renderer->init();
    d->animator = new PictureFlowAnimator;
    d->animator->state = d->state;
    stopAdd=false;

    QObject::connect(&d->animator->animateTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));

    QObject::connect(&d->triggerTimer, SIGNAL(timeout()), this, SLOT(render()));

  #ifdef PICTUREFLOW_QT4
    setAttribute(Qt::WA_StaticContents, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
  #endif
  #ifdef PICTUREFLOW_QT3
    setWFlags(getWFlags() | Qt::WStaticContents);
    setWFlags(getWFlags() | Qt::WNoAutoErase);
  #endif
  #ifdef PICTUREFLOW_QT2
    setWFlags(getWFlags() | Qt::WPaintClever);
    setWFlags(getWFlags() | Qt::WRepaintNoErase);
    setWFlags(getWFlags() | Qt::WResizeNoErase);
  #endif

}
void PictureFlow::finished(int ev)
{
//encount=false;

createThumbnails();

}
void PictureFlow::createThumbnails()
{//qDebug()<<"piccount"<<piccount;
    if (piccount<filelist.size())
       {
        d->renderer->fileTitle=QString("Adding Pictures,Please Wait...(%1)%").arg((double)(piccount+1)/filelist.size()*100,0,'g',4);
        d->renderer->filePath=filelist.at(piccount).filePath();
        this->repaint();
        if (myProcess>0)
    {
          myProcess->start("\""+qApp->applicationDirPath()+"/ffmpeg.exe\" -i "+"\""+shortPathName(d->renderer->filePath)+"\""+" -vframes 1 -r 1 -s 128x128 -f image2 "+ "\""+qApp->applicationDirPath()+ "/pictures/cover"+QString::number(piccount)+".jpeg""\"");
         addSlide(QPixmap(":/images/image_file.png"));
        //myProcess->waitForFinished(-1);
        //this->showNext();
       }
     piccount++;
       }
  else
    {//delete myProcess;
    d->renderer->fileTitle=QString("%1 Pictures.").arg(filelist.size()+1);
 this->repaint();
   return;
   }




}
void PictureFlow::backrelease()
{
   //this->btnBack->resize(32,32);
}

void PictureFlow::backpress()
{
    //this->btnBack->resize(28,28);
}
