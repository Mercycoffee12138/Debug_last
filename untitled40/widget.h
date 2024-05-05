#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QTimer>
#include<QList>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include<QMediaPlayer>
#include"fuxian.h"
#include"awula.h"
#include"Introduce.h"
#include"OUT.h"
#include"END.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //Howtoplay*howto=new Howtoplay;
    Introduce*intro=new Introduce;
    OUT*die=new OUT;
    END*ed=new END;

    //人物移动
    void fufuMove();
    //按键事件
    void keyPressEvent(QKeyEvent*event);
    void keyReleaseEvent(QKeyEvent*event);

    void player_facingside();
    void player_gravity();
    void attckingmagiccontroller();

    void normalattackingmagic();

    void flyingmagic();
    void normaldefensemagic();
    void appearance();
    void defensemagic();
    void rushing();

    void CreatEnemy();

    void Enemyattckingmagic_right();
    void Enemyattckingmagic_left();
    void fuxiandefensemagic();
    void fuxiandefensemagicover();
    void violinistattcking();
    void violinistappearance();


    void Collision_fuxian();
    void Collision_fufu();
    void Collision_soldier();
    void Collision_awula();

    void start();
    void backgroundchange();
    void Speedchange();

    void fufu_die();
    void happenagain();

private:
    Ui::Widget *ui;
   // Ui::Howtoplay*howto;

    double background_Speed=-0.8;
    double cloud_Speed=-0.8;
    double fufu_Speed=1.5;
    double gravity=1;

    QGraphicsView mGameview;
    QGraphicsScene mScene;
    QGraphicsScene gamestart;

    int fufu_life=50;
    int boss2_life=15;
    int fuxian_life=10;


    Player fufuplayer;
    fuxian *boss1=new fuxian;
    awula *boss2=new awula;
    bool facingside=true;
    bool shoot=false;
    bool flying_condition=false;
    bool flying_switch=false;
    bool defense_condition=false;
    bool defense_switch=false;
    bool attackingmagic_controller=false;
    bool rushing_condition=false;
    bool rushing_switch=true;

    bool the_first=true;
    bool the_second=false;
    bool end_switch=true;

    bool fuxiandefense_condition[8]={false,false,false,false,false,false,false,false};
    bool start_condition=false;
    bool changeend=true;
    bool fufu_dying=false;


    QGraphicsPixmapItem mCloud;
    QGraphicsPixmapItem mGrass;
    QGraphicsPixmapItem mSky;
    QGraphicsPixmapItem background[15];
    QGraphicsPixmapItem Defensemagic;
    QGraphicsPixmapItem fuxiandefense;

    //移动定时器
    QTimer*mbackgroundTimer;
    QTimer*fufuMoveTimer;
    QTimer*fufufacingside;
    QTimer*location_restrict;
    QTimer*normalattackingmagictimer;
    QTimer*bullet_controller;
    QTimer*magicmove1;
    QTimer*magicmove2;
    QTimer*mEnemycreatTimer;
    QTimer*mEnemymove;
    QTimer*flying_timer;
    QTimer*Enemyattckingmovetimer;
    QTimer*Enemyattackingcreattimer_left;
    QTimer*Enemyattackingcreattimer_right;
    QTimer*defensemagictimer;
    QTimer*defenseusedmagictimer;
    QTimer*Backgroundchangetimer;
    QTimer*fufurushingtimer;
    QTimer*Awulacollisiontimer;
    QTimer*violinlisttimer;
    QTimer*Violinlistmovetimer;
    QTimer*Speedchangetimer;
    //容器
    QList<int>mKeyList1;
    QList<Bullet*>mBulletList_left;
    QList<Bullet*>mBulletList_right;
    //QList<Bullet*>mBulletList_left2;
    //QList<Bullet*>mBulletList_right2;
    QList<Bullet*>EnemyBulletList_right;
    QList<Bullet*>EnemyBulletList_left;
    QList<Enemy*>mEnemyList_left;
    QList<Enemy*>mEnemyList_right;
    QList<fuxian*>mfuxianList;
    QList<QGraphicsPixmapItem*>DefensemagicList;
    QList<Bullet*>violinistattack;
    QList<bool>violinswitch;

    //背景音乐
    QMediaPlayer *mMeidaBG;


};
#endif // WIDGET_H
