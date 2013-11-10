#include "stereovinputdialog.h"
#include "ui_stereovinputdialog.h"

StereoVinputDialog::StereoVinputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StereoVinputDialog)
{
    ui->setupUi(this);
    _bstereo=false;

}

StereoVinputDialog::~StereoVinputDialog()
{
    delete ui;
}

void StereoVinputDialog::on_pushButtonOk_clicked()
{
    int mode=1;
    if (ui->radioButtonSbs->isChecked())
        mode=1;
     if (ui->radioButtonAbl->isChecked())
         mode=2;

    emit stereoInputFormat(mode);
    this->close();
}
