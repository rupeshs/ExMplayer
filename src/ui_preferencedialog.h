/********************************************************************************
** Form generated from reading UI file 'preferencedialog.ui'
**
** Created: Sun May 5 19:33:23 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCEDIALOG_H
#define UI_PREFERENCEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFontComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_preferenceDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *comboBox;
    QGroupBox *groupBox_16;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QComboBox *comboBoxStyle;
    QGroupBox *groupBox_17;
    QRadioButton *radioButtonIsng;
    QRadioButton *radioButtonImul;
    QGroupBox *groupBox_18;
    QCheckBox *checkBoxRemrm;
    QWidget *page_3;
    QGroupBox *groupBox_2;
    QCheckBox *cbEnableAEq;
    QGroupBox *groupBox_4;
    QComboBox *cmbAO;
    QWidget *page;
    QGroupBox *groupBox_3;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_12;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEditSc;
    QPushButton *chScDir;
    QWidget *page_4;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_3;
    QFontComboBox *fontComboBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *spinBoxFs;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBoxBold;
    QCheckBox *checkBoxItalic;
    QGroupBox *groupBox_14;
    QWidget *widget1;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *texcol;
    QPushButton *pushButton_3;
    QLabel *label_5;
    QLineEdit *borcol;
    QPushButton *pushButton_4;
    QLabel *shdwcol;
    QLineEdit *shcol;
    QPushButton *pushButton_5;
    QGroupBox *groupBox_15;
    QGridLayout *gridLayout_7;
    QLabel *label_7;
    QComboBox *comboBoxHa;
    QLabel *label_8;
    QComboBox *comboBoxVa;
    QPushButton *pushButton_6;
    QWidget *page_5;
    QGroupBox *groupBox_5;
    QComboBox *cmbiv;
    QGroupBox *groupBox_6;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *sbNetCache;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_7;
    QSpinBox *sbNetBw;
    QGroupBox *groupBox_9;
    QSpinBox *sbseekmin;
    QGroupBox *groupBox_8;
    QSpinBox *sbNetCachemin;
    QWidget *page_6;
    QGroupBox *groupBox_10;
    QTableWidget *twsc;
    QPushButton *pushButton;
    QLabel *label_2;
    QWidget *page_7;
    QGroupBox *groupBox_11;
    QRadioButton *rbVol;
    QRadioButton *rbSk;
    QWidget *page_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *labelDate;

    void setupUi(QDialog *preferenceDialog)
    {
        if (preferenceDialog->objectName().isEmpty())
            preferenceDialog->setObjectName(QString::fromUtf8("preferenceDialog"));
        preferenceDialog->resize(620, 400);
        preferenceDialog->setMinimumSize(QSize(570, 400));
        preferenceDialog->setMaximumSize(QSize(620, 400));
        buttonBox = new QDialogButtonBox(preferenceDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(280, 360, 291, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        listWidget = new QListWidget(preferenceDialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/player.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/audio.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/video.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/subtitle.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setIcon(icon3);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/Internet.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget);
        __qlistwidgetitem4->setIcon(icon4);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/keyboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidget);
        __qlistwidgetitem5->setIcon(icon5);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/mouse.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(listWidget);
        __qlistwidgetitem6->setIcon(icon6);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(listWidget);
        __qlistwidgetitem7->setIcon(icon7);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 181, 351));
        listWidget->setStyleSheet(QString::fromUtf8(""));
        listWidget->setIconSize(QSize(32, 32));
        stackedWidget = new QStackedWidget(preferenceDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(200, 10, 421, 351));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 251, 64));
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(label);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 26));
        comboBox->setMaximumSize(QSize(16777215, 26));

        horizontalLayout_3->addWidget(comboBox);


        horizontalLayout_6->addLayout(horizontalLayout_3);

        groupBox_16 = new QGroupBox(page_2);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        groupBox_16->setGeometry(QRect(10, 70, 251, 65));
        horizontalLayout_7 = new QHBoxLayout(groupBox_16);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(groupBox_16);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(44, 16777215));

        horizontalLayout_2->addWidget(label_6);

        comboBoxStyle = new QComboBox(groupBox_16);
        comboBoxStyle->setObjectName(QString::fromUtf8("comboBoxStyle"));

        horizontalLayout_2->addWidget(comboBoxStyle);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        groupBox_17 = new QGroupBox(page_2);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        groupBox_17->setGeometry(QRect(10, 200, 351, 41));
        radioButtonIsng = new QRadioButton(groupBox_17);
        radioButtonIsng->setObjectName(QString::fromUtf8("radioButtonIsng"));
        radioButtonIsng->setGeometry(QRect(30, 20, 82, 17));
        radioButtonImul = new QRadioButton(groupBox_17);
        radioButtonImul->setObjectName(QString::fromUtf8("radioButtonImul"));
        radioButtonImul->setGeometry(QRect(150, 20, 82, 17));
        groupBox_18 = new QGroupBox(page_2);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        groupBox_18->setGeometry(QRect(10, 140, 351, 51));
        groupBox_18->setFlat(false);
        groupBox_18->setCheckable(false);
        checkBoxRemrm = new QCheckBox(groupBox_18);
        checkBoxRemrm->setObjectName(QString::fromUtf8("checkBoxRemrm"));
        checkBoxRemrm->setGeometry(QRect(30, 20, 181, 16));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        groupBox_2 = new QGroupBox(page_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 60, 351, 41));
        cbEnableAEq = new QCheckBox(groupBox_2);
        cbEnableAEq->setObjectName(QString::fromUtf8("cbEnableAEq"));
        cbEnableAEq->setGeometry(QRect(10, 20, 70, 17));
        groupBox_4 = new QGroupBox(page_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 0, 351, 51));
        cmbAO = new QComboBox(groupBox_4);
        cmbAO->setObjectName(QString::fromUtf8("cmbAO"));
        cmbAO->setGeometry(QRect(20, 20, 311, 26));
        stackedWidget->addWidget(page_3);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        groupBox_3 = new QGroupBox(page);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 0, 351, 51));
        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(20, 20, 331, 26));
        groupBox_12 = new QGroupBox(page);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setGeometry(QRect(10, 60, 361, 56));
        widget = new QWidget(groupBox_12);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(17, 25, 331, 31));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        lineEditSc = new QLineEdit(widget);
        lineEditSc->setObjectName(QString::fromUtf8("lineEditSc"));
        lineEditSc->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEditSc);

        chScDir = new QPushButton(widget);
        chScDir->setObjectName(QString::fromUtf8("chScDir"));

        horizontalLayout_4->addWidget(chScDir);

        stackedWidget->addWidget(page);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        groupBox_13 = new QGroupBox(page_4);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        groupBox_13->setGeometry(QRect(0, 0, 221, 161));
        gridLayout_3 = new QGridLayout(groupBox_13);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        fontComboBox = new QFontComboBox(groupBox_13);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));

        gridLayout_3->addWidget(fontComboBox, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(groupBox_13);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBoxFs = new QSpinBox(groupBox_13);
        spinBoxFs->setObjectName(QString::fromUtf8("spinBoxFs"));
        spinBoxFs->setMinimum(1);

        horizontalLayout->addWidget(spinBoxFs);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        checkBoxBold = new QCheckBox(groupBox_13);
        checkBoxBold->setObjectName(QString::fromUtf8("checkBoxBold"));

        gridLayout_3->addWidget(checkBoxBold, 2, 0, 1, 1);

        checkBoxItalic = new QCheckBox(groupBox_13);
        checkBoxItalic->setObjectName(QString::fromUtf8("checkBoxItalic"));

        gridLayout_3->addWidget(checkBoxItalic, 3, 0, 1, 1);

        groupBox_14 = new QGroupBox(page_4);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        groupBox_14->setGeometry(QRect(220, 0, 171, 141));
        widget1 = new QWidget(groupBox_14);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(17, 25, 147, 91));
        gridLayout_2 = new QGridLayout(widget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        texcol = new QLineEdit(widget1);
        texcol->setObjectName(QString::fromUtf8("texcol"));
        texcol->setMinimumSize(QSize(38, 25));
        texcol->setMaximumSize(QSize(38, 25));
        QPalette palette;
        QBrush brush(QColor(170, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(236, 233, 216, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        texcol->setPalette(palette);
        texcol->setReadOnly(true);

        gridLayout_2->addWidget(texcol, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(widget1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(38, 25));
        pushButton_3->setMaximumSize(QSize(38, 16777215));

        gridLayout_2->addWidget(pushButton_3, 0, 2, 1, 1);

        label_5 = new QLabel(widget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        borcol = new QLineEdit(widget1);
        borcol->setObjectName(QString::fromUtf8("borcol"));
        borcol->setMinimumSize(QSize(38, 25));
        borcol->setMaximumSize(QSize(38, 25));
        borcol->setReadOnly(true);

        gridLayout_2->addWidget(borcol, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(widget1);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(38, 25));
        pushButton_4->setMaximumSize(QSize(38, 25));

        gridLayout_2->addWidget(pushButton_4, 1, 2, 1, 1);

        shdwcol = new QLabel(widget1);
        shdwcol->setObjectName(QString::fromUtf8("shdwcol"));

        gridLayout_2->addWidget(shdwcol, 2, 0, 1, 1);

        shcol = new QLineEdit(widget1);
        shcol->setObjectName(QString::fromUtf8("shcol"));
        shcol->setMinimumSize(QSize(38, 25));
        shcol->setMaximumSize(QSize(38, 25));
        shcol->setReadOnly(true);

        gridLayout_2->addWidget(shcol, 2, 1, 1, 1);

        pushButton_5 = new QPushButton(widget1);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(38, 25));
        pushButton_5->setMaximumSize(QSize(38, 25));

        gridLayout_2->addWidget(pushButton_5, 2, 2, 1, 1);

        groupBox_15 = new QGroupBox(page_4);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        groupBox_15->setGeometry(QRect(0, 190, 231, 101));
        gridLayout_7 = new QGridLayout(groupBox_15);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_7 = new QLabel(groupBox_15);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_7->addWidget(label_7, 0, 0, 1, 1);

        comboBoxHa = new QComboBox(groupBox_15);
        comboBoxHa->setObjectName(QString::fromUtf8("comboBoxHa"));

        gridLayout_7->addWidget(comboBoxHa, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_15);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_7->addWidget(label_8, 1, 0, 1, 1);

        comboBoxVa = new QComboBox(groupBox_15);
        comboBoxVa->setObjectName(QString::fromUtf8("comboBoxVa"));

        gridLayout_7->addWidget(comboBoxVa, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(page_4);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(290, 250, 81, 26));
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        groupBox_5 = new QGroupBox(page_5);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 10, 351, 51));
        cmbiv = new QComboBox(groupBox_5);
        cmbiv->setObjectName(QString::fromUtf8("cmbiv"));
        cmbiv->setGeometry(QRect(20, 20, 311, 26));
        groupBox_6 = new QGroupBox(page_5);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 70, 351, 56));
        widget2 = new QWidget(groupBox_6);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(17, 25, 221, 29));
        horizontalLayout_5 = new QHBoxLayout(widget2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        sbNetCache = new QSpinBox(widget2);
        sbNetCache->setObjectName(QString::fromUtf8("sbNetCache"));
        sbNetCache->setMinimum(4);
        sbNetCache->setMaximum(65535);
        sbNetCache->setValue(320);

        horizontalLayout_5->addWidget(sbNetCache);

        pushButton_2 = new QPushButton(widget2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_5->addWidget(pushButton_2);

        groupBox_7 = new QGroupBox(page_5);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 180, 151, 51));
        sbNetBw = new QSpinBox(groupBox_7);
        sbNetBw->setObjectName(QString::fromUtf8("sbNetBw"));
        sbNetBw->setGeometry(QRect(20, 20, 111, 26));
        sbNetBw->setMaximum(65535);
        sbNetBw->setValue(320);
        groupBox_9 = new QGroupBox(page_5);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(210, 130, 151, 51));
        sbseekmin = new QSpinBox(groupBox_9);
        sbseekmin->setObjectName(QString::fromUtf8("sbseekmin"));
        sbseekmin->setGeometry(QRect(10, 20, 61, 26));
        sbseekmin->setMaximum(100);
        sbseekmin->setValue(50);
        groupBox_8 = new QGroupBox(page_5);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 130, 171, 51));
        sbNetCachemin = new QSpinBox(groupBox_8);
        sbNetCachemin->setObjectName(QString::fromUtf8("sbNetCachemin"));
        sbNetCachemin->setGeometry(QRect(20, 20, 61, 26));
        sbNetCachemin->setMaximum(100);
        sbNetCachemin->setValue(50);
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        groupBox_10 = new QGroupBox(page_6);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(0, 0, 391, 341));
        twsc = new QTableWidget(groupBox_10);
        if (twsc->columnCount() < 3)
            twsc->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twsc->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twsc->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twsc->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        twsc->setObjectName(QString::fromUtf8("twsc"));
        twsc->setGeometry(QRect(10, 20, 371, 281));
        twsc->setStyleSheet(QString::fromUtf8(""));
        twsc->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twsc->setAlternatingRowColors(true);
        twsc->setSelectionMode(QAbstractItemView::SingleSelection);
        twsc->setSelectionBehavior(QAbstractItemView::SelectRows);
        twsc->setSortingEnabled(true);
        pushButton = new QPushButton(groupBox_10);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(300, 310, 75, 26));
        label_2 = new QLabel(groupBox_10);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 310, 241, 16));
        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        groupBox_11 = new QGroupBox(page_7);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(10, 10, 361, 81));
        rbVol = new QRadioButton(groupBox_11);
        rbVol->setObjectName(QString::fromUtf8("rbVol"));
        rbVol->setGeometry(QRect(70, 20, 82, 17));
        rbVol->setChecked(true);
        rbSk = new QRadioButton(groupBox_11);
        rbSk->setObjectName(QString::fromUtf8("rbSk"));
        rbSk->setGeometry(QRect(200, 20, 82, 17));
        stackedWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        label_9 = new QLabel(page_8);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 40, 51, 51));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/images/ExMplayer.png")));
        label_9->setScaledContents(true);
        label_10 = new QLabel(page_8);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(70, 20, 351, 221));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        labelDate = new QLabel(page_8);
        labelDate->setObjectName(QString::fromUtf8("labelDate"));
        labelDate->setGeometry(QRect(70, 120, 261, 16));
        stackedWidget->addWidget(page_8);

        retranslateUi(preferenceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), preferenceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), preferenceDialog, SLOT(reject()));
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));

        listWidget->setCurrentRow(0);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(preferenceDialog);
    } // setupUi

    void retranslateUi(QDialog *preferenceDialog)
    {
        preferenceDialog->setWindowTitle(QApplication::translate("preferenceDialog", "Preferences", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("preferenceDialog", "Player", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("preferenceDialog", "Audio", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("preferenceDialog", "Video", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("preferenceDialog", "Subtitles", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("preferenceDialog", "Network Streaming", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("preferenceDialog", "Keyboard", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem6 = listWidget->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("preferenceDialog", "Mouse", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem7 = listWidget->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("preferenceDialog", "About", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

#ifndef QT_NO_TOOLTIP
        groupBox->setToolTip(QApplication::translate("preferenceDialog", "Set process priority for MPlayer", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        groupBox->setWhatsThis(QApplication::translate("preferenceDialog", "Set process priority for MPlayer according to the predefined priorities available under Windows and OS/2.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupBox->setTitle(QApplication::translate("preferenceDialog", "Process Priority", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("preferenceDialog", "Priority:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("preferenceDialog", "idle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "belownormal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "abovenormal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "high", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "realtime", 0, QApplication::UnicodeUTF8)
        );
        groupBox_16->setTitle(QApplication::translate("preferenceDialog", "Style", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("preferenceDialog", "Style:", 0, QApplication::UnicodeUTF8));
        comboBoxStyle->clear();
        comboBoxStyle->insertItems(0, QStringList()
         << QApplication::translate("preferenceDialog", "windows", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "wood", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "cleanlooks", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "aqua", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "motif", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "cde", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "plastique", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "windowsxp", 0, QApplication::UnicodeUTF8)
        );
        groupBox_17->setTitle(QApplication::translate("preferenceDialog", "Instance", 0, QApplication::UnicodeUTF8));
        radioButtonIsng->setText(QApplication::translate("preferenceDialog", "Single", 0, QApplication::UnicodeUTF8));
        radioButtonImul->setText(QApplication::translate("preferenceDialog", "Multiple", 0, QApplication::UnicodeUTF8));
        groupBox_18->setTitle(QApplication::translate("preferenceDialog", "Recent file menu", 0, QApplication::UnicodeUTF8));
        checkBoxRemrm->setText(QApplication::translate("preferenceDialog", "Don't Remember files.", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("preferenceDialog", "Equalizer", 0, QApplication::UnicodeUTF8));
        cbEnableAEq->setText(QApplication::translate("preferenceDialog", "Enable", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("preferenceDialog", "Output driver", 0, QApplication::UnicodeUTF8));
        cmbAO->clear();
        cmbAO->insertItems(0, QStringList()
         << QApplication::translate("preferenceDialog", "Auto", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "Win32", 0, QApplication::UnicodeUTF8)
        );
        groupBox_3->setTitle(QApplication::translate("preferenceDialog", "Output driver", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("preferenceDialog", "Auto", 0, QApplication::UnicodeUTF8)
        );
        groupBox_12->setTitle(QApplication::translate("preferenceDialog", "Screen shot Folder", 0, QApplication::UnicodeUTF8));
        chScDir->setText(QApplication::translate("preferenceDialog", "&Change...", 0, QApplication::UnicodeUTF8));
        groupBox_13->setTitle(QApplication::translate("preferenceDialog", "Font", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("preferenceDialog", "Size  :", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinBoxFs->setToolTip(QApplication::translate("preferenceDialog", "Select size", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBoxBold->setText(QApplication::translate("preferenceDialog", "Bold", 0, QApplication::UnicodeUTF8));
        checkBoxItalic->setText(QApplication::translate("preferenceDialog", "Italic", 0, QApplication::UnicodeUTF8));
        groupBox_14->setTitle(QApplication::translate("preferenceDialog", "Colors", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("preferenceDialog", "Text:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_3->setToolTip(QApplication::translate("preferenceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Select color</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_3->setText(QApplication::translate("preferenceDialog", "...", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("preferenceDialog", "Border :", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_4->setToolTip(QApplication::translate("preferenceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Select color</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_4->setText(QApplication::translate("preferenceDialog", "...", 0, QApplication::UnicodeUTF8));
        shdwcol->setText(QApplication::translate("preferenceDialog", "Shadow:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_5->setToolTip(QApplication::translate("preferenceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Select color</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_5->setText(QApplication::translate("preferenceDialog", "...", 0, QApplication::UnicodeUTF8));
        groupBox_15->setTitle(QApplication::translate("preferenceDialog", "Alignment", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("preferenceDialog", "Horizontal:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        comboBoxHa->setToolTip(QApplication::translate("preferenceDialog", "Select horizontal alignment of subtitle", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("preferenceDialog", "Verticall:", 0, QApplication::UnicodeUTF8));
        comboBoxVa->clear();
        comboBoxVa->insertItems(0, QStringList()
         << QApplication::translate("preferenceDialog", "Bottom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "Middle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("preferenceDialog", "top", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        comboBoxVa->setToolTip(QApplication::translate("preferenceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Select vertical alignment of subtitle</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pushButton_6->setToolTip(QApplication::translate("preferenceDialog", "Reset to default subtitle settings", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_6->setText(QApplication::translate("preferenceDialog", "&Reset", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("preferenceDialog", "Network Protocol version", 0, QApplication::UnicodeUTF8));
        cmbiv->clear();
        cmbiv->insertItems(0, QStringList()
         << QApplication::translate("preferenceDialog", "ipv4", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_WHATSTHIS
        cmbiv->setWhatsThis(QApplication::translate("preferenceDialog", "Internet Protocol version,4 and 6", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupBox_6->setTitle(QApplication::translate("preferenceDialog", "Cache Size", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        sbNetCache->setWhatsThis(QApplication::translate("preferenceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Memory (in kBytes) to use when precaching a URL.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        sbNetCache->setSuffix(QApplication::translate("preferenceDialog", " KBytes", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("preferenceDialog", "&Reset", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("preferenceDialog", "BandWidth", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        sbNetBw->setWhatsThis(QApplication::translate("preferenceDialog", "Specify the maximum bandwidth for network streaming (for servers that are able to send content in different bitrates). Useful if you want to watch live streamed media behind a slow connection. With Real RTSP streaming, it is also used to set the maximum delivery bandwidth allowing faster cache filling and stream dumping.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        sbNetBw->setSuffix(QApplication::translate("preferenceDialog", " Bytes", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("preferenceDialog", "Cache seek min", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        sbseekmin->setWhatsThis(QApplication::translate("preferenceDialog", "If a seek is to be made to a position within <percentage> of the cache size from the current position, MPlayer will wait for the cache to be filled to this position rather than performing a stream seek ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        sbseekmin->setSuffix(QApplication::translate("preferenceDialog", "%", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("preferenceDialog", "Cache min", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        sbNetCachemin->setWhatsThis(QApplication::translate("preferenceDialog", "Playback will start when the cache has been filled up to <percentage> of the total.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        sbNetCachemin->setSuffix(QApplication::translate("preferenceDialog", "%", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("preferenceDialog", "Keyboard shortcut", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = twsc->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("preferenceDialog", "Action", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = twsc->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("preferenceDialog", "Name ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = twsc->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("preferenceDialog", "Shortcut", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("preferenceDialog", "&Reset All", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("preferenceDialog", "Double click and modify shortcut", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("preferenceDialog", "Mouse wheel", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        rbVol->setToolTip(QApplication::translate("preferenceDialog", "Changes the volume", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        rbVol->setText(QApplication::translate("preferenceDialog", "Volume", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        rbSk->setToolTip(QApplication::translate("preferenceDialog", "Seeks media file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        rbSk->setText(QApplication::translate("preferenceDialog", "Seek", 0, QApplication::UnicodeUTF8));
        label_9->setText(QString());
        label_10->setText(QApplication::translate("preferenceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#000000;\">ExMplayer 2</span><span style=\" font-size:14pt; font-weight:600;\">.0.0</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; mar"
                        "gin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Copyright \302\251 2010 -2013 Rupesh.S </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">&lt;rupesh.rupeshs@gmail.com&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Using Qt 4.7.4 (compiled with Qt 4.7.4)</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"
                        "\"><span style=\" font-size:8pt;\">MPlayer GUI with thumbnail seeking.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Using MPlayer Redxii-SVN-r35425-4.6.3.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\"> Copyright \302\251 2000-2013 the FFmpeg developers.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">MPlayer is copyrighted to MPlayer Team</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\""
                        " font-size:8pt;\">FFmpeg Copyright \302\251 2000-2013 the FFmpeg developers and</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">is licensed under the GPL</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Visit : </span><a href=\"http://rphmpfe.sourceforge.net\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">http://exmplayer.sourceforge.net</span></a></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        labelDate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class preferenceDialog: public Ui_preferenceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCEDIALOG_H
