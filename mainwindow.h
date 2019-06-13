#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include<QKeyEvent>
#include<QTimer>
#include "rpgobj.h"
#include "world.h"
#include <waypoint.h>
#include <vector>
#include <enemy.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <tower.h>
#include <towerposition.h>
#include <bullet.h>

class Enemy;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  
    void addWayPoints();

    void removeEnemy(Enemy * enemy);
    void removedBullet(Bullet *bullet);
    void removeall();

    void addBullet(Bullet *bullet);

    void drawPlayerGold(QPainter * p);
    void drawWave(QPainter *painter );
    void drawHP(QPainter *painter);

    void getMoney(int money);
    void losehp(int dmg);

    void gameover();
    void game_up_level();
    bool loadwave();

    QList<Enemy *> _EnemyList() const;

private slots:
     void updateMap();
     void gamestart();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    World                   _game;
    int                     _money=10000;
    int                     _level;
    int                     _hp;
    int                     _wave;
    bool                    _win;
    bool                    _lose;
    void                    loadTowerPositions();
    bool                    canBuyTower() const;

    QPixmap                 background;
    QList <WayPoint*>       m_wayPointList;
    QList<Enemy*>           m_enemylist;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<Bullet *>			m_bulletList;
};


#endif // MAINWINDOW_H


