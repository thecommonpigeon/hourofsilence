#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->soundList->setColumnCount(7);   //name, is enabled, play now button, MTTH, reset MTTH, volume, delete
    ui->soundList->horizontalHeader()->setVisible(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

