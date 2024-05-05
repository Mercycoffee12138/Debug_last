#ifndef END_H
#define END_H

#include <QWidget>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QGraphicsScene>

namespace Ui {
class END;
}

class END : public QWidget
{
    Q_OBJECT

public:
    explicit END(QWidget *parent = nullptr);
    ~END();

    QGraphicsPixmapItem item;
    QGraphicsView Gameview;
    QGraphicsScene Scene;

private:
    Ui::END *ui;
};

#endif // END_H
