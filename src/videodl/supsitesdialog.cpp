#include "supsitesdialog.h"
#include "ui_supsitesdialog.h"

SupSitesDialog::SupSitesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::supSitesDialog)
{
    ui->setupUi(this);
    bkCount=0;
}

SupSitesDialog::~SupSitesDialog()
{
    delete ui;
}
void SupSitesDialog::addSite(QString serviceName)
{
    new QListWidgetItem(serviceName ,ui->listWidget);
    if (serviceName.toUpper().contains("BROKEN"))
    {bkCount++;
    }

    ui->labelSiteCount->setText("Working services:"+QString::number(ui->listWidget->count())+"<br><font color=\"red\">Broken:" +QString::number(bkCount)+"</font>");
}
