#include "vdlsettingsdialog.h"
#include "ui_vdlsettingsdialog.h"

VdlSettingsDialog::VdlSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vdlSettingsDialog)
{
    ui->setupUi(this);
}

VdlSettingsDialog::~VdlSettingsDialog()
{
    delete ui;
}
