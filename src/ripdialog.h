#ifndef RIPDIALOG_H
#define RIPDIALOG_H

#include <Qtcore>
#include <QDialog>
#include "myprocess.h"
namespace Ui {
    class ripDialog;
}

class ripDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ripDialog(QWidget *parent = 0);
    ~ripDialog();
    QStringList lstdrvname;
    QStringList lsttrack;
public slots:
    void consoleLine(QByteArray str);

private slots:
    void on_pushButton_clicked();

    void on_cmbDv_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

private:
    Ui::ripDialog *ui;
    QPointer <MyProcess> ripProcess;
    QStringList lstdrv;


};

#endif // RIPDIALOG_H
