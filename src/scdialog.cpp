/*  umplayer, GUI front-end for mplayer.
    Copyright (C) 2010 Ori Rejwan

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include <QPainter>
#include <QBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include "myborder.h"

SCDialog* SCDialog::m_instance = 0;

SCTitleWidget::SCTitleWidget(QWidget *parent)
    :QWidget(parent)
{
    titleBGPix = QPixmap(":/images/bg-shoutcast-toolbar.png");
    scLogo = QPixmap(":/images/bg-shoutcast-logo.png");
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

QSize SCTitleWidget::sizeHint() const
{
    return QSize(380, 36);
}

void SCTitleWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setPen(Qt::white);
    QFont font = p.font();
    font.setPixelSize(14);
    p.setFont(font);
    p.drawTiledPixmap(rect(), titleBGPix);
    QRect logoRect = scLogo.rect();
    p.drawText(5, 0, width() - 5 - logoRect.width(), titleBGPix.height(), Qt::AlignLeft | Qt::AlignVCenter , m_text );
    logoRect.moveRight(width() - 5);
    logoRect.moveTop((height() - logoRect.height())/2 - 2);
    p.drawPixmap(logoRect, scLogo);
}

void SCTitleWidget::setText(QString text)
{
    m_text = text;
}

/*********************************************************************
  **************************  SCDialog  ******************************
  *******************************************************************/


SCDialog::SCDialog(QWidget *parent) :
    QWidget(parent),overlayVisible(false)
{

    this->setStyleSheet("QWindow(background-color:#ffffff;");
    QStringList logos;
    logos << "Umplayer-16" << "Umplayer-24" <<"Umplayer-32" << "Umplayer-48" << "Umplayer-256" << "Umplayer-512" ;
   // setWindowIcon( Images::icon(logos) );
    scLogo = QPixmap(":/images/sc-logo.png");
    //titleWidget = new SCTitleWidget(this);
    streamList = new QListWidget(this);
    QHBoxLayout* hbox = new QHBoxLayout;
    searchBox = new SearchBox(this);
    connect(searchBox, SIGNAL(search(QString)), this, SLOT(setSearchTerm(QString)));
    QLabel* logoLabel = new QLabel(this);
    logoLabel->setText("<a href=\"http://www.shoutcast.com/\"><img src=\":/images/sc-logo.png\"> </a>");
    logoLabel->setFixedSize(scLogo.size());
    logoLabel->setOpenExternalLinks(true);
    hbox->addWidget(searchBox);
    hbox->addSpacerItem(new QSpacerItem( 10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred));
    hbox->addWidget(logoLabel);
    hbox->setContentsMargins(6, 6, 9, 5);
    MyBorder* border = new MyBorder(this);

    QVBoxLayout* vbox = new QVBoxLayout;
    //vbox->addWidget(titleWidget);
    vbox->addWidget(streamList);
    vbox->addWidget(border);
    vbox->addLayout(hbox);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);
    setLayout(vbox);    
    streamList->setFrameShape(QFrame::NoFrame);
    delegate = new SCDelegate(streamList);
    streamList->setItemDelegate(delegate);
    //streamList->setMouseTracking(true);
    //streamList->viewport()->installEventFilter(this);
    streamList->setContextMenuPolicy(Qt::CustomContextMenu);
    streamList->setAutoScroll(false);
    overlay = new OverlayWidget(this);
    overlay->raise();
    setLoadingOverlay(false);    
    api = new SCDataAPI(this);    
    connect(streamList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(videoClicked(QListWidgetItem*)));
    connect(streamList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(videoDblClicked(QListWidgetItem*)));
    connect(streamList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));


}

void SCDialog::setMode(Mode mode)
{
    disconnect(api, SIGNAL(finalResult(SCReply&)), this, SLOT(gotAPIReply(SCReply&)) );
    reset();
    if(mode == Button)
    {
        searchTerm = QString();
        searchBox->setText(searchTerm);
        setWindowTitle("Top 500 Stations Today");
        setLoadingOverlay(true);
        api->getTop500();
    }
    else if(mode == Search)
    {
        setLoadingOverlay(true);
        setWindowTitle(QString("Results for \"%1\"").arg(searchTerm));
        searchBox->setText(searchTerm);
        api->getSearchResult(searchTerm);
    }
    connect(api, SIGNAL(finalResult(SCReply&)), this, SLOT(gotAPIReply(SCReply&)) );
}

void SCDialog::gotAPIReply(SCReply &formattedReply)
{
    if(!formattedReply.errorString.isEmpty())
    {
        overlay->setText("Error: Could not connect to SHOUTcast Server.");
        return;
    }
    if(formattedReply.results.count() == 0)
    {
        if(searchTerm.isEmpty())
            overlay->setText("No radio stations found");
        else
            overlay->setText("No radio stations found for \"" + searchTerm + "\"");
        return;
    }
    for(int i=0; i < formattedReply.totalResultCount; ++i)
    {
        SingleSCResult* sc = new SingleSCResult;
        *sc = formattedReply.results.at(i);
        QListWidgetItem* item = new QListWidgetItem(streamList, QListWidgetItem::UserType + 1 );
        item->setData(0, qVariantFromValue(sc));               
    }    
    setLoadingOverlay(false);
}

bool SCDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == streamList->viewport())
    {
        if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent* m = static_cast<QMouseEvent*>(event);
            QListWidgetItem* hoverItem =  streamList->itemAt(streamList->viewport()->mapFromGlobal(m->globalPos()));
            for(int i=0; i < streamList->count(); ++i)
            {
                QListWidgetItem* wi = streamList->item(i);
                if( wi == hoverItem )
                {
                    wi->setData(SCDelegate::HoverRole, true);
                }
                else
                {
                    wi->setData(SCDelegate::HoverRole, false);
                }
            }
            if(hoverItem)
                setCursor(QCursor(Qt::PointingHandCursor));
            else
                setCursor(QCursor(Qt::ArrowCursor));
        }
        if(event->type() == QEvent::Leave)
        {
            for(int i=0; i < streamList->count(); ++i)
            {
                QListWidgetItem* wi = streamList->item(i) ;
                wi->setData(SCDelegate::HoverRole, false);
            }
            setCursor(QCursor(Qt::ArrowCursor));
        }
    }
    return false;
}

void SCDialog::setLoadingOverlay(bool enable)
{
    overlayVisible = enable;
    if(enable)
    {
        overlay->resize(size());
        overlay->setText(QString());
        overlay->show();
    }
    else
    {
        overlay->hide();
    }
}

void SCDialog::resizeEvent(QResizeEvent* r)
{
    if(overlayVisible)
    {
        overlay->resize(r->size());
    }
}

void SCDialog::setSearchTerm(QString term)
{
    searchTerm = term;    
    setMode(Search);
}

void SCDialog::reset()
{
    streamList->clear();
    api->reset();            
}

void SCDialog::videoClicked(QListWidgetItem *item)
{
    for(int i=0; i < streamList->count(); ++i)
    {
        QListWidgetItem* wi = streamList->item(i) ;
        wi->setData(SCDelegate::ClickRole, false);
    }
    item->setData(SCDelegate::ClickRole, true);
}

void SCDialog::videoDblClicked(QListWidgetItem *item)
{
    SingleSCResult* ssr = item->data(0).value<SingleSCResult*>();
    emit gotUrls(QString("http://yp.shoutcast.com/sbin/tunein-station.pls?id=") + ssr->id  , ssr->name);
}

void SCDialog::showContextMenu(QPoint point)
{
    QMenu menu;
    menu.addAction("Tune In");
    QAction* action = menu.exec(streamList->viewport()->mapToGlobal(point));
    if(!action) return;
    QListWidgetItem* item = streamList->itemAt(point);
    if(action->text().startsWith('T'))
    {
       videoDblClicked(item);
    }
}


SCDialog* SCDialog::instance()
{
    if(m_instance == 0)
    {
        m_instance = new SCDialog;
    }
    return m_instance;
}
