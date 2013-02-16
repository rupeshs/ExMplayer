/********************************************************************************
** Form generated from reading UI file 'cutterdialog.ui'
**
** Created: Sun Feb 10 12:58:35 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUTTERDIALOG_H
#define UI_CUTTERDIALOG_H

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
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "rphslider.h"

QT_BEGIN_NAMESPACE

class Ui_cutterDialog
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonStart;
    QLineEdit *lineEditStart;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonStop;
    QLineEdit *lineEditStop;
    QPushButton *pushButtonCut;
    QLabel *label_2;
    QLineEdit *lineEditLen;
    QPushButton *pushButtonpre;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonof;
    QPushButton *pushButtonclose;
    QPushButton *pushButton_2;
    QPushButton *pushButtonhelp;
    QWidget *layoutWidget2;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *labelst;
    QProgressBar *progressBar;
    QGroupBox *groupBox;
    QLabel *vid;
    rphSlider *seek;
    QToolButton *toolButtonStop;

    void setupUi(QDialog *cutterDialog)
    {
        if (cutterDialog->objectName().isEmpty())
            cutterDialog->setObjectName(QString::fromUtf8("cutterDialog"));
        cutterDialog->resize(550, 194);
        cutterDialog->setMinimumSize(QSize(550, 194));
        cutterDialog->setMaximumSize(QSize(550, 194));
        label = new QLabel(cutterDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 51, 71));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/mediacutter.png")));
        layoutWidget = new QWidget(cutterDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 20, 271, 85));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonStart = new QPushButton(layoutWidget);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));

        gridLayout->addWidget(pushButtonStart, 0, 0, 1, 1);

        lineEditStart = new QLineEdit(layoutWidget);
        lineEditStart->setObjectName(QString::fromUtf8("lineEditStart"));
        lineEditStart->setReadOnly(true);

        gridLayout->addWidget(lineEditStart, 0, 1, 1, 1);

        pushButtonReset = new QPushButton(layoutWidget);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonReset->setIcon(icon);

        gridLayout->addWidget(pushButtonReset, 0, 2, 1, 1);

        pushButtonStop = new QPushButton(layoutWidget);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));

        gridLayout->addWidget(pushButtonStop, 1, 0, 1, 1);

        lineEditStop = new QLineEdit(layoutWidget);
        lineEditStop->setObjectName(QString::fromUtf8("lineEditStop"));
        lineEditStop->setReadOnly(true);

        gridLayout->addWidget(lineEditStop, 1, 1, 1, 1);

        pushButtonCut = new QPushButton(layoutWidget);
        pushButtonCut->setObjectName(QString::fromUtf8("pushButtonCut"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/mediacutter.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCut->setIcon(icon1);
        pushButtonCut->setIconSize(QSize(16, 16));

        gridLayout->addWidget(pushButtonCut, 1, 2, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEditLen = new QLineEdit(layoutWidget);
        lineEditLen->setObjectName(QString::fromUtf8("lineEditLen"));
        lineEditLen->setReadOnly(true);

        gridLayout->addWidget(lineEditLen, 2, 1, 1, 1);

        pushButtonpre = new QPushButton(layoutWidget);
        pushButtonpre->setObjectName(QString::fromUtf8("pushButtonpre"));

        gridLayout->addWidget(pushButtonpre, 2, 2, 1, 1);

        layoutWidget1 = new QWidget(cutterDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 130, 334, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonof = new QPushButton(layoutWidget1);
        pushButtonof->setObjectName(QString::fromUtf8("pushButtonof"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonof->setIcon(icon2);

        horizontalLayout->addWidget(pushButtonof);

        pushButtonclose = new QPushButton(layoutWidget1);
        pushButtonclose->setObjectName(QString::fromUtf8("pushButtonclose"));

        horizontalLayout->addWidget(pushButtonclose);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon3);
        pushButton_2->setDefault(true);

        horizontalLayout->addWidget(pushButton_2);

        pushButtonhelp = new QPushButton(layoutWidget1);
        pushButtonhelp->setObjectName(QString::fromUtf8("pushButtonhelp"));

        horizontalLayout->addWidget(pushButtonhelp);

        layoutWidget2 = new QWidget(cutterDialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 170, 211, 16));
        formLayout = new QFormLayout(layoutWidget2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        labelst = new QLabel(layoutWidget2);
        labelst->setObjectName(QString::fromUtf8("labelst"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labelst);

        progressBar = new QProgressBar(cutterDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(440, 170, 101, 16));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        groupBox = new QGroupBox(cutterDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(350, 10, 191, 151));
        vid = new QLabel(groupBox);
        vid->setObjectName(QString::fromUtf8("vid"));
        vid->setGeometry(QRect(10, 20, 171, 91));
        vid->setStyleSheet(QString::fromUtf8("background-color: rgb(1, 0, 0);"));
        seek = new rphSlider(groupBox);
        seek->setObjectName(QString::fromUtf8("seek"));
        seek->setGeometry(QRect(20, 120, 121, 16));
        seek->setOrientation(Qt::Horizontal);
        toolButtonStop = new QToolButton(groupBox);
        toolButtonStop->setObjectName(QString::fromUtf8("toolButtonStop"));
        toolButtonStop->setGeometry(QRect(150, 120, 31, 21));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonStop->setIcon(icon4);

        retranslateUi(cutterDialog);

        QMetaObject::connectSlotsByName(cutterDialog);
    } // setupUi

    void retranslateUi(QDialog *cutterDialog)
    {
        cutterDialog->setWindowTitle(QApplication::translate("cutterDialog", "Media cutter", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        pushButtonStart->setText(QApplication::translate("cutterDialog", "Mark &start", 0, QApplication::UnicodeUTF8));
        pushButtonReset->setText(QApplication::translate("cutterDialog", "&Reset", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QApplication::translate("cutterDialog", "Mark &stop", 0, QApplication::UnicodeUTF8));
        pushButtonCut->setText(QApplication::translate("cutterDialog", "&Cut", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("cutterDialog", "Length   :", 0, QApplication::UnicodeUTF8));
        lineEditLen->setText(QApplication::translate("cutterDialog", "00:00:00", 0, QApplication::UnicodeUTF8));
        pushButtonpre->setText(QApplication::translate("cutterDialog", "&Preview", 0, QApplication::UnicodeUTF8));
        pushButtonof->setText(QApplication::translate("cutterDialog", "&Open output", 0, QApplication::UnicodeUTF8));
        pushButtonclose->setText(QApplication::translate("cutterDialog", "&Stop", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("cutterDialog", "&Ok", 0, QApplication::UnicodeUTF8));
        pushButtonhelp->setText(QApplication::translate("cutterDialog", "&Help", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("cutterDialog", "Status:", 0, QApplication::UnicodeUTF8));
        labelst->setText(QApplication::translate("cutterDialog", "Ready", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("cutterDialog", "Player", 0, QApplication::UnicodeUTF8));
        vid->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButtonStop->setToolTip(QApplication::translate("cutterDialog", "Stop", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonStop->setText(QApplication::translate("cutterDialog", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class cutterDialog: public Ui_cutterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUTTERDIALOG_H
