#ifndef OUT_H
#define OUT_H

#include <QWidget>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QPushButton>

namespace Ui {
class OUT;
}

class OUT : public QWidget
{
    Q_OBJECT

public:
    explicit OUT(QWidget *parent = nullptr);
    ~OUT();
    QGraphicsPixmapItem item;
    QGraphicsView Gameview;
    QGraphicsScene Scene;

    signals:
    void back();
private:
    Ui::OUT *ui;
};

#endif // OUT_H
