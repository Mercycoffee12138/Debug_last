#include "Gamecontrol.h"


Gamecontrol* Gamecontrol::instance=nullptr;
Gamecontrol::Gamecontrol() {}

void Gamecontrol::GameInit()
{
    LoadStartScene();
    mGameview.setSceneRect(QRect(0,0,1278,720));
    GameObjectPool::Instance()->Init();
}

void Gamecontrol::LoadStartScene()
{
    mScene.setSceneRect(QRect(0,0,1280,720));
    gamestart.setSceneRect(QRect(0,0,1280,720));
    gamestart.addPixmap(QPixmap(":/background/Map/start.png"));
    auto startbtn=new QToolButton();
    startbtn->setFocusPolicy(Qt::NoFocus);
    startbtn->setIcon(QIcon(":/start/start/ui_start_idle.png"));
    startbtn->setIconSize(QSize(175,70));
    startbtn->move(549,500);
    connect(startbtn,&QToolButton::clicked,[this](){
        mGameview.setScene(&mScene);
        mGameview.show();
        //背景音乐
    });
    gamestart.addWidget(startbtn);
}

void Gamecontrol::Gameover()
{

}

