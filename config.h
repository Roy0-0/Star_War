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
#define HERO_PATH ":/Resource/Plane05.png"//飞机路径配置
#define BULLET_PATH ":/Resource/bullet_02.png"//己方子弹路径配置
#define BULLET_SPEED 5
#define BULLET_NUM 30   //弹匣中的子弹数
#define BULLET_INTERVAL 20  //发射子弹时间间隔
#define ENEMY_PATH ":/Resource/Plane03.png"//敌机图片
#define ENEMY_SPEED 5 //敌机速度
#define ENEMY_NUM 20 //敌机数量
#define ENEMY_INTERVAL 30 //敌机出现间隔
#define BOMB_PATH ":/Resource/bomb-%1.png"//爆炸图片路径
#define BOMB_NUM 20//爆炸数量
#define BOMB_MAX 7//最大爆炸图片索引
#define BOMB_INTERVAL 20//爆炸刷新间隔
#define SOUND_BACKGROUND "F:/Cs/StarWar/StarWar/Resource/bg.wav"//背景音乐
#define SOUND_BOMB "F:/Cs/StarWar/StarWar/Resource/collision.wav"//爆炸音效
#endif // CONFIG_H
