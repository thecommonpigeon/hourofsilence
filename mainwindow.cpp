#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->soundListWidget->setColumnCount(7);   //name, play now button, is muted, volume, MTTH, reset MTTH, delete
    ui->soundListWidget->horizontalHeader()->setVisible(0);

    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(openSoundFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSoundFile(){
    QUrl path = QUrl(QFileDialog::getOpenFileName(nullptr,
                                                  "Open",
                                                  QDir::currentPath().append("/sounds"),
                                                  "Sound files (*.mp3 *.wav *.ogg)"));
    if(!path.isEmpty()){
        SoundItem *newItem = new SoundItem(nullptr, path);
        if(newItem->malformed){
            newItem->~SoundItem();
        } else {
            soundList.append(newItem);
            int i = ui->soundListWidget->rowCount();
            ui->soundListWidget->insertRow(i);

            ui->soundListWidget->setItem(i, 0, new QTableWidgetItem(newItem->getName()));   //name

            QPushButton *playNow = new QPushButton("Play now");                             //play now button
            ui->soundListWidget->setCellWidget(i, 1, playNow);
            connect(playNow, SIGNAL(clicked()), newItem, SLOT(play()));

            QPushButton *del = new QPushButton("Delete");                                   //delete button
            del->setObjectName(QString("Delete%1").arg(i));                                 //sender->objectName() is used in delete slot
            ui->soundListWidget->setCellWidget(i, 6, del);
        }
    }
}
