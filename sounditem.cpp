#include "sounditem.h"

SoundItem::SoundItem(QObject *parent, QUrl path) : QObject(parent)
{
    if(path.isValid()){
        this->name = path.fileName();
        player.setMedia(path);
        player.setVolume(100);
        player.setMuted(0);
        connect(&timer, SIGNAL(timeout()), this, SLOT(play()));
    } else {
        QMessageBox error;
        malformed = true;
        error.setWindowTitle("Error opening file");
        error.setText("Invalid URL");
        error.addButton(new QPushButton("OK"), QMessageBox::YesRole);
        error.exec();
    }
}

QString SoundItem::getName(){
    return name;
}

void SoundItem::play(){
    player.play();
    startTimer();
}

void SoundItem::setMute(bool mute){
    player.setMuted(mute);
}

void SoundItem::setVolume(int sliderValue){
    qreal linearVolume = QAudio::convertVolume(sliderValue / double(100.0),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);
    player.setVolume(qRound(linearVolume * 100));
}

void SoundItem::setMTTH(int value){
    mtth = value;
    stop();
    startTimer();
}

void SoundItem::startTimer(){
    QRandomGenerator rng;
    rng.seed(static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay()+index));
    int i = 0;
    double irwinHall = 0;       //Irwin-Hall distribution is used for now because I skipped math class and can't think of a more suitable one
    for(i = 0; i < 32; i++){
        double uniform = rng.generateDouble();
        irwinHall += uniform;
    }
    timer.setInterval(qRound(mtth*1000*irwinHall/16));
    timer.start();
}

void SoundItem::clearPlaying(){
    player.stop();
}

void SoundItem::stop(){
    player.stop();
    timer.stop();
}
