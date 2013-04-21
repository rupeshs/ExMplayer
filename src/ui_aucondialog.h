/********************************************************************************
** Form generated from reading UI file 'aucondialog.ui'
**
** Created: Sat Feb 26 15:50:24 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUCONDIALOG_H
#define UI_AUCONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_aucDialog
{
public:
    QGroupBox *groupBox;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QPushButton *pushButton_2;
    QPushButton *pushButtonof;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *labelst;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QPushButton *btnConv;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBox_3;
    QLabel *label_7;
    QComboBox *comboBox_4;
    QLabel *label_8;
    QPushButton *pushButton_3;

    void setupUi(QDialog *aucDialog)
    {
        if (aucDialog->objectName().isEmpty())
            aucDialog->setObjectName(QString::fromUtf8("aucDialog"));
        aucDialog->resize(576, 283);
        groupBox = new QGroupBox(aucDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 541, 101));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 20, 231, 20));
        lineEdit->setReadOnly(true);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 20, 101, 23));
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(170, 60, 272, 26));
        gridLayout = new QGridLayout(layoutWidget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        progressBar = new QProgressBar(layoutWidget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 16));
        progressBar->setMaximumSize(QSize(16777215, 16));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        gridLayout->addWidget(progressBar, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(layoutWidget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon);

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButtonof = new QPushButton(layoutWidget_2);
        pushButtonof->setObjectName(QString::fromUtf8("pushButtonof"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonof->setIcon(icon1);

        gridLayout->addWidget(pushButtonof, 0, 2, 1, 1);

        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 70, 151, 16));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        labelst = new QLabel(layoutWidget);
        labelst->setObjectName(QString::fromUtf8("labelst"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labelst);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(390, 20, 51, 21));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/arrow.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(390, 40, 71, 16));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(460, 20, 51, 22));
        btnConv = new QPushButton(groupBox);
        btnConv->setObjectName(QString::fromUtf8("btnConv"));
        btnConv->setGeometry(QRect(450, 60, 75, 23));
        groupBox_2 = new QGroupBox(aucDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(150, 150, 261, 111));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 2, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        comboBox_3 = new QComboBox(groupBox_2);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout_2->addWidget(comboBox_3, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        comboBox_4 = new QComboBox(groupBox_2);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        gridLayout_2->addWidget(comboBox_4, 2, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 2, 2, 1, 1);

        pushButton_3 = new QPushButton(aucDialog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(470, 120, 75, 23));

        retranslateUi(aucDialog);

        QMetaObject::connectSlotsByName(aucDialog);
    } // setupUi

    void retranslateUi(QDialog *aucDialog)
    {
        aucDialog->setWindowTitle(QApplication::translate("aucDialog", "Audio converter", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("aucDialog", "Select File", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("aucDialog", "Open Video File...", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("aucDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        pushButtonof->setText(QApplication::translate("aucDialog", "&Open output", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("aucDialog", "Status:", 0, QApplication::UnicodeUTF8));
        labelst->setText(QApplication::translate("aucDialog", "Ready", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_2->setText(QApplication::translate("aucDialog", "Convert to", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("aucDialog", "aac", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("aucDialog", "ac3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("aucDialog", "amr", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("aucDialog", "mmf", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("aucDialog", "mp2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("aucDialog", "mp3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("aucDialog", "ogg", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("aucDialog", "wav", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("aucDialog", "wma", 0, QApplication::UnicodeUTF8)
         << QString()
        );
        btnConv->setText(QApplication::translate("aucDialog", "Convert", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("aucDialog", "Options", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("aucDialog", "Sampling frequency:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("aucDialog", "Hz", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("aucDialog", "Channels :", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("aucDialog", "Bitrate :", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("aucDialog", "kbps", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("aucDialog", "Details>>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class aucDialog: public Ui_aucDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUCONDIALOG_H
