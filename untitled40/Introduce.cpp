#include "Introduce.h"
#include "ui_Introduce.h"

Introduce::Introduce(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Introduce)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    setWindowTitle("Introduction");

}

Introduce::~Introduce()
{
    delete ui;
}
