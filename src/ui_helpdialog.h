/********************************************************************************
** Form generated from reading UI file 'helpdialog.ui'
**
** Created: Sun Mar 31 23:00:55 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_helpDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QListWidget *listWidgetContent;
    QTextEdit *textEditHelp;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *helpDialog)
    {
        if (helpDialog->objectName().isEmpty())
            helpDialog->setObjectName(QString::fromUtf8("helpDialog"));
        helpDialog->resize(330, 426);
        gridLayout_2 = new QGridLayout(helpDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        listWidgetContent = new QListWidget(helpDialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/player.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidgetContent);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/audio.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidgetContent);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/video.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidgetContent);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/subtitle.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidgetContent);
        __qlistwidgetitem3->setIcon(icon3);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/Internet.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidgetContent);
        __qlistwidgetitem4->setIcon(icon4);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/keyboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidgetContent);
        __qlistwidgetitem5->setIcon(icon5);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/mouse.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(listWidgetContent);
        __qlistwidgetitem6->setIcon(icon6);
        listWidgetContent->setObjectName(QString::fromUtf8("listWidgetContent"));
        listWidgetContent->setMaximumSize(QSize(181, 16777215));
        listWidgetContent->setStyleSheet(QString::fromUtf8("QListView {\n"
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
        listWidgetContent->setIconSize(QSize(32, 32));

        gridLayout->addWidget(listWidgetContent, 0, 0, 1, 1);

        textEditHelp = new QTextEdit(helpDialog);
        textEditHelp->setObjectName(QString::fromUtf8("textEditHelp"));
        textEditHelp->setReadOnly(true);

        gridLayout->addWidget(textEditHelp, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(helpDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(helpDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), helpDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(helpDialog);
    } // setupUi

    void retranslateUi(QDialog *helpDialog)
    {
        helpDialog->setWindowTitle(QApplication::translate("helpDialog", "ExMplayer- Help", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidgetContent->isSortingEnabled();
        listWidgetContent->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetContent->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("helpDialog", "Player", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetContent->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("helpDialog", "Audio", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidgetContent->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("helpDialog", "Video", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidgetContent->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("helpDialog", "Subtitles", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listWidgetContent->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("helpDialog", "Network Streaming", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem5 = listWidgetContent->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("helpDialog", "Keyboard", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem6 = listWidgetContent->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("helpDialog", "Mouse", 0, QApplication::UnicodeUTF8));
        listWidgetContent->setSortingEnabled(__sortingEnabled);

        textEditHelp->setDocumentTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class helpDialog: public Ui_helpDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPDIALOG_H
