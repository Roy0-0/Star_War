#ifndef MAP_H
#define MAP_H
#include <QPixmap>

class Map
{
public:
    Map();

    //地图滚动坐标计算
    void mapPosition();

public:

    //利用QPixmap控制两个地图对象
    QPixmap m_map1;
    QPixmap m_map2;

    //设置地图Y坐标(因为只需要上下移动)
    int m_map1_posY;
    int m_map2_posY;

    //控制地图滚动幅度
    int m_scroll_speed;
};

#endif // MAP_H
