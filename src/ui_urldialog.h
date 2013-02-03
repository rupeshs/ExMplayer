/********************************************************************************
** Form generated from reading UI file 'urldialog.ui'
**
** Created: Sun Jan 27 21:25:12 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_URLDIALOG_H
#define UI_URLDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_UrlDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QComboBox *comboBox;
    QLineEdit *lineEdit;

    void setupUi(QDialog *UrlDialog)
    {
        if (UrlDialog->objectName().isEmpty())
            UrlDialog->setObjectName(QString::fromUtf8("UrlDialog"));
        UrlDialog->resize(456, 105);
        UrlDialog->setMinimumSize(QSize(456, 105));
        UrlDialog->setMaximumSize(QSize(456, 105));
        buttonBox = new QDialogButtonBox(UrlDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(280, 70, 151, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(UrlDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 61, 41));
        comboBox = new QComboBox(UrlDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(90, 30, 341, 22));
        comboBox->setEditable(true);
        lineEdit = new QLineEdit(UrlDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 0, 341, 21));

        retranslateUi(UrlDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), UrlDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UrlDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UrlDialog);
    } // setupUi

    void retranslateUi(QDialog *UrlDialog)
    {
        UrlDialog->setWindowTitle(QApplication::translate("UrlDialog", "Open URL", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UrlDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/net.png\" /><span style=\" font-size:8pt;\"> URL</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UrlDialog: public Ui_UrlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_URLDIALOG_H
