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
#include "winampdspdialog.h"
#include "ui_winampdspdialog.h"
#include<QtCore>
#include<QFileDialog>
#include <QSettings>
#include "rphfile.h"
WinampDspDialog::WinampDspDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinampDspDialog)
{
    ui->setupUi(this);

}

WinampDspDialog::~WinampDspDialog()
{
    delete ui;
}

void WinampDspDialog::changeEvent(QEvent *e)
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
void WinampDspDialog::getPlugins()
{//if (_settings)
    //qDebug()<<_settings->value("Audio/Wadsp_rootdir",QString("C:\\Program Files\\Winamp\\Plugins\\")).toString();

    ui->lineEdit->setText(_settings->value("Audio/Wadsp_rootdir",QString("C:\\Program Files\\Winamp\\Plugins\\")).toString());
 QDir dir(ui->lineEdit->text());
 dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
 QStringList filters;
 filters << "*.dll";
 dir.setNameFilters(filters);
ui->listWidget->clear();
      QFileInfoList list = dir.entryInfoList();
if(list.count())
      { for (int i = 0; i < list.size(); ++i) {
            if(list.at(i).baseName().contains("dsp_")||list.at(i).baseName().contains("DSP_"))
                  ui->listWidget->addItem(list.at(i).absoluteFilePath());


            }
}

  }

void WinampDspDialog::on_pushButton_clicked()
{
    QString dir = rphFile::getDir(this,"Open winamp plugin directory","");

  if (!dir.isEmpty())
   {
    ui->lineEdit->setText(dir);
    emit settingChanged("Audio","Wadsp_rootdir",dir);
    getPlugins();
}

}

void WinampDspDialog::on_pushButton_2_clicked()
{
  emit enableWinampPlugin(false,ui->listWidget->selectedItems().at(0)->text());
  emit settingChanged("Audio","EnableWadsp",QString::number(0));
  ui->pushButton_2->setEnabled(false);
}

void WinampDspDialog::on_buttonBox_accepted()
{if (ui->listWidget->selectedItems().count()>0)
    {emit enableWinampPlugin(true,ui->listWidget->selectedItems().at(0)->text());
    emit settingChanged("Audio","EnableWadsp",QString::number(1));
    emit settingChanged("Audio","Wadsp_path",QString(ui->listWidget->selectedItems().at(0)->text()));
     ui->pushButton_2->setEnabled(true);
   }
}
void  WinampDspDialog::showEvent ( QShowEvent * event )
{
    /*if (settings->value("Audio/EnableWadsp","0").toInt()==0)
    ui->pushButton_2->setEnabled(false);
 else
    ui->pushButton_2->setEnabled(true);*/

//ui->listWidget->setCurrentIndex(ui->listWidget->findItems(_settings->value("Audio/Wadsp_path","").));
    QDialog::showEvent(event);
}
void WinampDspDialog::dlgsettings(QSettings* se)
{
   _settings= se;
   this->getPlugins();

if (_settings->value("EnableWadsp","0").toInt())
   ui->pushButton_2->setEnabled(true);
else
   ui->pushButton_2->setEnabled(false);

}
