#include "radiodialog.h"
#include "ui_radiodialog.h"
#include "QFile"
#include "QTextStream"
#include  "QCompleter"
#include  "QMessageBox"
RadioDialog::RadioDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RadioDialog)
{
    ui->setupUi(this);
    ui->comboBox->setLineEdit(ui->lineEdit);


    QFile  file(qApp->applicationDirPath()+"/stnlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {

    }
    else{
        QTextStream in(&file);
        QString line = in.readLine();

        while (!line.isNull()) {
            ui->comboBox->addItem(line.trimmed());
            wordList<<line;
            line = in.readLine();

        }
        file.close();
        wordList.sort();
        ui->labStnCount->setText(QString::number(wordList.count())+" Stations");
        QCompleter *completer = new QCompleter(wordList, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setMaxVisibleItems(10);
        completer->setCompletionPrefix(QString("*"));
        completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
        ui->comboBox->setCompleter(completer);

    }
}

RadioDialog::~RadioDialog()
{
    delete ui;
}

void RadioDialog::on_buttonBox_accepted()
{

}

void RadioDialog::on_pushButton_clicked()
{
    if (!ui->comboBox->currentText().isEmpty())
    {
        emit playurl(ui->comboBox->currentText());

    }
 else
    {
      QMessageBox::information(this,qApp->applicationName(),tr("Please Select a radio station!"),QMessageBox::Ok,QMessageBox::Cancel);
    }
}
