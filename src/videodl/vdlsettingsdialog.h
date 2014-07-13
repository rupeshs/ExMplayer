#ifndef VDLSETTINGSDIALOG_H
#define VDLSETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDesktopServices>
#include <QFileDialog>
namespace Ui {
class vdlSettingsDialog;
}

class VdlSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit VdlSettingsDialog(QWidget *parent ,QSettings *settings);
    ~VdlSettingsDialog();
    
private slots:


    void on_toolButtonBrFolderYdl_clicked();

    void on_toolButtonBrFolder_clicked();
    void settingChanged(QString group,QString key,QString value);
    void on_pushButtonReset_clicked();

private:
    Ui::vdlSettingsDialog *ui;
    QSettings *_settings;
    QString oPath;
};

#endif // VDLSETTINGSDIALOG_H
