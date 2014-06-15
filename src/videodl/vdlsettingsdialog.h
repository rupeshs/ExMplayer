#ifndef VDLSETTINGSDIALOG_H
#define VDLSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class vdlSettingsDialog;
}

class VdlSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit VdlSettingsDialog(QWidget *parent = 0);
    ~VdlSettingsDialog();
    
private:
    Ui::vdlSettingsDialog *ui;
};

#endif // VDLSETTINGSDIALOG_H
