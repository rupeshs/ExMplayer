#ifndef STEREOVINPUTDIALOG_H
#define STEREOVINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class StereoVinputDialog;
}

class StereoVinputDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit StereoVinputDialog(QWidget *parent = 0);
    ~StereoVinputDialog();

    inline bool Stereo(){return _bstereo;} //for stereo selection dialogue
    inline void setStereo(bool b){_bstereo=b;}
signals:
    void stereoInputFormat(int mode);
    
private slots:
    void on_pushButtonOk_clicked();



private:
    Ui::StereoVinputDialog *ui;
    bool _bstereo;
};

#endif // STEREOVINPUTDIALOG_H
