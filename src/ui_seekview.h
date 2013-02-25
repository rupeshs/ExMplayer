/********************************************************************************
** Form generated from reading UI file 'seekview.ui'
**
** Created: Sun Feb 17 10:50:24 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEEKVIEW_H
#define UI_SEEKVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_SeekView
{
public:
    QLabel *label;
    QLabel *frameView;
    QLabel *timedisp;

    void setupUi(QDialog *SeekView)
    {
        if (SeekView->objectName().isEmpty())
            SeekView->setObjectName(QString::fromUtf8("SeekView"));
        SeekView->resize(208, 141);
        SeekView->setWindowOpacity(0.7);
        SeekView->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(SeekView);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 128, 105));
        label->setStyleSheet(QString::fromUtf8("image: url(:/images/seekview.png);"));
        frameView = new QLabel(SeekView);
        frameView->setObjectName(QString::fromUtf8("frameView"));
        frameView->setGeometry(QRect(4, 4, 120, 90));
        frameView->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);\n"
"font: 75 10pt \"MS Shell Dlg 2\";"));
        frameView->setAlignment(Qt::AlignCenter);
        timedisp = new QLabel(SeekView);
        timedisp->setObjectName(QString::fromUtf8("timedisp"));
        timedisp->setGeometry(QRect(40, 80, 46, 13));
        timedisp->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(9, 9, 9);\n"
"font: 75 8pt \"MS Shell Dlg 2\";\n"
"border-radius: 4px;"));
        timedisp->setAlignment(Qt::AlignCenter);

        retranslateUi(SeekView);

        QMetaObject::connectSlotsByName(SeekView);
    } // setupUi

    void retranslateUi(QDialog *SeekView)
    {
        SeekView->setWindowTitle(QApplication::translate("SeekView", "Seek View", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        frameView->setText(QApplication::translate("SeekView", "Loading...", 0, QApplication::UnicodeUTF8));
        timedisp->setText(QApplication::translate("SeekView", "00:00:00", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SeekView: public Ui_SeekView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEEKVIEW_H
