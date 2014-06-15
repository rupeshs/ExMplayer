#ifndef SUPSITESDIALOG_H
#define SUPSITESDIALOG_H

#include <QDialog>
#include <QListWidget>
namespace Ui {
class supSitesDialog;
}

class SupSitesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SupSitesDialog(QWidget *parent = 0);
    ~SupSitesDialog();

    void addSite(QString);
    
private:
    Ui::supSitesDialog *ui;
    int bkCount;
};

#endif // SUPSITESDIALOG_H
