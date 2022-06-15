#ifndef SOUNDITEM_H
#define SOUNDITEM_H

#include <QtCore>
#include <QtWidgets>
#include <QtMultimedia>

class SoundItem : public QObject
{
    Q_OBJECT
public:
    explicit SoundItem(QObject *parent = nullptr, QUrl path = QUrl(""));
    QString getName();
    bool malformed = false;
    int index;          //required for rng seeding

signals:

public slots:
    void play();
    void setMute(bool mute);
    void setVolume(int sliderValue);
    void setMTTH(int value);
    void startTimer();
    void clearPlaying();
    void stop();

private:
    QMediaPlayer player;
    QUrl path;
    QString name;
    QTimer timer;
    int mtth = 300;
};

#endif // SOUNDITEM_H
