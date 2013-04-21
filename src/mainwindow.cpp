#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mp=new MplayerWindow(this,0);
    mp->setColorKey(QColor(0, 0, 255, 255));
    this->setCentralWidget(mp);

    mp->showLogo(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}
