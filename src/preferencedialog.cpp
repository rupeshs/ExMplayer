/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2021 Rupesh Sreeraman

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

#include "preferencedialog.h"
#include "ui_preferencedialog.h"


#if defined(Q_OS_WIN) || defined(Q_OS_OS2)
#ifdef Q_OS_WIN
#define DIRECTSOUND_VERSION 5
#include <dsound.h>
#include <windows.h>

#endif
#endif

#include <paths.h>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QColorDialog>
#include "colorutils.h"
#include "assstyles.h"
#include "rphmpfehelp.h"
#if QT_VERSION < 0x050000
#include "norwegianwoodstyle.h"
#endif
#include "languages.h"
#include <QMap>
#include <QString>
#include <QStringList>
#include <version.h>
#include <QAction>

int sound_devices;

QStringList AudioDriverLst;
#ifdef Q_OS_WIN
BOOL CALLBACK DirectSoundEnum(LPGUID guid, LPCSTR desc, LPCSTR module, LPVOID context)
{       QString s;
        s= desc;
            AudioDriverLst<<s;
                sound_devices++;

                    return TRUE;
}
#endif
preferenceDialog::preferenceDialog(QWidget *parent,QSettings *settings) :
    QDialog(parent),
    ui(new Ui::preferenceDialog)
{
    _settings=settings;
    AudioDriverLst.clear();
    apply=false;
    resetsc=false;

    ui->setupUi(this);
    ui-> groupBox_17->setVisible(false);
#ifdef Q_OS_WIN
    if (DirectSoundEnumerateA(DirectSoundEnum, NULL) != DS_OK){
        qDebug( "Error: can't list the audio devices\n");


    }

    for (int i=0;i<AudioDriverLst.count();i++)
    {
        ui->cmbAO->addItem(AudioDriverLst.at(i));

    }
#if QT_VERSION < 0x050000
       ui->comboBoxStyle->addItem("windowsxp");
#endif
#endif
#if QT_VERSION < 0x050000
    ui->comboBoxStyle->addItem("windows");
    ui->comboBoxStyle->addItem("wood");
    ui->comboBoxStyle->addItem("cleanlooks");
    ui->comboBoxStyle->addItem("aqua");
    ui->comboBoxStyle->addItem("motif");
    ui->comboBoxStyle->addItem("cde");
    ui->comboBoxStyle->addItem("plastique");
#else
    ui->comboBoxStyle->addItem("windows");
    ui->comboBoxStyle->addItem("aqua");
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
    ui->comboBox->setEnabled(false);
    ui->comboBoxStyle->addItem("GTK+");
#endif

    ui->stackedWidget->setCurrentIndex(0);
    on_listWidget_currentRowChanged(0);
    //Init sub encodings combo
    QStringList lstEncodings=QStringList(Languages::encodings().values());
    lstEncodings.sort();
    ui->comboBoxSubEncoding->addItems( lstEncodings);
    ui->labelVersion->setText("<span style=\" font-size:12pt; font-weight:600; color:#000000;\">ExMplayer v"+Version::stable()+ " <span>");


}

preferenceDialog::~preferenceDialog()
{
    delete ui;
}

void preferenceDialog::changeEvent(QEvent *e)
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
void preferenceDialog::on_buttonBox_clicked(QAbstractButton* button)
{
    if (ui->buttonBox->buttonRole(button)==QDialogButtonBox::HelpRole)
    {
        hlpDlg=new helpDialog(this);
        rphMPFEhelp hlp;
        switch(ui->stackedWidget->currentIndex())
        {
        case 0:hlpDlg->setHelpText(hlp.playerhlpstr);
            hlpDlg->show();
            break;
        case 1:hlpDlg->setHelpText(hlp.audiohlpstr);
            hlpDlg->show();
            break;
        case 2:hlpDlg->setHelpText(hlp.videohlpstr);
            hlpDlg->show();
            break;
        case 3:hlpDlg->setHelpText(hlp.subtitlehlpstr);
            hlpDlg->show();
            break;
        case 4:hlpDlg->setHelpText(hlp.internethlpstr);
            hlpDlg->show();
            break;
        case 5:hlpDlg->setHelpText(hlp.keyboardhlpstr);
            hlpDlg->show();
            break;
        case 6:hlpDlg->setHelpText(hlp.mousehlpstr);
            hlpDlg->show();
            break;

        }

    }

    if (ui->buttonBox->buttonRole(button)==QDialogButtonBox::ApplyRole)
        apply=false;

    if(!apply)
    {if(ui->buttonBox->buttonRole(button)==QDialogButtonBox::ApplyRole)
        {qDebug("setting");
            switch(ui->stackedWidget->currentIndex())
            {
            case 0:emit settingChanged("General","Priority",ui->comboBox->currentText());
                emit settingChanged("Skin","style",ui->comboBoxStyle->currentText());
                emit disableSS();
                emit settingChanged("General","recentFilesClear",QString::number(ui->checkBoxRemrm->checkState()));

                if (ui->comboBoxStyle->currentText()=="wood")
                  {
#if QT_VERSION < 0x050000
                    QApplication::setStyle(new NorwegianWoodStyle);
#endif
                }
                else if(ui->comboBoxStyle->currentText()=="aqua")
                    emit setAqua();
                else
                {
 #if QT_VERSION < 0x050000
                    qApp->setStyle(ui->comboBoxStyle->currentText());
 #endif
                }



                //if(ui->comboBoxStyle->currentText()!="windowsxp"&&ui->comboBoxStyle->currentText()!="aqua")
                QApplication::setPalette(QApplication::style()->standardPalette());

                emit restartComplete();
                break;

            case 1:{
                emit settingChanged("Audio","EnableEQ",QString::number(ui->cbEnableAEq->checkState()));
                emit settingChanged("Audio","Driver",ui->cmbAO->currentText());
                emit settingChanged("Audio","DevNo",QString::number(ui->cmbAO->currentIndex()));
                emit settingChanged("Audio","VolumeBoost",QString::number(ui->hSliderVolumeBoost->value()));
                emit restartComplete();

                break;
            }
            case 2: {

                     emit settingChanged("Video","EnableSoftEQ",QString::number(ui->cbEnableVideoSoftEq->checkState()));
                     emit restartComplete();
                     break;
            }
            case 3 :{AssStyles ass;
                //qDebug()<<ui->texcol->palette().color(QPalette::Base).toRgb().value();
                ass.primarycolor=ui->texcol->palette().color(QPalette::Base).rgb();
                ass.backcolor=ui->shcol->palette().color(QPalette::Base).rgb();
                ass.outlinecolor=ui->borcol->palette().color(QPalette::Base).rgb();
                ass.fontname=ui->fontComboBox->currentFont().family();
                ass.fontsize=ui->spinBoxFs->value();
                ass.bold=ui->checkBoxBold->isChecked();
                ass.italic=ui->checkBoxItalic->isChecked();
                ass.valignment=ui->comboBoxVa->currentIndex();
                ass.halignment=ui->comboBoxHa->itemData(ui->comboBoxHa->currentIndex()).toInt();
                ass.save(_settings);
                ass.exportStyles(Paths::configPath()+"/styles.ass");
                emit settingChanged("Subtitles","UseCodePage",QString::number(ui->checkBoxUseCodePage->checkState()));
                emit settingChanged("Subtitles","CodePage",ui->comboBoxSubEncoding->currentText());
#ifdef Q_OS_WIN
                //Open fontconfig

                //Calculate Sha1
                //QStringList fontConfLst;
                /*QByteArray hashData;
                QFile inputFile(qApp->applicationDirPath()+"/mplayer/fonts/fonts.conf");

                    if (inputFile.open(QIODevice::ReadOnly)) {
                        QByteArray fileData = inputFile.readAll();
                        hashData =  QCryptographicHash::hash(fileData, QCryptographicHash::Sha1);
                    }
                    qDebug() << hashData.toHex();
                    QMessageBox::critical(this,QString(hashData.toHex()),"gfd");
                    QString actHash="c8ba9d01342f8488c815fb5e63e96f53ba9f46fb";*/
                // if ( QString(hashData.toHex())!=actHash)
                //{
                //   qDebug() << "Different font config";
                if (ui->checkBoxUseCodePage->isChecked())
                {QString exeFileName(qApp->applicationDirPath()+"/exmplayer-font-cache.exe");

                int result = (int)::ShellExecuteA(0, "open", exeFileName.toUtf8().constData(), 0, 0, SW_HIDE);
                if (SE_ERR_ACCESSDENIED == result)
                {
                    // Requesting elevation(Windows Vista/Window7/window8)
                    result = (int)::ShellExecuteA(0, "runas", exeFileName.toUtf8().constData(), 0, 0, SW_HIDE);
                }
                }

                //c8ba9d01342f8488c815fb5e63e96f53ba9f46fb
                /*if (inputFile.open(QIODevice::ReadOnly))
                {
                    QTextStream in(&inputFile);
                    while ( !in.atEnd() )
                    {
                        fontConfLst<< in.readLine();

                    }
                    inputFile.close();
                }

                if(fontConfLst.filter(QRegExp(".*<dir></dir>")).count()==1)
                {
                    fontConfLst.replaceInStrings("<dir></dir>","<dir>WINDOWSFONTDIR</dir>");
                    qDebug()<<fontConfLst;
                    QFile outFile(qApp->applicationDirPath()+"/mplayer/fonts/fonts.conf");
                    if (outFile.open(QFile::WriteOnly|QFile::Truncate))
                    {
                        foreach (QString fontConfig, fontConfLst) {
                           outFile.write(fontConfig.toAscii()+"\n");
                        }

                    }
                    else
                    {
                       //What to do? (Beta)
                       // QMessageBox::critical(this,"Error","failed to open file for writing");

                    }

                    outFile.close();

                }*/
#endif

                emit restartComplete();
                break;
            }
            case 4:{
                emit settingChanged("Network","ipv",ui->cmbiv->currentText());
                emit settingChanged("Network","Bandwidth",QString::number(ui->sbNetBw->value()));
                emit settingChanged("Network","cache",QString::number(ui->sbNetCache->value()));
                emit settingChanged("Network","seekmin",QString::number(ui->sbseekmin->value()));
                emit settingChanged("Network","cachemin",QString::number(ui->sbNetCachemin->value()));

                break;
            }
            case 5:if( !resetsc)
                {saveActionToXml();
                    //emit reloadshortcut();
                    QMessageBox::information(this,qApp->applicationName(),tr("Shortcut will be active after a restart."),QMessageBox::Ok,QMessageBox::Cancel);
                }
                break;
            case 6:  {emit settingChanged("Mouse","Wheel",QString::number(mw));
                emit setmousewheelrole();
                break;
            }
            case 7:settingChanged("Updates","Automatic",QString::number(ui->checkUpdates->isChecked()));
        }

    }

}
apply=true;
if(ui->buttonBox->buttonRole(button)==QDialogButtonBox::AcceptRole)
this->close();


}
void preferenceDialog::on_listWidget_currentRowChanged(int currentRow)
{
    switch(currentRow)
    {
    case 0://qDebug()<<_settings->value("General/Priority","abovenormal").toString();
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(_settings->value("General/Priority","abovenormal").toString()));
        ui->comboBoxStyle->setCurrentIndex(ui->comboBoxStyle->findText(_settings->value("Skin/style","aqua").toString()));
        if ( _settings->value("General/recentFilesClear",0).toInt()==2)
            ui->checkBoxRemrm->setCheckState(Qt::Checked);
        else
            ui->checkBoxRemrm->setCheckState(Qt::Unchecked);

        break;
    case  1 :
        if (_settings->value("Audio/EnableEQ","2").toInt()==2)
            ui->cbEnableAEq->setCheckState(Qt::Checked);
        else
            ui->cbEnableAEq->setCheckState(Qt::Unchecked);

        ui->cmbAO->setCurrentIndex(ui->cmbAO->findText(_settings->value("Audio/Driver","Auto").toString()));

        ui->hSliderVolumeBoost->setValue(_settings->value("Audio/VolumeBoost","500").toInt());
        break;
    case  2 :{QDesktopServices mycomputer;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
     QString picfolder=mycomputer->storageLocation(QDesktopServices::PicturesLocation);
 #else
     QString picfolder=QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
 #endif

        ui->lineEditSc->setText(_settings->value("Video/CaptureDir",picfolder).toString());
        if (_settings->value("Video/EnableSoftEQ","0").toInt()==0)
            ui->cbEnableVideoSoftEq->setCheckState(Qt::Unchecked);
        else
            ui->cbEnableVideoSoftEq->setCheckState(Qt::Checked);


        break;
    }
    case 3 :{AssStyles ass;
        ass.load(_settings);
        ColorUtils::setBackgroundColor(ui->texcol,QColor(ass.primarycolor));
        ColorUtils::setBackgroundColor(ui->shcol,QColor(ass.backcolor));
        ColorUtils::setBackgroundColor(ui->borcol,QColor(ass.outlinecolor));
        ui->fontComboBox->setCurrentFont(QFont(ass.fontname));
        ui->spinBoxFs->setValue(ass.fontsize);
        ui->checkBoxBold->setChecked(ass.bold);
        ui->checkBoxItalic->setChecked(ass.italic);
        ui->comboBoxHa->clear();
        ui->comboBoxHa->addItem(tr("Left", "horizontal alignment"), 1);
        ui->comboBoxHa->addItem(tr("Centered", "horizontal alignment"), 2);
        ui->comboBoxHa->addItem(tr("Right", "horizontal alignment"), 3);

        ui->comboBoxHa->setCurrentIndex(ui->comboBoxHa->itemData(ui->comboBoxHa->currentIndex()).toInt());
        ui->comboBoxVa->setCurrentIndex(ass.valignment);

        if (_settings->value("Subtitles/UseCodePage","0").toInt()==0)

            ui->checkBoxUseCodePage->setCheckState(Qt::Unchecked);
        else
            ui->checkBoxUseCodePage->setCheckState(Qt::Checked);

        ui->comboBoxSubEncoding->setCurrentIndex(ui->comboBoxSubEncoding->findText(_settings->value("Subtitles/CodePage","Western European Languages").toString()));

        break;
    }

    case 4:ui->groupBox_7->setVisible(false);
        ui->groupBox_8->setVisible(false);
        ui->groupBox_9->setVisible(false);
        ui->sbNetCache->setValue(_settings->value("Network/cache","320").toInt());
        break;
    case 6: int mousewheelrole ;
        mousewheelrole =_settings->value("Mouse/Wheel","0").toInt();

        if  (mousewheelrole==0)
            ui->rbVol->setChecked(true);
        else
            ui->rbSk->setChecked(true);
        break;
    case 8:{ QFileInfo fi(qApp->applicationFilePath());
        QDateTime dt=fi.created();
        //ui->labelDate->setText(QString("Build on "+dt.toString()));
        break;
    }
    case  5 :
    {QList<QAction *> acts = _w->findChildren<QAction*>();

        for (int i=0;i<acts.count();i++)
        {
            if(acts.at(i)->objectName()!="")
            {QTableWidgetItem *newItem = new QTableWidgetItem(acts.at(i)->objectName());
                ui->twsc->setRowCount(i+1);
                newItem->setIcon(acts.at(i)->icon());
                ui->twsc->setItem(i,0,newItem);
                QTableWidgetItem *newItem1 = new QTableWidgetItem(acts.at(i)->text());
                ui->twsc->setItem(i,1,newItem1);
                QTableWidgetItem *newItem2 = new QTableWidgetItem(acts.at(i)->shortcut().toString());
                ui->twsc->setItem(i,2,newItem2);
            }
        }
        break;
    }
    case 7:{
        if (_settings->value("Updates/Automatic","1").toInt()==1)
            ui->checkUpdates->setCheckState(Qt::Checked);
        else
            ui->checkUpdates->setCheckState(Qt::Unchecked);

        //ui->checkUpdates->setChecked(_settings->value("","1").toInt());
        break;
    }

    }
}
void preferenceDialog::saveActionToXml()
{//QMessageBox msgBox;

    QFile file(Paths::configPath()+"/"+"sc_user.xml");
    file.resize(0);

    if (!file.open(QIODevice::ReadWrite)) {
        // msgBox.setText(file.errorString());
        //msgBox.exec();
    }
    else
    {QXmlStreamWriter writer(&file);

        for (int i=0; i< ui->twsc->rowCount();i++)
        {if (i==0)
            {writer.setAutoFormatting(true);
                writer.writeStartDocument();
                writer.writeStartElement("Shortcuts");
            }
            writer.writeStartElement("Action");
            writer.writeTextElement("Name",ui->twsc->item(i,0)->text());
            writer.writeTextElement("ShortCut", ui->twsc->item(i,2)->text());
            writer.writeEndElement();

            if (i== ui->twsc->rowCount()-1)
                writer.writeEndElement();

        }

    }



}

void preferenceDialog::on_twsc_itemDoubleClicked(QTableWidgetItem* item)
{
    scg=new ShortcutGetter(this);
    QString str=scg->exec(ui->twsc->item(item->row(),2)->text());

    if (str.isEmpty())
    {resetsc=false;
        ui->twsc->item(item->row(),2)->setText(str);
        return;
    }
    else
    {//qDebug()<<str;
        QList<QTableWidgetItem *>  ni ;
        ni= ui->twsc->findItems(str,Qt::MatchExactly);
        if( ni.count()>0)
        { if (str!=ui->twsc->item(item->row(),2)->text())
            {QMessageBox::critical(this,qApp->applicationName(),tr("Shrotcut already in use,Please select another key"),QMessageBox::Ok,QMessageBox::Cancel);
                return;
            }
        }
        else
        {ui->twsc->item(item->row(),2)->setText(str);
            resetsc=false;
        }
    }
}

void preferenceDialog::on_pushButton_clicked()
{
    resetsc=true;
    QFile file(Paths::configPath()+"/"+"sc_user.xml");
    file.remove();
#ifdef Q_OS_WIN
    file.copy(Paths::configPath()+"/"+"sc_default.xml",Paths::configPath()+"/"+"sc_user.xml");
#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
    file.copy(Paths::getStaticConfigPath()+"/"+"sc_default.xml",Paths::configPath()+"/"+"sc_user.xml");
# endif


    QMessageBox::information(this,qApp->applicationName(),tr("New Shortcut(s) will be active after a restart."),QMessageBox::Ok,QMessageBox::Cancel);


}

void preferenceDialog::on_rbVol_toggled(bool checked)
{
    if (checked)
        mw=0;
    else
        mw=1;
}

void preferenceDialog::on_pushButton_2_clicked()
{
    ui->sbNetCache->setValue(320);
    // emit settingChanged("Network","cache",QString::number(ui->sbNetCache->value()));

}

void preferenceDialog::on_chScDir_clicked()
{
    QDesktopServices mycomputer;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
     QString picfolder=mycomputer->storageLocation(QDesktopServices::PicturesLocation);
 #else
     QString picfolder=QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
 #endif
    QString root=_settings->value("Video/CaptureDir",picfolder).toString();


    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    root,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (!dir.isEmpty())
    {
        ui->lineEditSc->setText( dir);
        emit settingChanged("Video","CaptureDir",dir);
    }
}

void preferenceDialog::on_pushButton_3_clicked()
{
    QColorDialog::ColorDialogOptions options;
    const QColor col= QColorDialog::getColor ( QColor(), this,"Select text color",  options );
    ColorUtils::setBackgroundColor(ui->texcol,col);

}

void preferenceDialog::on_pushButton_4_clicked()
{

    QColorDialog::ColorDialogOptions options;
    const QColor col= QColorDialog::getColor ( QColor(), this,"Select text color",  options );
    ColorUtils::setBackgroundColor(ui->borcol,col);

}

void preferenceDialog::on_pushButton_5_clicked()
{

    QColorDialog::ColorDialogOptions options;
    const QColor col= QColorDialog::getColor ( QColor(), this,"Select text color",  options );
    ColorUtils::setBackgroundColor(ui->shcol,col);

}

void preferenceDialog::on_pushButton_6_clicked()
{
    AssStyles ass;
    ass.exportStyles(Paths::configPath()+"/styles.ass") ;
    ColorUtils::setBackgroundColor(ui->texcol,QColor(ass.primarycolor));
    ColorUtils::setBackgroundColor(ui->shcol,QColor(ass.backcolor));
    ColorUtils::setBackgroundColor(ui->borcol,QColor(ass.outlinecolor));
    ui->fontComboBox->setCurrentFont(QFont(ass.fontname));
    ui->spinBoxFs->setValue(ass.fontsize);
    ui->checkBoxBold->setChecked(ass.bold);
    ui->checkBoxItalic->setChecked(ass.italic);
    ui->comboBoxHa->setCurrentIndex(1);
    ui->comboBoxVa->setCurrentIndex(ass.valignment);
    ui->checkBoxUseCodePage->setChecked(false);

}

void preferenceDialog::on_hSliderVolumeBoost_valueChanged(int value)
{
    ui->labelVolumeBoost->setText(QString::number(value)+QString("%"));
}

void preferenceDialog::on_pushButtonResetVolumeBoost_clicked()
{
    ui->hSliderVolumeBoost->setValue(500);
}
