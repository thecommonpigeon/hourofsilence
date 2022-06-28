#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->soundListWidget->setColumnCount(6);   //name, play now button, is muted, volume, MTTH, delete
    ui->soundListWidget->setColumnWidth(0, qRound(ui->soundListWidget->width()*0.25));
    ui->soundListWidget->setColumnWidth(1, qRound(ui->soundListWidget->width()*0.1));
    ui->soundListWidget->setColumnWidth(2, qRound(ui->soundListWidget->width()*0.1));
    ui->soundListWidget->setColumnWidth(3, qRound(ui->soundListWidget->width()*0.25));
    ui->soundListWidget->setColumnWidth(4, qRound(ui->soundListWidget->width()*0.2));
    ui->soundListWidget->setColumnWidth(5, qRound(ui->soundListWidget->width()*0.08));
    ui->soundListWidget->horizontalHeader()->setVisible(0);
    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(openSoundFile()));
    connect(ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(startPressedSlot()));
    connect(ui->pushButtonStop, SIGNAL(clicked()), this, SLOT(stopPressedSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSoundFile(){
    QList<QUrl> paths;
    QStringList urlStrList = QFileDialog::getOpenFileNames(nullptr,
                                                           "Open",
                                                           QDir::currentPath().append("/sounds"),
                                                           "Sound files (*.mp3 *.wav *.ogg)");
    foreach (QString urlStr, urlStrList){
        QUrl path(urlStr);
        {
            if(!path.isEmpty()){
                SoundItem *newItem = new SoundItem(nullptr, path);
                if(isRunning){
                    newItem->startTimer();
                }
                if(newItem->malformed){
                    newItem->~SoundItem();
                } else {
                    soundList.append(newItem);
                    connect(ui->pushButtonStart, SIGNAL(clicked()), newItem, SLOT(startTimer()));
                    connect(ui->pushButtonStop, SIGNAL(clicked()), newItem, SLOT(stop()));
                    connect(ui->pushButtonClearPlaying, SIGNAL(clicked()), newItem, SLOT(clearPlaying()));

                    int i = ui->soundListWidget->rowCount();
                    newItem->index = i;
                    ui->soundListWidget->insertRow(i);

                    ui->soundListWidget->setItem(i, 0, new QTableWidgetItem(newItem->getName()));   //name
                    ui->soundListWidget->item(i, 0)->setToolTip("Editable name of the sound");

                    QPushButton *playNow = new QPushButton("Play now");                             //play now button
                    playNow->setToolTip("Play this sound once with set volume");
                    playNow->setObjectName("PlayNowButton");
                    connect(playNow, SIGNAL(clicked()), newItem, SLOT(play()));
                    ui->soundListWidget->setCellWidget(i, 1, playNow);

                    QCheckBox *mute = new QCheckBox("Mute");                                         //mute checkbox
                    mute->setChecked(0);
                    mute->setToolTip("Mute this sound");
                    connect(mute, SIGNAL(clicked(bool)), newItem, SLOT(setMute(bool)));
                    ui->soundListWidget->setCellWidget(i, 2, mute);

                    QSlider *vol = new QSlider;                                                      //volume slider
                    vol->setOrientation(Qt::Horizontal);
                    vol->setMaximum(100);
                    vol->setMinimum(0);
                    vol->setValue(100);
                    vol->setToolTip("Volume: 100%");
                    connect(vol, SIGNAL(valueChanged(int)), this, SLOT(setVolumeSliderTooltip(int)));
                    connect(vol, SIGNAL(valueChanged(int)), newItem, SLOT(setVolume(int)));
                    ui->soundListWidget->setCellWidget(i, 3, vol);

                    QSpinBox *mtth = new QSpinBox;                                                  //MTTH spinbox
                    mtth->setRange(10, 3600);
                    mtth->setValue(300);
                    mtth->setSuffix(" sec");
                    mtth->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
                    mtth->setToolTip("Mean time to happen for this sound. Changing this resets the timer if running");
                    connect(mtth, SIGNAL(valueChanged(int)), newItem, SLOT(setMTTH(int)));
                    ui->soundListWidget->setCellWidget(i, 4, mtth);


                    QPushButton *del = new QPushButton("Delete");                                   //delete button
                    del->setObjectName(QString("Delete%1").arg(i));                                 //sender->objectName() is used in delete slot
                    connect(del, SIGNAL(clicked()), this, SLOT(deleteSound()));
                    ui->soundListWidget->setCellWidget(i, 5, del);
                }
            }
        }
    }
}

    void MainWindow::deleteSound(){
        int i = static_cast<QPushButton*>(sender())->objectName().remove("Delete").toInt();
        ui->soundListWidget->item(i, 0)->~QTableWidgetItem();
        int j;
        for(j = 1; j < 6; j++){
            ui->soundListWidget->cellWidget(i, j)->~QWidget();
        }
        ui->soundListWidget->removeRow(i);
        soundList[i]->~SoundItem();
        soundList.removeAt(i);
        for(i = 0; i < soundList.size(); i++){
            soundList[i]->index = i;
        }
    }

    void MainWindow::setVolumeSliderTooltip(int volume){
        QSlider *slider = reinterpret_cast<QSlider*>(sender());
        slider->setToolTip(QString("Volume: %1%").arg(volume));
    }

    void MainWindow::startPressedSlot(){
        ui->labelStatus->setText("Status: Running");
        isRunning = 1;
    }

    void MainWindow::stopPressedSlot(){
        ui->labelStatus->setText("Status: Stopped");
        isRunning = 0;
    }
