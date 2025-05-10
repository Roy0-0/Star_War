#include "bullet.h"
#include "config.h"

Bullet::Bullet()
{
    //加载子弹资源
    m_Bullet.load(BULLET_PATH);

    //设置子弹坐标
    m_X=GAME_WIDTH*0.5-m_Bullet.width()*0.5;
    m_Y=GAME_HEIGHT;

    //子弹状态
    m_Free=true;//默认为空闲状态；

    //子弹速度初始化
    m_Speed=BULLET_SPEED;

    //子弹矩形框
    m_Rect.setWidth(m_Bullet.width());
    m_Rect.setHeight(m_Bullet.height());

    m_Rect.moveTo(m_X,m_Y);
}

void Bullet::updatePosition()
{
    if(m_Free)//子弹空闲，不用移动
    {
        return ;
    }
    else
    {
        m_Y-=m_Speed;
        m_Rect.moveTo(m_X,m_Y);
    }

    //子弹超出屏幕后，重置空闲状态
    if(m_Y<=-m_Rect.height())
    {
        m_Free=true;
    }
}
