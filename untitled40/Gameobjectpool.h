#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H

#include <QObject>
#include"Bullet.h"
#include"Enemy.h"

class GameObjectPool : public QObject
{
    static GameObjectPool*instance;
public:
    explicit GameObjectPool(QObject *parent = nullptr);
    static GameObjectPool*Instance()
    {
        if(instance==nullptr)
        {
            return instance=new GameObjectPool;
        }
        return instance;
    }
    void Init();//缓存
    //获取对象
    Bullet*CreatBullet();
    Enemy*CreatEnemy();

//对象回收
    void RecoveryObject(Bullet*bullet);
    void RecoveryObject(Enemy*enemy);

    void Clear();
protected:
    QList<Bullet*>mBulletPool;
    QList<Enemy*>mEnemyPool;
signals:
};

#endif // GAMEOBJECTPOOL_H
