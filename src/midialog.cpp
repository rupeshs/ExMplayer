/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2013 Rupesh Sreeraman

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

#include "midialog.h"
#include "ui_midialog.h"
#include "QFileDialog"
#include "QTextStream"
#include "QDebug"

miDialog::miDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::miDialog)
{
    ui->setupUi(this);


    this->setWindowFlags(Qt::Window);
}

miDialog::~miDialog()
{
    delete ui;
}

void miDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void miDialog::setMiText(QString tex)
{
    ui->textEdit->setText(tex);
}


void miDialog::setbtnSaveEnable(bool val)
{
    ui->btncov->setEnabled(val);
}

void miDialog::on_pushButton_clicked()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                         tr("Save as"),
                                         "",
                                         tr("html (*.html)"),
                                         &selectedFilter,
                                         options);
    if (!fileName.isEmpty())
      {
         QFile file(fileName);
         file.open(QIODevice::WriteOnly);
         QTextStream out(&file);   // we will serialize the data into the file

         QString html="<p><b><SPAN STYLE=\"color: blue\">Created by ExMplayer 1.1 Copyright (c) 2010 Rupesh.S</SPAN></b></p>"+ui->textEdit->toHtml();

         //filename without extension
         QFileInfo fi(fileName);
         //qDebug()<<"file"<<fi.absolutePath();
         //qDebug()<<"f"<<fi.baseName();
         QString path;
         QString str;
         str.resize(1);

         str[0] = QChar('"');
         //qDebug()<<str;
          path=QDir::tempPath()+"/mcover.jpeg";
          path.append(str);
          path.prepend(str);
         html.replace(path,fi.baseName()+".jpeg");

         out <<html ;
         QFile file1(QDir::tempPath()+"/"+"mcover.jpeg");
        //qDebug()<<fi.absolutePath()+fi.baseName()+".jpeg";
         file1.copy(QDir::tempPath()+"/"+"mcover.jpeg",fi.absolutePath()+"/"+fi.baseName()+".jpeg");

     }

}

void miDialog::on_pushButton_3_clicked()
{
    this->close();
}

void miDialog::on_btncov_clicked()
{
    emit  saveCoverArt();
}
