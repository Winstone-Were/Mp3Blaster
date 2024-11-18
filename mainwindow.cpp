#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , playlist(new QMediaPlaylist(this))
{
    ui->setupUi(this);
    player->setPlaylist(playlist);
    player->setVolume(50);
    ui->volumeSlider->setValue(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked(){
    player->play();
}

void MainWindow::on_pauseButton_clicked() {
    player->pause();
}

void MainWindow::on_stopButton_clicked() {
    player->stop();
}

void MainWindow::on_loadButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open MP3 File", QString(), "Audio Files (*.mp3)");
    if(! fileName.isEmpty()){
        QFileInfo File(fileName);
        ui->track_name->setText(File.fileName());
        playlist->clear();
        playlist->addMedia(QUrl::fromLocalFile(fileName));
        playlist->setCurrentIndex(0);
    }
}

void MainWindow::on_volumeSlider_valueChanged(int value) {
    player->setVolume(value);
}

void MainWindow::on_rateSlider_valueChanged(int value){
    double rate = value / 100.0;
    player->setPlaybackRate(rate);
}
