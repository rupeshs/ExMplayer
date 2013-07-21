/********************************************************************************
** Form generated from reading UI file 'audioextdialog.ui'
**
** Created: Sun May 5 19:33:23 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOEXTDIALOG_H
#define UI_AUDIOEXTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_audioextDialog
{
public:
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QPushButton *pex;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *labelst;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QPushButton *pushButton_2;
    QPushButton *pushButtonof;

    void setupUi(QDialog *audioextDialog)
    {
        if (audioextDialog->objectName().isEmpty())
            audioextDialog->setObjectName(QString::fromUtf8("audioextDialog"));
        audioextDialog->resize(550, 113);
        audioextDialog->setMinimumSize(QSize(550, 113));
        audioextDialog->setMaximumSize(QSize(550, 113));
        audioextDialog->setFocusPolicy(Qt::StrongFocus);
        audioextDialog->setAcceptDrops(true);
        groupBox = new QGroupBox(audioextDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 521, 63));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit);

        pex = new QPushButton(groupBox);
        pex->setObjectName(QString::fromUtf8("pex"));

        horizontalLayout->addWidget(pex);

        layoutWidget = new QWidget(audioextDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 80, 151, 19));
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

        layoutWidget_2 = new QWidget(audioextDialog);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(220, 80, 318, 29));
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


        retranslateUi(audioextDialog);

        QMetaObject::connectSlotsByName(audioextDialog);
    } // setupUi

    void retranslateUi(QDialog *audioextDialog)
    {
        audioextDialog->setWindowTitle(QApplication::translate("audioextDialog", "Audio Extractor", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("audioextDialog", "Select File", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("audioextDialog", "Open Video File...", 0, QApplication::UnicodeUTF8));
        pex->setText(QApplication::translate("audioextDialog", "&Extract", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("audioextDialog", "Status:", 0, QApplication::UnicodeUTF8));
        labelst->setText(QApplication::translate("audioextDialog", "Ready", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("audioextDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        pushButtonof->setText(QApplication::translate("audioextDialog", "&Open output", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class audioextDialog: public Ui_audioextDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOEXTDIALOG_H
