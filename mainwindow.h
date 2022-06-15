#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "sounditem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<SoundItem*> soundList;
    bool isRunning = 0;

public slots:
    void openSoundFile();
    void setVolumeSliderTooltip(int volume);
    void startPressedSlot();    //these 2 could be one but i'm lazy
    void stopPressedSlot();
};
#endif // MAINWINDOW_H
