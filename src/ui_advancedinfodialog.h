/********************************************************************************
** Form generated from reading UI file 'advancedinfodialog.ui'
**
** Created: Sun Apr 7 17:28:37 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVANCEDINFODIALOG_H
#define UI_ADVANCEDINFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdvancedInfoDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBoxAudio;
    QCheckBox *checkBoxVideo;
    QCheckBox *checkBoxSub;
    QGroupBox *groupBox_2;
    QLabel *labelAudioCodec;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *labelVideoCodec;
    QGroupBox *groupBox_4;
    QLabel *labelAudioDevice;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_2;
    QLabel *labelVideoDevice;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_6;
    QWidget *layoutWidget;
    QFormLayout *formLayout_2;
    QLabel *labelSpeed_2;
    QLabel *labelAudioCPU;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout_3;
    QLabel *labelSpeed_3;
    QLabel *labelVideoCPU;
    QWidget *layoutWidget_3;
    QFormLayout *formLayout_5;
    QLabel *labelFramesCap;
    QLabel *labelFrames;
    QWidget *layoutWidget_4;
    QFormLayout *formLayout_6;
    QLabel *labelSpeed_6;
    QLabel *labelAVdealy;
    QWidget *layoutWidget1;
    QFormLayout *formLayout;
    QLabel *labelSpeed;
    QLabel *labellSpeedFactor;

    void setupUi(QDialog *AdvancedInfoDialog)
    {
        if (AdvancedInfoDialog->objectName().isEmpty())
            AdvancedInfoDialog->setObjectName(QString::fromUtf8("AdvancedInfoDialog"));
        AdvancedInfoDialog->resize(470, 425);
        AdvancedInfoDialog->setMinimumSize(QSize(470, 425));
        AdvancedInfoDialog->setMaximumSize(QSize(470, 425));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/ExMplayer.png"), QSize(), QIcon::Normal, QIcon::Off);
        AdvancedInfoDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(AdvancedInfoDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(AdvancedInfoDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 51));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBoxAudio = new QCheckBox(groupBox);
        checkBoxAudio->setObjectName(QString::fromUtf8("checkBoxAudio"));
        checkBoxAudio->setCheckable(true);
        checkBoxAudio->setChecked(false);
        checkBoxAudio->setAutoRepeat(false);
        checkBoxAudio->setAutoExclusive(false);
        checkBoxAudio->setTristate(false);

        horizontalLayout->addWidget(checkBoxAudio);

        checkBoxVideo = new QCheckBox(groupBox);
        checkBoxVideo->setObjectName(QString::fromUtf8("checkBoxVideo"));

        horizontalLayout->addWidget(checkBoxVideo);

        checkBoxSub = new QCheckBox(groupBox);
        checkBoxSub->setObjectName(QString::fromUtf8("checkBoxSub"));

        horizontalLayout->addWidget(checkBoxSub);


        gridLayout->addWidget(groupBox, 0, 0, 1, 2);

        groupBox_2 = new QGroupBox(AdvancedInfoDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        labelAudioCodec = new QLabel(groupBox_2);
        labelAudioCodec->setObjectName(QString::fromUtf8("labelAudioCodec"));
        labelAudioCodec->setGeometry(QRect(10, 20, 211, 71));
        labelAudioCodec->setWordWrap(true);

        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(AdvancedInfoDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelVideoCodec = new QLabel(groupBox_3);
        labelVideoCodec->setObjectName(QString::fromUtf8("labelVideoCodec"));
        labelVideoCodec->setScaledContents(true);
        labelVideoCodec->setWordWrap(true);

        gridLayout_3->addWidget(labelVideoCodec, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 1, 1, 1, 1);

        groupBox_4 = new QGroupBox(AdvancedInfoDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        labelAudioDevice = new QLabel(groupBox_4);
        labelAudioDevice->setObjectName(QString::fromUtf8("labelAudioDevice"));
        labelAudioDevice->setGeometry(QRect(10, 20, 201, 71));
        labelAudioDevice->setWordWrap(true);

        gridLayout->addWidget(groupBox_4, 2, 0, 1, 1);

        groupBox_5 = new QGroupBox(AdvancedInfoDialog);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_2 = new QGridLayout(groupBox_5);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labelVideoDevice = new QLabel(groupBox_5);
        labelVideoDevice->setObjectName(QString::fromUtf8("labelVideoDevice"));
        labelVideoDevice->setScaledContents(true);
        labelVideoDevice->setWordWrap(true);

        gridLayout_2->addWidget(labelVideoDevice, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_5, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(AdvancedInfoDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 0, 1, 2);

        groupBox_6 = new QGroupBox(AdvancedInfoDialog);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        layoutWidget = new QWidget(groupBox_6);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 50, 207, 15));
        formLayout_2 = new QFormLayout(layoutWidget);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        labelSpeed_2 = new QLabel(layoutWidget);
        labelSpeed_2->setObjectName(QString::fromUtf8("labelSpeed_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labelSpeed_2);

        labelAudioCPU = new QLabel(layoutWidget);
        labelAudioCPU->setObjectName(QString::fromUtf8("labelAudioCPU"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, labelAudioCPU);

        layoutWidget_2 = new QWidget(groupBox_6);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 70, 207, 15));
        formLayout_3 = new QFormLayout(layoutWidget_2);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        labelSpeed_3 = new QLabel(layoutWidget_2);
        labelSpeed_3->setObjectName(QString::fromUtf8("labelSpeed_3"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, labelSpeed_3);

        labelVideoCPU = new QLabel(layoutWidget_2);
        labelVideoCPU->setObjectName(QString::fromUtf8("labelVideoCPU"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, labelVideoCPU);

        layoutWidget_3 = new QWidget(groupBox_6);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(240, 50, 201, 16));
        formLayout_5 = new QFormLayout(layoutWidget_3);
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        formLayout_5->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_5->setContentsMargins(0, 0, 0, 0);
        labelFramesCap = new QLabel(layoutWidget_3);
        labelFramesCap->setObjectName(QString::fromUtf8("labelFramesCap"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, labelFramesCap);

        labelFrames = new QLabel(layoutWidget_3);
        labelFrames->setObjectName(QString::fromUtf8("labelFrames"));

        formLayout_5->setWidget(0, QFormLayout::FieldRole, labelFrames);

        layoutWidget_4 = new QWidget(groupBox_6);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(240, 30, 207, 15));
        formLayout_6 = new QFormLayout(layoutWidget_4);
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        formLayout_6->setContentsMargins(0, 0, 0, 0);
        labelSpeed_6 = new QLabel(layoutWidget_4);
        labelSpeed_6->setObjectName(QString::fromUtf8("labelSpeed_6"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, labelSpeed_6);

        labelAVdealy = new QLabel(layoutWidget_4);
        labelAVdealy->setObjectName(QString::fromUtf8("labelAVdealy"));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, labelAVdealy);

        layoutWidget1 = new QWidget(groupBox_6);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 30, 166, 15));
        formLayout = new QFormLayout(layoutWidget1);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        labelSpeed = new QLabel(layoutWidget1);
        labelSpeed->setObjectName(QString::fromUtf8("labelSpeed"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelSpeed);

        labellSpeedFactor = new QLabel(layoutWidget1);
        labellSpeedFactor->setObjectName(QString::fromUtf8("labellSpeedFactor"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labellSpeedFactor);


        gridLayout->addWidget(groupBox_6, 3, 0, 1, 2);


        retranslateUi(AdvancedInfoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AdvancedInfoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AdvancedInfoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AdvancedInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *AdvancedInfoDialog)
    {
        AdvancedInfoDialog->setWindowTitle(QApplication::translate("AdvancedInfoDialog", "Advanced Info", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AdvancedInfoDialog", "Stream(s)", 0, QApplication::UnicodeUTF8));
        checkBoxAudio->setText(QApplication::translate("AdvancedInfoDialog", "Audio", 0, QApplication::UnicodeUTF8));
        checkBoxVideo->setText(QApplication::translate("AdvancedInfoDialog", "Video", 0, QApplication::UnicodeUTF8));
        checkBoxSub->setText(QApplication::translate("AdvancedInfoDialog", "Subtitle", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("AdvancedInfoDialog", "Audio Codec", 0, QApplication::UnicodeUTF8));
        labelAudioCodec->setText(QApplication::translate("AdvancedInfoDialog", "Audio Codec:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("AdvancedInfoDialog", "Video Codec", 0, QApplication::UnicodeUTF8));
        labelVideoCodec->setText(QApplication::translate("AdvancedInfoDialog", "Video Codec:", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("AdvancedInfoDialog", "Audio Device", 0, QApplication::UnicodeUTF8));
        labelAudioDevice->setText(QApplication::translate("AdvancedInfoDialog", "Audio Device:", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("AdvancedInfoDialog", "Video Device", 0, QApplication::UnicodeUTF8));
        labelVideoDevice->setText(QApplication::translate("AdvancedInfoDialog", "Audio Device:", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("AdvancedInfoDialog", "Status", 0, QApplication::UnicodeUTF8));
        labelSpeed_2->setText(QApplication::translate("AdvancedInfoDialog", "Audio codec CPU usage :", 0, QApplication::UnicodeUTF8));
        labelAudioCPU->setText(QApplication::translate("AdvancedInfoDialog", "0.0", 0, QApplication::UnicodeUTF8));
        labelSpeed_3->setText(QApplication::translate("AdvancedInfoDialog", "Video codec CPU usage :", 0, QApplication::UnicodeUTF8));
        labelVideoCPU->setText(QApplication::translate("AdvancedInfoDialog", "0.0", 0, QApplication::UnicodeUTF8));
        labelFramesCap->setText(QApplication::translate("AdvancedInfoDialog", "Frames decoded :", 0, QApplication::UnicodeUTF8));
        labelFrames->setText(QApplication::translate("AdvancedInfoDialog", "0", 0, QApplication::UnicodeUTF8));
        labelSpeed_6->setText(QApplication::translate("AdvancedInfoDialog", "A-V delay :", 0, QApplication::UnicodeUTF8));
        labelAVdealy->setText(QApplication::translate("AdvancedInfoDialog", "0.0", 0, QApplication::UnicodeUTF8));
        labelSpeed->setText(QApplication::translate("AdvancedInfoDialog", "Playback Speed:", 0, QApplication::UnicodeUTF8));
        labellSpeedFactor->setText(QApplication::translate("AdvancedInfoDialog", "1x", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AdvancedInfoDialog: public Ui_AdvancedInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVANCEDINFODIALOG_H
