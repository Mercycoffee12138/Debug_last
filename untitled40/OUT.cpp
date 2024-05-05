#include "OUT.h"
#include "ui_OUT.h"

OUT::OUT(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OUT)
{
    ui->setupUi(this);
    setWindowTitle("Do you wanna another try?");
    Gameview.setSceneRect(QRect(0,0,598,500));
    Scene.setSceneRect(QRect(0,0,600,500));
    item.setPixmap(QPixmap(":/start/start/dying_001.png"));
    Gameview.setScene(&Scene);
    Scene.addItem(&item);
    auto btn=new QPushButton();
    btn->setIcon(QIcon(":/start/start/again_001.png"));
    btn->setIconSize(QSize(72,89));
    btn->setStyleSheet("border: none; border-style: solid; border-color: transparent;");
    //btn->setStyleSheet("border:none;");
    btn->move(524,411);
    Scene.addWidget(btn);
    connect(btn,&QPushButton::clicked,[=](){
        emit this->back();
    });
   // Gameview.show();
}

OUT::~OUT()
{
    delete ui;
}
