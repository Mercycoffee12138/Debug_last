#ifndef INTRODUCE_H
#define INTRODUCE_H

#include <QWidget>

namespace Ui {
class Introduce;
}

class Introduce : public QWidget
{
    Q_OBJECT

public:
    explicit Introduce(QWidget *parent = nullptr);
    ~Introduce();

private:
    Ui::Introduce *ui;
};

#endif // INTRODUCE_H
