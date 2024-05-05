#include "widget.h"
#include "ui_widget.h"
#include<QPushButton>
#include<QToolButton>
#include<QTimer>
#include<QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->setupUi(this);
    this->setFixedSize(1280,720);


    mGameview.setSceneRect(QRect(0,0,1278,720));
    mScene.setSceneRect(QRect(0,0,1280,720));
    gamestart.setSceneRect(QRect(0,0,1280,720));
    gamestart.addPixmap(QPixmap(":/start/Map/start_003.png"));

    auto startbtn=new QPushButton();
    auto howtobtn=new QPushButton();
    startbtn->setFlat(true);
    startbtn->setFocusPolicy(Qt::NoFocus);
    startbtn->setIcon(QIcon(":/start/start/start_001.png"));
    howtobtn->setIcon(QIcon(":/start/start/introduction.png"));
    startbtn->setStyleSheet("border:none;");
    howtobtn->setStyleSheet("border:none;");
    startbtn->setIconSize(QSize(175,70));
    howtobtn->setIconSize(QSize(175,70));
    howtobtn->move(100,100);
    startbtn->move(100,300);
    connect(howtobtn,&QPushButton::clicked,[=](){
        this->intro->show();
    });
    connect(startbtn,&QPushButton::clicked,[this](){
        mGameview.setScene(&mScene);
        mGameview.show();
        //背景音乐
        // this->mMeidaBG=new QMediaPlayer;
        // this->mMeidaBG->setSource(QUrl("qrc:/music/Music/bgm.mp3"));
        // this->mMeidaBG->play();
    });
    connect(this->die,&OUT::back,[=](){
        this->die->hide();
        this->show();
        mGameview.setScene(&gamestart);
    });
    connect(this->die,&OUT::back,[=](){
        happenagain();
    });
    gamestart.addWidget(startbtn);
    gamestart.addWidget(howtobtn);
      connect(startbtn,&QPushButton::clicked,this,&Widget::start);



    for(int i=0;i<10;i++)
    {
        background[i].setPixmap(QPixmap(":/background/Map/background1.png"));
        mScene.addItem(&background[i]);
        background[i].setPos(1279*(i-2),0);
    }



    mCloud.setPixmap(QPixmap(":/background/Map/cloud1.png"));

    //设置位置
    mCloud.setPos(650,50);
    //player_right_001.setPos(250,340);
    //图片元素添加到场景

    mScene.addItem(&mCloud);
    mScene.addItem(&fufuplayer.fufu);

    //设置视图场景
    mGameview.setScene(&mScene);
    mGameview.setScene(&gamestart);
    mGameview.setParent(this);
    mGameview.show();

    //人物移动
    fufuMoveTimer=new QTimer(this);
    fufuMoveTimer->start(1000/144);
    connect(fufuMoveTimer,&QTimer::timeout,this,&Widget::fufuMove);
    //角色朝向
    fufufacingside=new QTimer(this);
    fufufacingside->start(1000/144);
    connect(fufufacingside,&QTimer::timeout,this,&Widget::player_facingside);
    connect(fufufacingside,&QTimer::timeout,this,&Widget::player_gravity);

    //fufu攻击子弹生成
    normalattackingmagictimer=new QTimer(this);
    normalattackingmagictimer->start(1000/144);
    connect(normalattackingmagictimer,&QTimer::timeout,this,&Widget::normalattackingmagic);

    bullet_controller=new QTimer(this);
    bullet_controller->start(1000/144);
    connect(bullet_controller,&QTimer::timeout,this,&Widget:: attckingmagiccontroller);

    //子弹移动
    magicmove1=new QTimer(this);
    magicmove1->start(1000/144);
    connect(magicmove1,&QTimer::timeout,[this](){
        for(auto bullet:mBulletList_right)
        {
            bullet->BulletMove_right();
        }
        for(auto bullet:mBulletList_left)
        {
            bullet->BulletMove_left();
        }
        Collision_fuxian();
        Collision_fufu();
    });


    mEnemycreatTimer=new QTimer(this);
    mEnemycreatTimer->start(9000);
    connect(mEnemycreatTimer,&QTimer::timeout,this,&Widget::CreatEnemy);

    mEnemymove=new QTimer(this);
    mEnemymove->start(1000/144);
    connect(mEnemymove,&QTimer::timeout,[this](){
        for(auto enemy:mEnemyList_left)
        {
            enemy->EnemyMove_left();
        }
        for(auto enemy:mEnemyList_right)
        {
            enemy->EnemyMove_right();
        }

    });

    flying_timer=new QTimer(this);
    flying_timer->start(1000/144);
    connect(flying_timer,&QTimer::timeout,this,&Widget::flyingmagic);
    connect(flying_timer,&QTimer::timeout,this,&Widget::appearance);

    Enemyattackingcreattimer_right=new QTimer(this);
    Enemyattackingcreattimer_right->start(90000/144);
    Enemyattackingcreattimer_left=new QTimer(this);
    Enemyattackingcreattimer_left->start(5000/144);
    connect(Enemyattackingcreattimer_left,&QTimer::timeout,this,&::Widget::Enemyattckingmagic_left);
    connect(Enemyattackingcreattimer_right,&QTimer::timeout,this,&Widget::Enemyattckingmagic_right);

    Enemyattckingmovetimer=new QTimer(this);
    Enemyattckingmovetimer->start(900/144);
    connect(Enemyattckingmovetimer,&QTimer::timeout,[this](){
        for(auto bullet:EnemyBulletList_left)
        {
            bullet->BulletMove_left();
        }
        for(auto bullet:EnemyBulletList_right)
        {
            bullet->BulletMove_right();
        }
        for(auto bullet:violinistattack)
        {
            bullet->BulletMove_left();
        }
       // Collision_soldier();
    });



    defensemagictimer=new QTimer(this);
    defensemagictimer->start(1000/144);
    connect(defensemagictimer,&QTimer::timeout,this,&Widget::normaldefensemagic);

    defenseusedmagictimer=new QTimer(this);
    defenseusedmagictimer->start(1000/144);
    connect(defenseusedmagictimer,&QTimer::timeout,this,&Widget::defensemagic);
    //connect(defensemagictimer,&QTimer::timeout,this,&Widget::fuxiandefensemagic);
    //connect(defensemagictimer,&QTimer::timeout,this,&Widget::fuxiandefensemagicover);

    Backgroundchangetimer=new QTimer(this);
    Backgroundchangetimer->start(1000/144);
    connect(Backgroundchangetimer,&QTimer::timeout,this,&Widget::backgroundchange);

    fufurushingtimer=new QTimer(this);
    fufurushingtimer->start(1000/144);
    connect(fufurushingtimer,&QTimer::timeout,this,&Widget::rushing);

    violinlisttimer=new QTimer(this);
    violinlisttimer->start(1000);
    connect(violinlisttimer,&QTimer::timeout,this,&Widget::violinistattcking);

    Violinlistmovetimer=new QTimer(this);
    Violinlistmovetimer->start(1000);
    connect(Violinlistmovetimer,&QTimer::timeout,this,&Widget::violinistappearance);

    Awulacollisiontimer=new QTimer(this);
    Awulacollisiontimer->start(1000/144);
    connect(Awulacollisiontimer,&QTimer::timeout,this,&Widget::Collision_awula);

    Speedchangetimer=new QTimer(this);
    Speedchangetimer->start(1000/144);
    connect(Speedchangetimer,&QTimer::timeout,this,&Widget::Speedchange);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::fufuMove()
{
    for(int KeyCode:mKeyList1)
    {
        switch(KeyCode)
        {
        case Qt::Key_S:{
            if(the_first)
            {
            if(fufuplayer.fufu.y()+fufu_Speed>340)
                {fufuplayer.fufu.setY(340);break;}
            else
            {fufuplayer.fufu.moveBy(0,fufu_Speed);break;}
            }
            else if(the_second)
            {
                if(fufuplayer.fufu.y()+fufu_Speed>460)
                {fufuplayer.fufu.setY(460);break;}
                else
                {fufuplayer.fufu.moveBy(0,fufu_Speed);break;}}
            }
        case Qt::Key_A:{
            if(fufuplayer.fufu.x()-fufu_Speed<0)
            {fufuplayer.fufu.setX(0);
                for(int i=0;i<10;i++)
                {
                    background[i].moveBy(fufu_Speed,0);
                }
                mCloud.moveBy(fufu_Speed,0);
                break;
            }
            else
            {fufuplayer.fufu.moveBy(-fufu_Speed,0);break;}}
        case Qt::Key_D:{
            if(the_first)
            {
                if(fufuplayer.fufu.x()+fufu_Speed>450)
                {fufuplayer.fufu.setX(450);
                    for(int i=0;i<10;i++)
                    {
                        background[i].moveBy(-fufu_Speed,0);
                    }
                    mCloud.moveBy(-fufu_Speed,0);
                    break;
                }
                else{fufuplayer.fufu.moveBy(fufu_Speed,0);break;}}
            }
            if(!the_first)
            {
                if(fufuplayer.fufu.x()+fufu_Speed>798)
                {fufuplayer.fufu.setX(798);
                for(int i=0;i<10;i++)
                {
                    background[i].moveBy(-fufu_Speed,0);
                }
                mCloud.moveBy(-fufu_Speed,0);
                break;
            }
            else{fufuplayer.fufu.moveBy(fufu_Speed,0);break;}}
            }
    }

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    mKeyList1.append(event->key());
    switch(event->key())
    {
    case::Qt::Key_Y:{defense_condition=true;break;}
    case::Qt::Key_J:{flying_condition=true;break;}
    case::Qt::Key_G:{attackingmagic_controller=true;shoot=true;break;}
    case Qt::Key_A:{facingside=false;break;}
    case Qt::Key_D:{facingside=true;break;}
    case Qt::Key_R:{rushing_condition=true;break;}
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //移除按键
    switch (event->key()) {
    case::Qt::Key_Y:{defense_condition=false;break;}
    case::Qt::Key_J:{flying_condition=false;break;}
    case::Qt::Key_G:{shoot=false;break;}
    case Qt::Key_R:{rushing_condition=false;break;}
    }
    if(mKeyList1.contains(event->key()))
    {
        mKeyList1.removeOne(event->key());
    }
}

void Widget::player_facingside()
{
    if(facingside)
    {
        fufuplayer.fufu.setPixmap(QPixmap(":/player/Player/fufu_right_001.png"));
    }
    else
    {
        fufuplayer.fufu.setPixmap(QPixmap(":/player/Player/fufu_left_001.png"));
    }
}

void Widget::player_gravity()
{
    if(fufuplayer.fufu.y()<340)
    {
        fufuplayer.fufu.moveBy(0,gravity);
    }
}

void Widget::attckingmagiccontroller()
{
    if(attackingmagic_controller)
    {
        attackingmagic_controller=false;
    }
}

void Widget::normalattackingmagic()
{
    if(facingside&&shoot&&attackingmagic_controller&&!defense_condition&&!flying_condition)
    {
        //QPixmap img(":/bullet/bullet/bullets_003.png");
        QPixmap img(":/bullet/bullet/bullet_007.png");
        QPoint pos(fufuplayer.fufu.x()+182,fufuplayer.fufu.y()+17);
       // int randy=(rand()%660);
        //QPoint pos(fufuplayer.fufu.x()+132,randy);
        Bullet *bullet=new Bullet(pos,img,0);
        mScene.addItem(bullet);
        mBulletList_right.append(bullet);
    }
    else if(!facingside&&shoot&&attackingmagic_controller&&!defense_condition&&flying_condition)
    {
        QPixmap img(":/bullet/bullet/bullet_007.png");
        QPoint pos(fufuplayer.fufu.x()-100,fufuplayer.fufu.y()+30);
        Bullet *bullet=new Bullet(pos,img,0);
        mScene.addItem(bullet);
        mBulletList_left.append(bullet);
    }
    else if(facingside&&shoot&&attackingmagic_controller&&!defense_condition&&flying_condition)
    {
        QPixmap img(":/bullet/bullet/bullet_007.png");
        QPoint pos(fufuplayer.fufu.x()+270,fufuplayer.fufu.y()+30);
        Bullet *bullet=new Bullet(pos,img,0);
        mScene.addItem(bullet);
        mBulletList_right.append(bullet);
    }
    else if(!facingside&&shoot&&attackingmagic_controller&&!defense_condition&&!flying_condition)
    {
        QPixmap img(":/bullet/bullet/bullet_007.png");
        QPoint pos(fufuplayer.fufu.x(),fufuplayer.fufu.y()+17);
        Bullet *bullet=new Bullet(pos,img,0);
        mScene.addItem(bullet);
        mBulletList_left.append(bullet);
    }
}


void Widget::flyingmagic()
{
    for(int KeyCode:mKeyList1)
    {
        switch(KeyCode)
        {
        case Qt::Key_W:{
            if(flying_condition)
            {
                if(fufuplayer.fufu.y()-fufu_Speed<0)
                {
                    fufuplayer.fufu.setY(0);
                    break;
                }
                else
                {
                    fufuplayer.fufu.moveBy(0,-fufu_Speed*2);
                    break;
                }
            }
            else if(!flying_condition&&fufuplayer.fufu.y()<290)
            {
                break;
            }
            else if(!flying_condition&&fufuplayer.fufu.y()>290)
            {
                if(fufuplayer.fufu.y()>290&&fufuplayer.fufu.y()-fufu_Speed<290)
                {
                    fufuplayer.fufu.setY(290);
                    break;
                }
                else if(fufuplayer.fufu.y()<290)
                {
                    fufuplayer.fufu.setY(290);
                }
                else
                {
                    fufuplayer.fufu.moveBy(0,-fufu_Speed-gravity);
                    break;
                }
            }
        }
        }
    }
}

void Widget::normaldefensemagic()
{
    if(defense_condition&&facingside&&!flying_condition)
    {
        Defensemagic.setPixmap(QPixmap(":/bullet/bullet/defense_001.png"));
        QPoint _pos(fufuplayer.fufu.x()+200,fufuplayer.fufu.y()-20);
        Defensemagic.setPos(_pos);
        mScene.addItem(&Defensemagic);
        defense_switch=true;
    }
    else if(defense_condition&&!facingside&&!flying_condition)
      {
        Defensemagic.setPixmap(QPixmap(":/bullet/bullet/defense_003.png"));
        QPoint _pos(fufuplayer.fufu.x(),fufuplayer.fufu.y()-20);
        Defensemagic.setPos(_pos);
        mScene.addItem(&Defensemagic);
        defense_switch=true;
       }
    else if(defense_condition&&!facingside&&flying_condition)
    {
        Defensemagic.setPixmap(QPixmap(":/bullet/bullet/defense_003.png"));
        QPoint _pos(fufuplayer.fufu.x()-40,fufuplayer.fufu.y()-20);
        Defensemagic.setPos(_pos);
        mScene.addItem(&Defensemagic);
        defense_switch=true;
    }
    else if(defense_condition&&facingside&&flying_condition)
    {
        Defensemagic.setPixmap(QPixmap(":/bullet/bullet/defense_001.png"));
        QPoint _pos(fufuplayer.fufu.x()+300,fufuplayer.fufu.y()-20);
        Defensemagic.setPos(_pos);
        mScene.addItem(&Defensemagic);
        defense_switch=true;
    }
    else if(!defense_condition&&defense_switch)
    {
        mScene.removeItem(&Defensemagic);
        defense_switch=false;
    }
}

void Widget::appearance()
{
    if (flying_condition && facingside && !rushing_condition)
    {
        fufuplayer.fufu.setPixmap(QPixmap(":/player/Player/flying_condition_right.png"));
    }
    else if (flying_condition && !facingside && !rushing_condition)
    {
        fufuplayer.fufu.setPixmap(QPixmap(":/player/Player/flying_condition_left.png"));
    }
    else if (!flying_condition && facingside && !rushing_condition)
    {
        fufuplayer.fufu.setPixmap(QPixmap(":/player/Player/fufu_right_001.png"));
    }
    else if (!flying_condition && !facingside && !rushing_condition)
    {
        fufuplayer.fufu.setPixmap(QPixmap(":/player/Player/fufu_left_001.png"));
    }
    else if (rushing_condition && facingside)
    {
        fufuplayer.fufu.setPixmap(QPixmap(":/player/Player/rush_right_001.png"));
    }
    else if (rushing_condition && !facingside)
    {
        fufuplayer.fufu.setPixmap(QPixmap(":/player/Player/rush_left_001_.png"));
    }
}

void Widget::defensemagic()
{
    if(defense_condition)
    {
    for(int i=0;i<EnemyBulletList_left.size();i++)
    {
        if(EnemyBulletList_left[i]->collidesWithItem(&Defensemagic))
        {
            mScene.removeItem(EnemyBulletList_left[i]);
            EnemyBulletList_left.removeOne(EnemyBulletList_left[i]);
        }
    }
    for(int i=0;i<EnemyBulletList_right.size();i++)
    {
        if(EnemyBulletList_right[i]->collidesWithItem(&Defensemagic))
        {
            mScene.removeItem(EnemyBulletList_right[i]);
            EnemyBulletList_right.removeOne(EnemyBulletList_right[i]);
        }
    }
    }
}

void Widget::CreatEnemy()
{
    if(the_second)
    {
    int rand_enemy_left=(rand()%4)+1;
    int rand_enemy_right=(rand()%4)+1;
    QString str1;
    QString str2;
    str1=QString(":/Enemy/Enemy/enemy_00%1_left.png").arg(rand_enemy_left);
    str2=QString(":/Enemy/Enemy/enemy_00%1_right.png").arg(rand_enemy_right);
    QPixmap pixmap1(str1);
    QPixmap pixmap2(str2);
    int randy1=(rand()%480);
    int randy2=(rand()%480);
    Enemy*enemy1=new Enemy(QPoint(1280,randy1),pixmap1);
    Enemy*enemy2=new Enemy(QPoint(-300,randy2),pixmap2);

    mScene.addItem(enemy1);
    mScene.addItem(enemy2);

    mEnemyList_left.append(enemy1);
    mEnemyList_right.append(enemy2);
    }
}

void Widget::Enemyattckingmagic_left()
{
    if(the_first&&start_condition)
    {
    QPixmap img(":/bullet/bullet/bullets_001 (2).png");
    int randy=(rand()%660);
    QPoint pos(790,randy);
    Bullet *bullet=new Bullet(pos,img,0);
    mScene.addItem(bullet);
    EnemyBulletList_left.append(bullet);
    }
}
void Widget::Enemyattckingmagic_right()
{
    if(the_first&&start_condition)
    {
        QPixmap img(":/bullet/bullet/bullets_001 (2).png");
        int randy=(rand()%660);
        QPoint pos(0,randy);
        Bullet *bullet=new Bullet(pos,img,0);
        mScene.addItem(bullet);
        EnemyBulletList_right.append(bullet);
    }
}

void Widget::fuxiandefensemagic()
{
    if(the_first)
    {
    for(int i=0;i<mBulletList_right.size();i++)
    {
        for(int j=0;j<8;j++)
        {
            if(mBulletList_right[i]->collidesWithItem(&fuxiandefense))
            {
                mScene.addItem(&fuxiandefense);
                fuxiandefense_condition[j]=true;
                mScene.removeItem(mBulletList_right[i]);
                mBulletList_right.removeOne(mBulletList_right[i]);
            }
        }
    }
    }
}

void Widget::fuxiandefensemagicover()
{
    for(int i=0;i<8;i++)
    {
        if(fuxiandefense_condition[i])
        {
            fuxiandefense_condition[i]=false;
        }
    }
}

void Widget::violinistattcking()
{
    if(start_condition&&the_second)
    {
    int randy=(rand()%660);
    QPixmap img(":/bullet/bullet/bullet_009.png");
    QPoint pos(800,randy);
    Bullet* bullet=new Bullet(pos,img,0);
    mScene.addItem(bullet);
    violinistattack.append(bullet);
    boss2->setPos(boss2->x(),randy);
    bool attckswitch=true;
    violinswitch.append(attckswitch);
    }
}

void Widget::violinistappearance()
{
    if(start_condition&&the_second)
    {
    int randm=rand()%4;
    if(randm==0)
    {
        boss2->setPixmap(QPixmap(":/Enemy/Enemy/awula_002.png"));
    }
    else
    {
        boss2->setPixmap(QPixmap(":/Enemy/Enemy/awula_003.png"));
    }
    }

}

void Widget::Collision_fuxian()
{
    if(the_first)
    {

    for(int i=0;i<mBulletList_right.size();i++)
    {
        if(mBulletList_right[i]->collidesWithItem(&fuxiandefense))
        {
            if(fufuplayer.fufu.y()>290)
            {
                int randm=(rand()%10);
                if(randm==0)
                {
                    fuxian_life=fuxian_life-1;
                }
                mScene.removeItem(mBulletList_right[i]);
                mBulletList_right.removeOne(mBulletList_right[i]);
            }
            else if(fufuplayer.fufu.y()<=290)
            {
                int randm=(rand()%3);
                if(randm==0)
                {
                    fuxian_life=fuxian_life-1;
                }
                mScene.removeItem(mBulletList_right[i]);
                mBulletList_right.removeOne(mBulletList_right[i]);
            }
        }
       // qDebug()<<fuxian_life;
    }
    if(fuxian_life<=0)
    {
        the_second=true;
        boss1->moveBy(-1280,0);
        fuxiandefense.moveBy(-1280,0);
        the_first=false;
    }
    }
}

void Widget::Collision_fufu()
{

    if(the_first)
    {
    for(int i=0;i<EnemyBulletList_left.size();i++)
    {
        if(fufuplayer.fufu.collidesWithItem(EnemyBulletList_left[i]))
        {
            mScene.removeItem(EnemyBulletList_left[i]);
            EnemyBulletList_left.removeOne(EnemyBulletList_left[i]);
            fufu_life=fufu_life-1;
           // qDebug()<<fufu_life;
        }
    }
    for(int i=0;i<EnemyBulletList_right.size();i++)
    {
        if(fufuplayer.fufu.collidesWithItem(EnemyBulletList_right[i]))
        {
            mScene.removeItem(EnemyBulletList_right[i]);
            EnemyBulletList_right.removeOne(EnemyBulletList_right[i]);
            fufu_life=fufu_life-1;
            // qDebug()<<fufu_life;
        }
    }
   // qDebug()<<fufu_life;
    }
    if(the_second)
    {
        for(int i=0;i<violinistattack.size();i++)
        {
            if(fufuplayer.fufu.collidesWithItem(violinistattack[i])&&violinswitch[i])
            {
                fufu_life=fufu_life-1;
                violinswitch[i]=false;
            }
        }

    }
    if((fufu_life==0)&&!fufu_dying)
    {
        this->hide();
        this->die->Gameview.show();
        fufu_dying=true;
        start_condition=false;
    }
}

void Widget::Collision_soldier()
{
    for(int i=0;i<mBulletList_left.size();i++)
    {
        int flag=0;
        for(int j=0;j<mEnemyList_left.size();j++)
        {
            if(mBulletList_left[i]->collidesWithItem(mEnemyList_left[j]))
            {
                mScene.removeItem(mBulletList_left[i]);
                mScene.removeItem(mEnemyList_left[j]);
                mEnemyList_left[j]->moveBy(-1280,0);
                mBulletList_left.removeOne(mBulletList_left[i]);
                mEnemyList_left.removeOne(mEnemyList_left[j]);
                flag=1;
                break;

            }
        }
        if(flag)
        {
            break;
        }
    }
    for(int i=0;i<mBulletList_right.size();i++)
    {
        int flag=0;
        for(int j=0;j<mEnemyList_left.size();j++)
        {
            if(mBulletList_right[i]->collidesWithItem(mEnemyList_left[j]))
            {
                mScene.removeItem(mBulletList_right[i]);
                mScene.removeItem(mEnemyList_left[j]);
                mEnemyList_left[j]->moveBy(-1280,0);
                mBulletList_right.removeOne(mBulletList_right[i]);
                mEnemyList_left.removeOne(mEnemyList_left[j]);
                flag=1;
                break;
            }
        }
        if(flag)
        {
            break;
        }
    }
    for(int i=0;i<mBulletList_left.size();i++)
    {
        int flag=0;
        for(int j=0;j<mEnemyList_right.size();j++)
        {
            if(mBulletList_left[i]->collidesWithItem(mEnemyList_right[j]))
            {
                mScene.removeItem(mBulletList_left[i]);
                mScene.removeItem(mEnemyList_right[j]);
                mEnemyList_right[j]->moveBy(1280,0);
                mBulletList_left.removeOne(mBulletList_left[i]);
                mEnemyList_left.removeOne(mEnemyList_left[j]);
                flag=1;
                break;
            }
        }
        if(flag)
        {
            break;
        }
    }
    for(int i=0;i<mBulletList_right.size();i++)
    {
        int flag=0;
        for(int j=0;j<mEnemyList_right.size();j++)
        {
            if(mBulletList_right[i]->collidesWithItem(mEnemyList_right[j]))
            {
                mScene.removeItem(mBulletList_right[i]);
                mScene.removeItem(mEnemyList_right[j]);
                mEnemyList_right[j]->moveBy(1280,0);
                mBulletList_right.removeOne(mBulletList_right[i]);
                mEnemyList_left.removeOne(mEnemyList_left[j]);
                flag=1;
                break;
            }
        }
        if(flag)
        {
            break;
        }
    }
}

void Widget::Collision_awula()
{

    for(int i=0;i<mBulletList_right.size();i++)
    {
        if(mBulletList_right[i]->collidesWithItem(boss2))
        {
            boss2_life=boss2_life-1;
            mScene.removeItem(mBulletList_right[i]);
            mBulletList_right.removeOne(mBulletList_right[i]);\
               // qDebug()<<boss2_life;
        }
    }

    if(boss2_life<0&&end_switch)
    {
        //this->ed->show();
        this->ed->Gameview.show();
        this->hide();
        end_switch=false;
    }
}

void Widget::start()
{
    start_condition=true;
    if(the_first)
    {
    mScene.addItem(boss1);
    fuxiandefense.setPixmap(QPixmap(":/bullet/bullet/defense_004.png"));
    boss1->setPos(QPoint(813,20));
    mScene.addItem(&fuxiandefense);
    fuxiandefense.setPos(780,0);
    }
    if(the_second)
    {
        boss2=new awula(this);
        mScene.addItem(boss2);
    }
}

void Widget::happenagain()
{
        fufu_life=50;
        fuxian_life=10;
        boss2_life=15;
        the_first=true;
        the_second=false;
        start_condition=false;
        fufu_dying=false;
        for(int i=0;i<10;i++)
        {
            background[i].setPixmap(QPixmap(":/background/Map/background1.png"));
            mScene.addItem(&background[i]);
            background[i].setPos(1279*(i-2),0);
        }
        // qDebug()<<fufu_life;
        // qDebug()<<fuxian_life;
        foreach(auto item,mKeyList1)
        {
            mKeyList1.removeOne(item);
        }
        // foreach(auto item,mEnemyList_left)
        // {
        //     mEnemyList_left.removeOne(item);
        // }
        // foreach(auto item,mEnemyList_right)
        // {
        //     mEnemyList_right.removeOne(item);
        // }
        // foreach(auto item,EnemyBulletList_left)
        // {
        //     EnemyBulletList_left.removeOne(item);
        // }
        // foreach(auto item,EnemyBulletList_right)
        // {
        //     EnemyBulletList_right.removeOne(item);
        // }
        fufuplayer.fufu.setPos(250,340);

}

void Widget::backgroundchange()
{
    if(!the_first&&the_second&&changeend)
    {
        for(int i=0;i<10;i++)
        {
            if(background[i].x()>=0&&background[i].x()<=1280)
            {
                background[i-1].setPixmap(QPixmap(":/background/Map/night_006.png"));
                for(int j=i;j<9;j++)
                {
                    background[j].setPixmap(QPixmap(":/background/Map/night_003.png"));
                }
                background[9].setPixmap(QPixmap(":/background/Map/night_005.png"));
                changeend=false;
                mScene.addItem(boss2);
                boss2->setPos(850,260);
                break;
            }
        }
    }
}

void Widget::Speedchange()
{
    if(the_second)
    {
        fufu_Speed=3;
    }
}

void Widget::rushing()
{
    if (rushing_condition && !facingside)
    {
        if (fufuplayer.fufu.x() - 3 * fufu_Speed < 0)
        {
            fufuplayer.fufu.setX(0);
            for (int i = 0; i < 15; i++)
            {
                background[i].moveBy(3 * fufu_Speed, 0);
            }
            mCloud.moveBy(3 * fufu_Speed, 0);
        }
        else
        {
            fufuplayer.fufu.moveBy(-3 * fufu_Speed, 0);
        }
    }
    else if (rushing_condition && facingside)
    {
        if (fufuplayer.fufu.x() + 3 * fufu_Speed > 450)
        {
            fufuplayer.fufu.setX(450);
            for (int i = 0; i < 15; i++)
            {
                background[i].moveBy(-3 * fufu_Speed, 0);
            }
            mCloud.moveBy(-3 * fufu_Speed, 0);
        }
        else
        {
            fufuplayer.fufu.moveBy(3 * fufu_Speed, 0);
        }
    }
}



