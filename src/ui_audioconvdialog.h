/********************************************************************************
** Form generated from reading UI file 'audioconvdialog.ui'
**
** Created: Thu Apr 4 00:41:49 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOCONVDIALOG_H
#define UI_AUDIOCONVDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_audioconvDialog
{
public:
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QComboBox *comboBoxSr;
    QLabel *label_6;
    QComboBox *comboBoxCh;
    QLabel *label_7;
    QComboBox *comboBoxBr;
    QLabel *label_8;
    QLabel *label_5;
    QPushButton *detailsPushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBoxAfmts;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QPushButton *pushButton_2;
    QPushButton *pushButtonof;
    QFormLayout *formLayout;
    QLabel *labelst;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QPushButton *btnConv;
    QLabel *labfmt;

    void setupUi(QDialog *audioconvDialog)
    {
        if (audioconvDialog->objectName().isEmpty())
            audioconvDialog->setObjectName(QString::fromUtf8("audioconvDialog"));
        audioconvDialog->resize(595, 344);
        groupBox_2 = new QGroupBox(audioconvDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(140, 180, 251, 101));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        comboBoxSr = new QComboBox(groupBox_2);
        comboBoxSr->setObjectName(QString::fromUtf8("comboBoxSr"));

        gridLayout_2->addWidget(comboBoxSr, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        comboBoxCh = new QComboBox(groupBox_2);
        comboBoxCh->setObjectName(QString::fromUtf8("comboBoxCh"));

        gridLayout_2->addWidget(comboBoxCh, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        comboBoxBr = new QComboBox(groupBox_2);
        comboBoxBr->setObjectName(QString::fromUtf8("comboBoxBr"));

        gridLayout_2->addWidget(comboBoxBr, 2, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 2, 2, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 2, 1, 1);

        detailsPushButton = new QPushButton(audioconvDialog);
        detailsPushButton->setObjectName(QString::fromUtf8("detailsPushButton"));
        detailsPushButton->setGeometry(QRect(450, 150, 91, 23));
        detailsPushButton->setCheckable(true);
        layoutWidget = new QWidget(audioconvDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 508, 136));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(51, 21));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/arrow.png")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBoxAfmts = new QComboBox(groupBox);
        comboBoxAfmts->setObjectName(QString::fromUtf8("comboBoxAfmts"));

        horizontalLayout->addWidget(comboBoxAfmts);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 16));
        progressBar->setMaximumSize(QSize(16777215, 16));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar { \n"
"border: 2px solid lightblue;\n"
"border-radius: 5px;\n"
"\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"background-color:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 150), stop:1 rgba(255, 255, 255, 100));\n"
"width: 20px;\n"
"}"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        gridLayout->addWidget(progressBar, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon);

        gridLayout->addWidget(pushButton_2, 0, 2, 1, 1);

        pushButtonof = new QPushButton(groupBox);
        pushButtonof->setObjectName(QString::fromUtf8("pushButtonof"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonof->setIcon(icon1);

        gridLayout->addWidget(pushButtonof, 0, 3, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelst = new QLabel(groupBox);
        labelst->setObjectName(QString::fromUtf8("labelst"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labelst);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);


        gridLayout->addLayout(formLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 2, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox);

        btnConv = new QPushButton(layoutWidget);
        btnConv->setObjectName(QString::fromUtf8("btnConv"));

        horizontalLayout_2->addWidget(btnConv);

        labfmt = new QLabel(audioconvDialog);
        labfmt->setObjectName(QString::fromUtf8("labfmt"));
        labfmt->setGeometry(QRect(30, 150, 301, 16));
        labfmt->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);\n"
"font: 75 8pt \"MS Shell Dlg 2\";\n"
"font: 75 8pt \"MS Shell Dlg 2\";"));

        retranslateUi(audioconvDialog);

        QMetaObject::connectSlotsByName(audioconvDialog);
    } // setupUi

    void retranslateUi(QDialog *audioconvDialog)
    {
        audioconvDialog->setWindowTitle(QApplication::translate("audioconvDialog", "Audio Converter", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("audioconvDialog", "Options", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("audioconvDialog", "Sampling frequency:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("audioconvDialog", "Channels :", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("audioconvDialog", "Bitrate :", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("audioconvDialog", "kbps", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("audioconvDialog", "Hz", 0, QApplication::UnicodeUTF8));
        detailsPushButton->setText(QApplication::translate("audioconvDialog", " Advanced>>>  ", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("audioconvDialog", "Convert", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("audioconvDialog", "Open Audio File...", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_2->setText(QApplication::translate("audioconvDialog", "Convert to", 0, QApplication::UnicodeUTF8));
        comboBoxAfmts->clear();
        comboBoxAfmts->insertItems(0, QStringList()
         << QApplication::translate("audioconvDialog", "aac", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "ac3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "amr", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "flac", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "mmf", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "m4a", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "mp2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "mp3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "ogg", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "wav", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("audioconvDialog", "wma", 0, QApplication::UnicodeUTF8)
        );
        pushButton_2->setText(QApplication::translate("audioconvDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        pushButtonof->setText(QApplication::translate("audioconvDialog", "&Open output", 0, QApplication::UnicodeUTF8));
        labelst->setText(QApplication::translate("audioconvDialog", "Ready", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("audioconvDialog", "Status:", 0, QApplication::UnicodeUTF8));
        btnConv->setText(QApplication::translate("audioconvDialog", "Convert", 0, QApplication::UnicodeUTF8));
        labfmt->setText(QApplication::translate("audioconvDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:72; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">A</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class audioconvDialog: public Ui_audioconvDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOCONVDIALOG_H
