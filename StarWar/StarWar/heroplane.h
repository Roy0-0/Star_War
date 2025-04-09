#ifndef HEROPLANE_H
#define HEROPLANE_H
#include <QPixmap>
#include <QRect>
#include "bullet.h"
#include "config.h"

class HeroPlane
{
public:
    HeroPlane();
    //发射子弹
    void shoot();

    //设置弹匣
    Bullet m_bullets[ BULLET_NUM ];

    //记录发射时间
    int m_recorder=0;

    //设置飞机位置
    void setPosition(int x,int y);

    //设置飞机资源以及对象
        QPixmap m_Plane;

    //飞机坐标
    int m_X,m_Y;

    //飞机矩形边框，方便碰撞检测
    QRect m_Rect;
};

#endif // HEROPLANE_H
