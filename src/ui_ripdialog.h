/********************************************************************************
** Form generated from reading UI file 'ripdialog.ui'
**
** Created: Sun Dec 9 11:42:03 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RIPDIALOG_H
#define UI_RIPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ripDialog
{
public:
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QComboBox *cmbDv;
    QLabel *label;
    QTableWidget *tab;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *ripDialog)
    {
        if (ripDialog->objectName().isEmpty())
            ripDialog->setObjectName(QString::fromUtf8("ripDialog"));
        ripDialog->resize(495, 324);
        layoutWidget = new QWidget(ripDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 311, 22));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        cmbDv = new QComboBox(layoutWidget);
        cmbDv->setObjectName(QString::fromUtf8("cmbDv"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cmbDv);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        tab = new QTableWidget(ripDialog);
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setGeometry(QRect(20, 60, 441, 211));
        pushButton = new QPushButton(ripDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 280, 75, 23));
        pushButton_2 = new QPushButton(ripDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(110, 280, 75, 23));

        retranslateUi(ripDialog);

        QMetaObject::connectSlotsByName(ripDialog);
    } // setupUi

    void retranslateUi(QDialog *ripDialog)
    {
        ripDialog->setWindowTitle(QApplication::translate("ripDialog", "Copy Audio CD", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ripDialog", "Select Drive        :", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ripDialog", "Read", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ripDialog", "Copy", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ripDialog: public Ui_ripDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RIPDIALOG_H
