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

signals:

public slots:
    void play();

private:
    QMediaPlayer player;
    QUrl path;
    QString name;
    QTimer timer;
};

#endif // SOUNDITEM_H
