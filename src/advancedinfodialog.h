#ifndef ADVANCEDINFODIALOG_H
#define ADVANCEDINFODIALOG_H

#include <QDialog>
#include "mplayerfe.h"
#include <QTimer>
namespace Ui {
class AdvancedInfoDialog;
}

class AdvancedInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AdvancedInfoDialog(QWidget *parent = 0);
    void setMPlayer(QPointer<mplayerfe> mp);
    ~AdvancedInfoDialog();
public slots:
    void updateStatus();
    
private:
    Ui::AdvancedInfoDialog *ui;
    QPointer<mplayerfe> _mp;
    QPointer<QTimer> statusTimer;
};

#endif // ADVANCEDINFODIALOG_H
