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

signals:

public slots:

private:
    QMediaPlayer player;
    QString name;
    QUrl path;
    QTimer timer;
};

#endif // SOUNDITEM_H
