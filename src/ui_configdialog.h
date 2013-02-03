/********************************************************************************
** Form generated from reading UI file 'configdialog.ui'
**
** Created: Sun Dec 9 11:42:03 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "filechooser.h"

QT_BEGIN_NAMESPACE

class Ui_ConfigDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *recording_group;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    FileChooser *directory_edit;
    QGridLayout *gridLayout;
    QLabel *label_19;
    QComboBox *recordQualityCombo;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_21;
    QComboBox *recordFormatCombo;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *playback_group;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *player_combo;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ConfigDialog)
    {
        if (ConfigDialog->objectName().isEmpty())
            ConfigDialog->setObjectName(QString::fromUtf8("ConfigDialog"));
        ConfigDialog->resize(536, 264);
        verticalLayout = new QVBoxLayout(ConfigDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        recording_group = new QGroupBox(ConfigDialog);
        recording_group->setObjectName(QString::fromUtf8("recording_group"));
        verticalLayout_2 = new QVBoxLayout(recording_group);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(recording_group);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        directory_edit = new FileChooser(recording_group);
        directory_edit->setObjectName(QString::fromUtf8("directory_edit"));

        horizontalLayout->addWidget(directory_edit);


        verticalLayout_2->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_19 = new QLabel(recording_group);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 0, 0, 1, 1);

        recordQualityCombo = new QComboBox(recording_group);
        recordQualityCombo->setObjectName(QString::fromUtf8("recordQualityCombo"));
        recordQualityCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout->addWidget(recordQualityCombo, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        label_21 = new QLabel(recording_group);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout->addWidget(label_21, 1, 0, 1, 1);

        recordFormatCombo = new QComboBox(recording_group);
        recordFormatCombo->setObjectName(QString::fromUtf8("recordFormatCombo"));

        gridLayout->addWidget(recordFormatCombo, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(288, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addWidget(recording_group);

        playback_group = new QGroupBox(ConfigDialog);
        playback_group->setObjectName(QString::fromUtf8("playback_group"));
        verticalLayout_3 = new QVBoxLayout(playback_group);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(playback_group);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        player_combo = new QComboBox(playback_group);
        player_combo->setObjectName(QString::fromUtf8("player_combo"));

        horizontalLayout_2->addWidget(player_combo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(playback_group);

        line = new QFrame(ConfigDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        buttonBox = new QDialogButtonBox(ConfigDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(directory_edit);
        label_19->setBuddy(recordQualityCombo);
        label_21->setBuddy(recordFormatCombo);
        label_2->setBuddy(player_combo);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(directory_edit, recordQualityCombo);
        QWidget::setTabOrder(recordQualityCombo, recordFormatCombo);
        QWidget::setTabOrder(recordFormatCombo, player_combo);
        QWidget::setTabOrder(player_combo, buttonBox);

        retranslateUi(ConfigDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConfigDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConfigDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigDialog)
    {
        ConfigDialog->setWindowTitle(QApplication::translate("ConfigDialog", "Settings", 0, QApplication::UnicodeUTF8));
        recording_group->setTitle(QApplication::translate("ConfigDialog", "Recording", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConfigDialog", "&Save to this folder", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("ConfigDialog", "&Quality", 0, QApplication::UnicodeUTF8));
        recordQualityCombo->clear();
        recordQualityCombo->insertItems(0, QStringList()
         << QApplication::translate("ConfigDialog", "Normal (360p)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ConfigDialog", "HD (720p)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ConfigDialog", "Full HD (1080p)", 0, QApplication::UnicodeUTF8)
        );
        label_21->setText(QApplication::translate("ConfigDialog", "&Format", 0, QApplication::UnicodeUTF8));
        recordFormatCombo->clear();
        recordFormatCombo->insertItems(0, QStringList()
         << QApplication::translate("ConfigDialog", "MP4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ConfigDialog", "Flv", 0, QApplication::UnicodeUTF8)
        );
        playback_group->setTitle(QApplication::translate("ConfigDialog", "Playback", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConfigDialog", "&Player:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfigDialog: public Ui_ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
