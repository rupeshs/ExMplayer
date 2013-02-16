/********************************************************************************
** Form generated from reading UI file 'midialog.ui'
**
** Created: Sun Feb 10 12:58:35 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIDIALOG_H
#define UI_MIDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_miDialog
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btncov;
    QPushButton *pushButton;
    QPushButton *pushButton_3;

    void setupUi(QDialog *miDialog)
    {
        if (miDialog->objectName().isEmpty())
            miDialog->setObjectName(QString::fromUtf8("miDialog"));
        miDialog->resize(272, 385);
        miDialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(miDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEdit = new QTextEdit(miDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btncov = new QPushButton(miDialog);
        btncov->setObjectName(QString::fromUtf8("btncov"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/filesave .png"), QSize(), QIcon::Normal, QIcon::Off);
        btncov->setIcon(icon);

        horizontalLayout->addWidget(btncov);

        pushButton = new QPushButton(miDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(75, 23));
        pushButton->setMaximumSize(QSize(75, 23));
        pushButton->setIcon(icon);

        horizontalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(miDialog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(75, 23));
        pushButton_3->setMaximumSize(QSize(75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon1);
        pushButton_3->setDefault(true);

        horizontalLayout->addWidget(pushButton_3);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);


        retranslateUi(miDialog);

        QMetaObject::connectSlotsByName(miDialog);
    } // setupUi

    void retranslateUi(QDialog *miDialog)
    {
        miDialog->setWindowTitle(QApplication::translate("miDialog", "Media Info", 0, QApplication::UnicodeUTF8));
        btncov->setText(QApplication::translate("miDialog", "Save &Cover", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("miDialog", "&Save As..", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("miDialog", "&Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class miDialog: public Ui_miDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIDIALOG_H
