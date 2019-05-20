
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include "icon.h"
#include <QTime>
#include<QTimer>
#include <map>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     this->_game.initWorld();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *p){
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/images/bg.jpg"));

    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    this->_game.show(pa);
    pa->end();
    delete pa;
}
