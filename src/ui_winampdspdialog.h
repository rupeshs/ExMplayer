/********************************************************************************
** Form generated from reading UI file 'winampdspdialog.ui'
**
** Created: Sun Jan 27 21:25:12 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINAMPDSPDIALOG_H
#define UI_WINAMPDSPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WinampDspDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QPushButton *pushButton_2;

    void setupUi(QDialog *WinampDspDialog)
    {
        if (WinampDspDialog->objectName().isEmpty())
            WinampDspDialog->setObjectName(QString::fromUtf8("WinampDspDialog"));
        WinampDspDialog->resize(453, 336);
        WinampDspDialog->setMinimumSize(QSize(453, 336));
        WinampDspDialog->setMaximumSize(QSize(453, 336));
        buttonBox = new QDialogButtonBox(WinampDspDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(250, 290, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        label = new QLabel(WinampDspDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 151, 21));
        lineEdit = new QLineEdit(WinampDspDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(170, 20, 181, 21));
        lineEdit->setReadOnly(true);
        pushButton = new QPushButton(WinampDspDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(360, 20, 61, 21));
        listWidget = new QListWidget(WinampDspDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(30, 50, 391, 231));
        listWidget->setStyleSheet(QString::fromUtf8("QListView {\n"
"     show-decoration-selected: 1; /* make the selection span the entire width of the view */\n"
" }\n"
"\n"
" QListView::item:alternate {\n"
"     background: #EEEEEE;\n"
" }\n"
"\n"
" QListView::item:selected {\n"
"  background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 100), stop:1 rgba(255, 255, 255, 200));\n"
"\n"
"\n"
" \n"
" }\n"
"\n"
"\n"
"\n"
" QListView::item:selected:active {\n"
"    background: qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 75), stop:1 rgba(255, 255, 255, 200));\n"
"	color: rgb(0, 0, 255);\n"
"border:1px lightblue;\n"
" }\n"
"\n"
" QListView::item:hover {\n"
"     background:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 50), stop:1 rgba(255, 255, 255, 200));\n"
" }\n"
"\n"
""));
        pushButton_2 = new QPushButton(WinampDspDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(180, 294, 71, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/cancel"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon);

        retranslateUi(WinampDspDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), WinampDspDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WinampDspDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(WinampDspDialog);
    } // setupUi

    void retranslateUi(QDialog *WinampDspDialog)
    {
        WinampDspDialog->setWindowTitle(QApplication::translate("WinampDspDialog", "Winamp Dsp", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WinampDspDialog", "Winamp Dsp plugins Location :", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("WinampDspDialog", "C:\\Program Files\\Winamp\\Plugins\\", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("WinampDspDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("WinampDspDialog", "&Disable", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WinampDspDialog: public Ui_WinampDspDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINAMPDSPDIALOG_H
