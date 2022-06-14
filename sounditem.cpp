#include "sounditem.h"

SoundItem::SoundItem(QObject *parent, QUrl path) : QObject(parent)
{
    if(path.isLocalFile() && path.isValid()){
        this->name = path.fileName();
        player.setMedia(path);
        player.setVolume(100);
        player.setMuted(0);
    } else {
        QMessageBox error;
        error.setWindowTitle("Error opening file");
        error.setText("Invalid URL");
        error.addButton(new QPushButton("OK"), QMessageBox::YesRole);
        error.exec();
        this->~SoundItem();
    }
}
