#ifndef CONFIG_H
#define CONFIG_H

/*游戏参数配置，设置窗口长度，宽度，标题*/
#define GAME_WIDTH 512
#define GAME_HEIGHT 768//依据背景图的尺寸设计尺寸
#define GAME_TITTLE "StarWar v1.0"
#define GAME_RES_PATH "./plane.rcc"  //rcc路径
#define GAME_ICON ":/Resource/jet.ico"
#define GAME_RATE 10 //刷新频率10ms

#define MAP_PATH ":/Resource/mapback.png"
#define MAP_SCROLL_SPEED 2//地图滚动速度,单位像素

#endif // CONFIG_H
