/*  exmplayer, GUI front-end for mplayer.
    Copyright (C) 2010-2020 Rupesh Sreeraman

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "urldialog.h"
#include "ui_urldialog.h"
#include <QCompleter>
#include <QMessageBox>
UrlDialog::UrlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UrlDialog)
{
    ui->setupUi(this);
    ui->comboBox->setLineEdit(ui->lineEdit);


}

UrlDialog::~UrlDialog()
{
    delete ui;
}

void UrlDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UrlDialog::on_lineEdit_returnPressed()
{

}

void UrlDialog::on_buttonBox_accepted()
{
    if (!ui->comboBox->currentText().isEmpty())
    {
        wordList<<ui->lineEdit->text();
        QCompleter *completer = new QCompleter(wordList, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setCompletionMode(QCompleter::PopupCompletion);
        ui->comboBox->setCompleter(completer);
        ui->comboBox->addItem(ui->comboBox->currentText());
        emit playurl(ui->comboBox->currentText());

    }
 else
    {
      QMessageBox::information(this,qApp->applicationName(),tr("Please enter a url!"),QMessageBox::Ok,QMessageBox::Cancel);
    }
}
