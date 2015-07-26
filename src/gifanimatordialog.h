/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2015 Rupesh Sreeraman

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
#ifndef GIFANIMATORDIALOG_H
#define GIFANIMATORDIALOG_H


#include <QDialog>
#include <mplayerfe.h>
#include "gifgenerator.h"
#include "gifpalettegenerator.h"
#include "rphfile.h"
#include "filefilters.h"
#include <QMovie>
namespace Ui {
class GifAnimatorDialog;
}

class GifAnimatorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GifAnimatorDialog(QWidget *parent ,mplayerfe *mpf);
    ~GifAnimatorDialog();
    QString filepath;
    
private:
    Ui::GifAnimatorDialog *ui;
     QPointer<mplayerfe> mp;
     float startPos;
     float stopPos;
     int testnum;
     QString outPath;
     QPointer<GifPaletteGenerator> gifPalettteGen;
     QPointer<GifGenerator> gifGene;
     QMovie *movie;
     QWidget *extension;
     QString gifPath;

signals:
    void showfile(QString opt,QString fn);
private slots:

    void on_pushButtonOpenFolder_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonAnimate_clicked();
    void triggerGifGenerator(int ec);
    void ProcessingCompleted(int ec,QString outpath);
    void on_pushButtonReset_clicked();
    void toggleExtension(bool fa);
    void on_checkBox_toggled(bool checked);
};

#endif // GIFANIMATORDIALOG_H
