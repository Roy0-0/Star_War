#include "Map.h"
#include "config.h"

Map::Map()
{
    //加载地图对象
    m_map1.load(MAP_PATH);
    m_map2.load(MAP_PATH);

    //初始化Y坐标
    m_map1_posY=-GAME_HEIGHT;
    m_map2_posY=0;
    //地图滚动速度
    m_scroll_speed=MAP_SCROLL_SPEED;
}

void Map::mapPosition()
{
    m_map1_posY += m_scroll_speed;
    if(m_map1_posY >= 0)//窗口最上面是0，最下面是-GAME_HEIGHT
    {
        m_map1_posY = -GAME_HEIGHT;
    }

    m_map2_posY += m_scroll_speed;
    if(m_map2_posY >= GAME_HEIGHT)//窗口最上面是0，最下面是-GAME_HEIGHT
    {
        m_map2_posY = 0;
    }
}
