#include "END.h"
#include "ui_END.h"

END::END(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::END)
{
    ui->setupUi(this);
    // QString str="The life is a grand separation";
    // setWindowTitle(str);
    item.setPixmap(QPixmap(":/start/start/end_001.png"));
    Gameview.setSceneRect(QRect(0,0,598,500));
    Scene.setSceneRect(QRect(0,0,600,500));
    Gameview.setScene(&Scene);
    Scene.addItem(&item);
    //Gameview.show();
}

END::~END()
{
    delete ui;
}
