#include "bomb.h"
#include "config.h"
#include <QString>

Bomb::Bomb()
{
    //将所有的爆炸图片放入数组
    for(int i=1;i<=BOMB_MAX;i++)
    {
        QString str = QString(BOMB_PATH).arg(i);
        m_pixArr.push_back(QPixmap(str));
    }

    //初始化坐标
    m_X=0;
    m_Y=0;
    //空闲状态下标
    m_Free=true;
    //播放当前图片下标
    m_index=0;
    //播放爆炸间隔记录
    m_Recoder=0;
}

void Bomb::updateInfo()
{
    //空闲状态下的炸弹不需要爆炸
    if(m_Free) return ;
    m_Recoder++;
    // 还未到切图时间
    if(m_Recoder<BOMB_INTERVAL) return ;

    //重置爆炸间隔
    m_Recoder=0;
    //切换到下一张图
    m_index++;
    // 现在存在数组中了，下标从零开始，当下标大于六时重置，爆炸效果重置
    if(m_index>BOMB_MAX-1)
    {
        m_index=0;
        m_Free=true;
    }
}
