#include "Gameobjectpool.h"

GameObjectPool*GameObjectPool::instance=nullptr;
GameObjectPool::GameObjectPool(QObject *parent)
    : QObject{parent}
{

}

void GameObjectPool::Init()
{
    for(int i=0;i<20;i++)
    {
        Bullet*bullet=new Bullet;
        mBulletPool.append(bullet);

        Enemy*enemy=new Enemy;
        mEnemyPool.append(enemy);
    }
}

Bullet *GameObjectPool::CreatBullet()
{
    Bullet*bullet=mBulletPool.first();
    mBulletPool.pop_front();
    return bullet;
}

Enemy *GameObjectPool::CreatEnemy()
{
    Enemy*enemy=mEnemyPool.first();
    mEnemyPool.pop_front();
    return enemy;
}

void GameObjectPool::RecoveryObject(Bullet *bullet)
{
    mBulletPool.append(bullet);
}

void GameObjectPool::RecoveryObject(Enemy *enemy)
{
    mEnemyPool.append(enemy);
}

void GameObjectPool::Clear()
{
    for(auto pBullet:mBulletPool)
    {
        delete pBullet;
    }
    for(auto pEnemy:mEnemyPool)
    {
        delete pEnemy;
    }
}
