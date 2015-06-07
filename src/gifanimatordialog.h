#ifndef GIFANIMATORDIALOG_H
#define GIFANIMATORDIALOG_H

#include <QDialog>
#include <mplayerfe.h>
#include "gifgenerator.h"
#include "gifpalettegenerator.h"
#include "rphfile.h"
#include "filefilters.h"
#include <QMovie>
namespace Ui {
class GifAnimatorDialog;
}

class GifAnimatorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GifAnimatorDialog(QWidget *parent ,mplayerfe *mpf);
    ~GifAnimatorDialog();
    QString filepath;
    
private:
    Ui::GifAnimatorDialog *ui;
     QPointer<mplayerfe> mp;
     float startPos;
     float stopPos;
     QString outPath;
     QPointer<GifPaletteGenerator> gifPalettteGen;
     QPointer<GifGenerator> gifGene;
     QMovie *movie;

signals:
    void showfile(QString opt,QString fn);
private slots:

    void on_pushButtonOpenFolder_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonAnimate_clicked();
    void triggerGifGenerator(int ec);
    void ProcessingCompleted(int ec);
    void on_pushButtonReset_clicked();
};

#endif // GIFANIMATORDIALOG_H
