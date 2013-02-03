/********************************************************************************
** Form generated from reading UI file 'radiodialog.ui'
**
** Created: Sun Dec 9 11:42:03 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RADIODIALOG_H
#define UI_RADIODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RadioDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QLabel *labStnCount;
    QLineEdit *lineEdit;

    void setupUi(QDialog *RadioDialog)
    {
        if (RadioDialog->objectName().isEmpty())
            RadioDialog->setObjectName(QString::fromUtf8("RadioDialog"));
        RadioDialog->resize(502, 136);
        buttonBox = new QDialogButtonBox(RadioDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(140, 90, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        gridLayoutWidget = new QWidget(RadioDialog);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(80, 30, 401, 51));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEditable(true);

        gridLayout->addWidget(comboBox, 1, 0, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        labStnCount = new QLabel(gridLayoutWidget);
        labStnCount->setObjectName(QString::fromUtf8("labStnCount"));
        labStnCount->setStyleSheet(QString::fromUtf8("color: rgb(100, 100, 100);"));

        gridLayout->addWidget(labStnCount, 0, 0, 1, 1);

        lineEdit = new QLineEdit(RadioDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(190, 10, 318, 20));

        retranslateUi(RadioDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RadioDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RadioDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RadioDialog);
    } // setupUi

    void retranslateUi(QDialog *RadioDialog)
    {
        RadioDialog->setWindowTitle(QApplication::translate("RadioDialog", "Internet Radio", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("RadioDialog", "Tune In", 0, QApplication::UnicodeUTF8));
        labStnCount->setText(QApplication::translate("RadioDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RadioDialog: public Ui_RadioDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RADIODIALOG_H
