/********************************************************************************
** Form generated from reading UI file 'mixdialog.ui'
**
** Created: Tue Apr 2 16:39:58 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIXDIALOG_H
#define UI_MIXDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mixDialog
{
public:
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *labelst;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QPushButton *pushButtonof;

    void setupUi(QDialog *mixDialog)
    {
        if (mixDialog->objectName().isEmpty())
            mixDialog->setObjectName(QString::fromUtf8("mixDialog"));
        mixDialog->resize(454, 56);
        mixDialog->setMinimumSize(QSize(0, 56));
        mixDialog->setMaximumSize(QSize(16777215, 56));
        layoutWidget = new QWidget(mixDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 161, 21));
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

        layoutWidget1 = new QWidget(mixDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(180, 20, 272, 26));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        progressBar = new QProgressBar(layoutWidget1);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 16));
        progressBar->setMaximumSize(QSize(16777215, 16));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        gridLayout->addWidget(progressBar, 0, 0, 1, 1);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        pushButtonof = new QPushButton(layoutWidget1);
        pushButtonof->setObjectName(QString::fromUtf8("pushButtonof"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonof->setIcon(icon1);

        gridLayout->addWidget(pushButtonof, 0, 2, 1, 1);


        retranslateUi(mixDialog);

        QMetaObject::connectSlotsByName(mixDialog);
    } // setupUi

    void retranslateUi(QDialog *mixDialog)
    {
        mixDialog->setWindowTitle(QApplication::translate("mixDialog", "Media Mixer", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("mixDialog", "Status:", 0, QApplication::UnicodeUTF8));
        labelst->setText(QApplication::translate("mixDialog", "Ready", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("mixDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        pushButtonof->setText(QApplication::translate("mixDialog", "&Open output", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mixDialog: public Ui_mixDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIXDIALOG_H
