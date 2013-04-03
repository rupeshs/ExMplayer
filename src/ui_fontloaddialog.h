/********************************************************************************
** Form generated from reading UI file 'fontloaddialog.ui'
**
** Created: Thu Apr 4 00:41:49 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FONTLOADDIALOG_H
#define UI_FONTLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_fontLoadDialog
{
public:
    QLabel *label_3;
    QProgressBar *progressBar;

    void setupUi(QDialog *fontLoadDialog)
    {
        if (fontLoadDialog->objectName().isEmpty())
            fontLoadDialog->setObjectName(QString::fromUtf8("fontLoadDialog"));
        fontLoadDialog->resize(179, 59);
        fontLoadDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 250, 255);"));
        label_3 = new QLabel(fontLoadDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 171, 16));
        label_3->setStyleSheet(QString::fromUtf8(""));
        progressBar = new QProgressBar(fontLoadDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 30, 161, 16));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar { \n"
"border: 1px solid lightblue;\n"
"border-radius: 5px;\n"
"background-color:#ffffff;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"background-color:qlineargradient(spread:pad, x1:0.955, y1:1, x2:0.914318, y2:0.057, stop:0 rgba(0, 205, 248, 150), stop:1 rgba(255, 255, 255, 100));\n"
"width: 20px;\n"
"\n"
"}"));
        progressBar->setMaximum(0);
        progressBar->setValue(-1);

        retranslateUi(fontLoadDialog);

        QMetaObject::connectSlotsByName(fontLoadDialog);
    } // setupUi

    void retranslateUi(QDialog *fontLoadDialog)
    {
        fontLoadDialog->setWindowTitle(QApplication::translate("fontLoadDialog", "Scan fonts", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("fontLoadDialog", "Building font cache...Please wait", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class fontLoadDialog: public Ui_fontLoadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FONTLOADDIALOG_H
