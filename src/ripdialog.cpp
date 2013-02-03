#include "ripdialog.h"
#include "ui_ripdialog.h"
#include <QTableWidgetItem>
static QRegExp rx_devid("[0-9],[0-9],[0-9]");
static QRegExp rx_toc("T0\\d+:");
static QRegExp rx_title(".*title '(.*)' from '(.*)'");

ripDialog::ripDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ripDialog)
{
    ui->setupUi(this);

    ripProcess=new MyProcess();
    ripProcess->addArgument(qApp->applicationDirPath()+"/cdda2wav.exe");
    ripProcess->start();
    QObject::connect(ripProcess,SIGNAL(lineAvailable(QByteArray)),this,SLOT(consoleLine(QByteArray)));
   // QObject::connect(ripProcess,SIGNAL(),this,SLOT());

    ui->tab->setColumnCount(3);
     //ui->tab->setAcceptDrops(true);
    QStringList headerLabels;
    headerLabels << "Title" << "Duration"<<"";
     ui->tab->setHorizontalHeaderLabels(headerLabels);
     ui->tab->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tab->setColumnWidth(0,170);
    //tab->setDragEnabled(true);
     //ui->tab->setDropIndicatorShown(true);
    //tab->viewport()->setAcceptDrops(true);
     ui->tab->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

ripDialog::~ripDialog()
{
    delete ui;
}
void ripDialog::consoleLine(QByteArray str)
{lstdrvname.clear();
    qDebug()<<str;
    QString str1;
    str1=QString(str);

  if (rx_toc.indexIn(str1) >-1 )
    {
      QStringList tmp=str1.split(QRegExp("title (\'.*\')"));
       //lsttrack<<"lengthhhhhh"<<tmp.;
      // qDebug()<<tmp.

     if (rx_title.indexIn(str1) >-1 )
     {
         qDebug()<<rx_title.cap(1)<<"yyyy";
      // qDebug()<<rx_len.cap(0).toAscii()<<"ffffffffffffff";


       ui->tab->setRowCount(ui->tab->rowCount()+1);
       QTableWidgetItem *newItem = new QTableWidgetItem(QString(rx_title.cap(1)));
       ui->tab->setItem(ui->tab->rowCount()-1, 0, newItem);
       QTableWidgetItem *newItem1 = new QTableWidgetItem(rx_title.cap(2));
       ui->tab->setItem(ui->tab->rowCount()-1, 1, newItem1);

}
    }

    if( str.contains("Removable CD-ROM"))
        {qDebug(str);
            if (rx_devid.indexIn(str) >-1 )
            {


               qDebug(rx_devid.cap(0).toAscii());
               lstdrv <<rx_devid.cap(0).toAscii();

               QString str1=str;

                 QStringList ls = str1.split(" ");
                 if  (ls.count()>2)
                {QString tmp=ls.at(1);
                     lstdrvname<<tmp.mid(1,tmp.length()-2);
                  ui->cmbDv->addItems(lstdrvname);
                 }


               // lstdrvname<<rx_devname.cap(0).toAscii();


            }

        }

}

void ripDialog::on_pushButton_clicked()
{
    //qDebug()<<ui->cmbDv->currentIndex();

ui->tab->setRowCount(0);
ui->tab->clear();
QStringList headerLabels;
headerLabels << "Title" << "Duration"<<"";
 ui->tab->setHorizontalHeaderLabels(headerLabels);
ripProcess->clearArguments();
    ripProcess->addArgument(qApp->applicationDirPath()+"/cdda2wav.exe");
    ripProcess->addArgument("dev="+lstdrv.at(ui->cmbDv->currentIndex()));
    ripProcess->addArgument("-v=toc,title");
    ripProcess->addArgument("-gui");
    ripProcess->addArgument("-info-only");
    ripProcess->start();
}

void ripDialog::on_cmbDv_currentIndexChanged(const QString &arg1)
{
}

void ripDialog::on_pushButton_2_clicked()
{
    int tnum;
    QList<QTableWidgetItem *> ni;
    ni = ui->tab->selectedItems();
    ripProcess->clearArguments();
    // tab->item(currentIndex,2)->data(Qt::DisplayRole).toString();
    ripProcess->addArgument(qApp->applicationDirPath()+"/cdda2wav.exe");
    ripProcess->addArgument("dev="+lstdrv.at(ui->cmbDv->currentIndex()));

    ripProcess->addArgument("verbose-level=summary");
    ripProcess->addArgument("-gui");
    ripProcess->addArgument("-bulk");
    ripProcess->addArgument("-no-infofile");
    ripProcess->addArgument("track="+QString::number(tnum+1)+"+"+QString::number(tnum+1)+"- ");
    ripProcess->addArgument("|\"D:/cdrtfe/tools/sound/lame.exe\"");
   //ripProcess->addArgument("--presetstandard");

    ripProcess->addArgument("--nohist");
    //ripProcess->addArgument("--add-id3v2");
    //ripProcess->addArgument("--tt "+ui->tab->item(tnum,0)->data(Qt::DisplayRole).toString());
   // ripProcess->addArgument("--ta "+ui->tab->item(tnum,1)->data(Qt::DisplayRole).toString());
    ripProcess->addArgument("- C:/Documents and Settings/Rupesh/My Documents/My Music/track_02.mp3");
    qDebug()<<  ripProcess->arguments();
    ripProcess->start();
}
