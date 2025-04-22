#ifndef BULLET_H
#define BULLET_H
#include <QPixmap>
#include <QRect>

class Bullet
{
    public:
        Bullet();

        //更新子弹坐标
        void updatePosition();

    public:
        //子弹资源对象
        QPixmap m_Bullet;
        //子弹坐标
        int m_X;
        int m_Y;
        //子弹移动速度
        int m_Speed;
        //子弹状态，即是否闲置,若处于非闲置状态，则维护坐标移动，当移动出屏幕后维护状态为闲置（防止资源加载过多，内存不够）
        bool m_Free;
        //子弹矩形边框，用于检测子弹碰撞
        QRect m_Rect;
};

#endif // BULLET_H
