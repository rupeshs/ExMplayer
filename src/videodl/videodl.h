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
#include <QSettings>
#include <supsitesdialog.h>
#include <QProgressIndicator.h>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
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
    explicit Videodl(QWidget *parent ,QSettings *settings);
    ~Videodl();
   public slots:
    void ydlConsole(QByteArray);
    void emitProcessFinished(int);
    void animateUi();
private slots:
    void on_pushButtonChkFormats_clicked();

    void on_pushButtonDwnload_clicked();
    void initYoutubeDl(QString ydlPath,QString videoUrl);

    void on_pushButtonCancel_clicked();

    void on_lineEditVurl_textChanged(const QString &arg1);

    void on_toolButtonSettings_clicked();

    void on_toolButton_clicked();

    void on_pushButtonUpdate_clicked();

    //get youtube-dl path it varies
    QString getYoutubeDlPath();
    //ger download path default my video
    QString getDownloadPath();

    void initDownload();

    void on_pushButtonOpenOutput_clicked();
    void on_toolButtonSupFormats_clicked();

signals:
    void showfile(QString opt,QString fn);
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
    QSettings *_settings;
};

#endif // VIDEODL_H
