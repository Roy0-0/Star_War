#include "heroplane.h"
#include "config.h"

HeroPlane::HeroPlane()
{
    //加载飞机资源
    m_Plane.load(HERO_PATH);

    //初始化飞机坐标
    m_X=(GAME_WIDTH-m_Plane.width())*0.5;
    m_Y=(GAME_HEIGHT-m_Plane.height());

    //初始化矩形边框
    m_Rect.setWidth(m_Plane.width());
    m_Rect.setHeight(m_Plane.height());

    //初始化矩形的位置
    m_Rect.moveTo(m_X,m_Y);

}

void HeroPlane::shoot()
{
    //累加时间间隔记录
    m_recorder++;

    //记录时间未达到发射子弹时间间隔
    if(m_recorder<BULLET_INTERVAL) return ;

    //否则达到时间间隔，即将发射这颗子弹
    m_recorder=0;

    //发射子弹
    for(int i=0;i<BULLET_NUM;i++)
    {
        //出现空闲子弹即可发射
        if(m_bullets[i].m_Free)
        {
            m_bullets[i].m_Free=false;
            //设置子弹发射坐标
            m_bullets[i].m_X=m_X+m_Rect.width()*0.5-25;
            m_bullets[i].m_Y=m_Y-25;
            break;
        }
    }
}

void HeroPlane::setPosition(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_Rect.moveTo(m_X,m_Y);
}
