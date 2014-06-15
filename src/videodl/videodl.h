#ifndef VIDEODL_H
#define VIDEODL_H

#include <QMainWindow>

#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <youtubedlfe.h>
#include <vdlsettingsdialog.h>
#include <QPointer>
#include <QListWidget>
#include <supsitesdialog.h>
#include <QProgressIndicator.h>

//[download]  32.2% of 3.95MiB at 136.61KiB/s ETA 00:20"
//format code extension resolution  note
static QRegExp rx_pro("[download].*(\\d+.\\d+)%.*");
static QRegExp rx_fmt("format.*code.*extension.*resolution.*note.*");
namespace Ui {
class Videodl;
}

class Videodl : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Videodl(QWidget *parent = 0);
    ~Videodl();
   public slots:
    void ydlConsole(QByteArray);
    void emitProcessFinished(int);
private slots:
    void on_pushButtonChkFormats_clicked();

    void on_pushButtonDwnload_clicked();
    void initYoutubeDl(QString ydlPath,QString videoUrl);

    void on_pushButtonCancel_clicked();

    void on_lineEditVurl_textChanged(const QString &arg1);

    void on_toolButtonSettings_clicked();

    void on_toolButton_clicked();

    void on_pushButtonUpdate_clicked();

private:
    Ui::Videodl *ui;
    QPointer<YoutubedlFe> ydlFe;
    VdlSettingsDialog *settingDlg;
    bool formatsFound;
    bool isdownloading;
    bool blistExtrators;
    bool isUpdating;
    SupSitesDialog *supDlg;
    QProgressIndicator *pgIndicator;
};

#endif // VIDEODL_H
