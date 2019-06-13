#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include"enemy2.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <map>
#include <QPen>
#include <qfile.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  ,_money(2000)
  ,_hp(5)
  ,_wave(0)
  ,_win(false)
  ,_lose(false)
  ,_level(2)
  ,background(QPixmap(":/images/BeiJing.jpg"))

{
    ui->setupUi(this);



    addWayPoints();
    //loadKTowerPositions();
    loadTowerPositions();
    //loadWTowerPositions();
    _game.initWorld();


    //多媒体

    //地图更新
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);


    QTimer::singleShot(300, this, SLOT(gamestart()));


}
void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *p){
    if (_lose)
    {
        QString text ("YOU FAIL!");

        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }
    if(_win){
        QPixmap win(QPixmap(":/images/win.png"));
        QPainter p(this);
        p.drawPixmap(0,0,win);
    }

    if(_level == 1){
        QPixmap garden(background);
        QPainter gardenPainter(&garden);
        QPainter painter(this);

        foreach (const Enemy *enemy, m_enemylist)
            enemy->drawe(&gardenPainter);
        foreach (const Bullet *bullet, m_bulletList)
            bullet->draw(&gardenPainter);

        foreach (const TowerPosition &towerPos, m_towerPositionsList)
            towerPos.draw(&gardenPainter);

        foreach (const Tower *tower, m_towersList)
            tower->draw(&gardenPainter);

        drawWave(&gardenPainter);
        drawHP(&gardenPainter);
        drawPlayerGold(&gardenPainter);
        _game.show(&gardenPainter);

        painter.drawPixmap(0,0,garden);

    }
    if(_level == 2){
        background = QPixmap(":/images/bj2.jpg");
        QPixmap desert(background);
        QPainter desertPainter(&desert);

        foreach (const Enemy *enemy, m_enemylist)
            enemy->drawe(&desertPainter);
        foreach (const Bullet *bullet, m_bulletList)
            bullet->draw(&desertPainter);

        foreach (const TowerPosition &towerPos, m_towerPositionsList)
            towerPos.draw(&desertPainter);

        foreach (const Tower *tower, m_towersList)
            tower->draw(&desertPainter);


        drawWave(&desertPainter);
        drawHP(&desertPainter);
        drawPlayerGold(&desertPainter);
        _game.show(&desertPainter);
        QPainter painter(this);
        painter.drawPixmap(0, 0, desert);
    }



}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            _money -= 500;
            it->setHasTower();

            Tower *tower = new Tower(it->centerPos(), this);
            m_towersList.push_back(tower);
            update();
            break;
        }

        ++it;
    }
}

bool MainWindow::canBuyTower() const
{
    if (_money >= 500)
        return true;
    return false;
}

void MainWindow::drawPlayerGold(QPainter *p){
    QPen pen(Qt::red);
    QFont font;
    font.setPointSize(25);
    p->setFont(font);
    p->setPen(pen);
    p->drawText(QRect(200, 30, 200, 50), QString("GOLD : %1").arg(_money));
}
void MainWindow::drawHP(QPainter *painter){
    QPen pen(Qt::red);
    QFont font;
    font.setPointSize(25);
    painter->setFont(font);
     painter->setPen(pen);
     painter->drawText(QRect(600, 30, 200, 50), QString("HP: %1").arg(_hp));
}
void MainWindow::drawWave(QPainter *painter){
    QPen pen(Qt::red);
    QFont font;
    font.setPointSize(25);
     painter->setFont(font);
     painter->setPen(pen);
     painter->drawText(QRect(1000, 30, 200, 50), QString("WAVE : %1").arg(_wave));
}
//以下写的是路径添加

void MainWindow::addWayPoints(){

    if(_level == 1) {
               WayPoint *waypoint1=new WayPoint(QPoint(400,820));
               m_wayPointList.push_back(waypoint1);

               WayPoint *waypoint2=new WayPoint(QPoint(1100,800));
               m_wayPointList.push_back(waypoint2);
               waypoint2->SetNextWayPoint(waypoint1);

               WayPoint *waypoint3=new WayPoint(QPoint(1100,600));
               m_wayPointList.push_back(waypoint3);
               waypoint3->SetNextWayPoint(waypoint2);

               WayPoint *waypoint4=new WayPoint(QPoint(480,600));
               m_wayPointList.push_back(waypoint4);
               waypoint4->SetNextWayPoint(waypoint3);

               WayPoint *waypoint5=new WayPoint(QPoint(480,380));
               m_wayPointList.push_back(waypoint5);
               waypoint5->SetNextWayPoint(waypoint4);

               WayPoint *waypoint6=new WayPoint(QPoint(1120,380));
               m_wayPointList.push_back(waypoint6);
               waypoint6->SetNextWayPoint(waypoint5);

               WayPoint *waypoint7=new WayPoint(QPoint(1120,100));
               m_wayPointList.push_back(waypoint7);
               waypoint7->SetNextWayPoint(waypoint6);
    }
    if(_level == 2){
        WayPoint *waypoint1=new WayPoint(QPoint(165,920));
        m_wayPointList.push_back(waypoint1);

        WayPoint *waypoint2=new WayPoint(QPoint(1360,920));
        m_wayPointList.push_back(waypoint2);
        waypoint2->SetNextWayPoint(waypoint1);

        WayPoint *waypoint3=new WayPoint(QPoint(1360,600));
        m_wayPointList.push_back(waypoint3);
        waypoint3->SetNextWayPoint(waypoint2);

        WayPoint *waypoint4=new WayPoint(QPoint(225,600));
        m_wayPointList.push_back(waypoint4);
        waypoint4->SetNextWayPoint(waypoint3);

        WayPoint *waypoint5=new WayPoint(QPoint(225,230));
        m_wayPointList.push_back(waypoint5);
        waypoint5->SetNextWayPoint(waypoint4);

        WayPoint *waypoint6=new WayPoint(QPoint(1360,230));
        m_wayPointList.push_back(waypoint6);
        waypoint6->SetNextWayPoint(waypoint5);

        WayPoint *waypoint7=new WayPoint(QPoint(1360,80));
        m_wayPointList.push_back(waypoint7);
        waypoint7->SetNextWayPoint(waypoint6);
    }

}

void MainWindow::getMoney(int money){
    _money+= money;
}


void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::removeEnemy(Enemy *enemy){
    Q_ASSERT(enemy);
    m_enemylist.removeOne(enemy);
    delete enemy;
    if(m_enemylist.empty()){
        _wave++;
        if (!loadwave() && _level ==1)
        {
            _level ++;
           getMoney(1000);
           _hp += 2;
           game_up_level();

        }
        if(!loadwave() && _level == 2){
            _win = true;
            _level++;
    }
    }
}

bool MainWindow::loadwave(){

    if(_level == 1){
        if (_wave >= 2)
            return false;
        WayPoint *startWayPoint = m_wayPointList.back(); // 这里是个逆序的，尾部才是其实节点
        int enemyStartInterval[] = { 100, 6000, 10000};
        int enemyStartInterval2[] = { 3800, 25000 };

        for (int i = 0; i < 3; ++i)
        {
            Enemy *enemy = new Enemy(startWayPoint, this);
            m_enemylist.push_back(enemy);

            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        for(int i = 0 ;i <2 ;i++){

            Enemy *enemy2 = new Enemy2(startWayPoint, this);
             m_enemylist.push_back(enemy2);
             QTimer::singleShot(enemyStartInterval2[i], enemy2, SLOT(doActivate()));
        }
        return true;
    }
    if(_level == 2){
        if (_wave >= 3)
            return false;
        WayPoint *startWayPoint = m_wayPointList.back(); // 这里是个逆序的，尾部才是其实节点
         int enemyStartInterval[] = { 100, 8000, 25000};
        int enemyStartInterval2[] = { 4000, 13000, 15000, 2000 ,30000};

        for (int i = 0; i < 3; ++i)
        {
            Enemy *enemy = new Enemy(startWayPoint, this);
            m_enemylist.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        for(int i = 0 ;i <5 ;i++){

            Enemy *enemy2 = new Enemy2(startWayPoint, this);
             m_enemylist.push_back(enemy2);
             QTimer::singleShot(enemyStartInterval2[i], enemy2, SLOT(doActivate()));
        }
        return true;
    }
}
QList<Enemy *> MainWindow::_EnemyList() const
{
    return m_enemylist;
}

void MainWindow::updateMap(){
    foreach(Enemy *enemy,m_enemylist)
        enemy->move();
    foreach (Tower *tower,m_towersList)
        tower->checkEnemyInRange();
    update();
}

void MainWindow::losehp(int dmg){
    _hp -= dmg;
    if(_hp<=0){
        gameover();
    }
}

void MainWindow::gameover(){
    if(!_lose){
        _lose=true;
    }
}
void MainWindow::gamestart(){
    loadwave();
}

void MainWindow::game_up_level(){
        _wave = 0;
        removeall();
        loadTowerPositions();
        addWayPoints();
        loadwave();
    }

void MainWindow::loadTowerPositions(){
    if(_level == 1){
        QPoint position[]={
           QPoint(638,212),QPoint(992,214),QPoint(571,428),QPoint(357,355),QPoint(497,638),
            QPoint(1065,425),QPoint(1207,208),QPoint(992,635),QPoint(1134,850)
        };

        int n=sizeof position/sizeof position[0];
        for(int i=0;i<n;i++){
            m_towerPositionsList.push_back(position[i]);
        }
    }
    if(_level == 2){
        QPoint position[]={
           QPoint(426,301),QPoint(784,305),QPoint(1145,299),QPoint(283,687),QPoint(993,687),QPoint(636,687),QPoint(350,814),QPoint(303,400),QPoint(636,814)
        };

        int n=sizeof position/sizeof position[0];
        for(int i=0;i<n;i++){
            m_towerPositionsList.push_back(position[i]);
        }
    }

}
void MainWindow::removeall(){
        m_towersList.clear();
        m_wayPointList.clear();
        m_bulletList.clear();
        m_towerPositionsList.clear();
}
