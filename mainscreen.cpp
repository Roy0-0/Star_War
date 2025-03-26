#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "config.h"
#include <QIcon>
#include <QPainter>

MainScreen::MainScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    //调用初始化场景接口
    InitScreen();

    //启动游戏
    playGame();
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::InitScreen()//初始化窗口函数
{
    //窗口固定尺寸
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //设置窗口标题
    setWindowTitle(GAME_TITTLE);
    //设置窗口图标ICON
    setWindowIcon(QIcon(GAME_ICON));
    //Timer定时器设置

    m_Timer.setInterval(GAME_RATE);

}

void MainScreen::playGame()
{
    //启动定时器
    m_Timer.start();

    //每隔十毫秒监听信号槽中的TimeOut信号
    connect(&m_Timer,&QTimer::timeout,[=]()
    {
      //更新坐标并绘制
      updatePosition();
      update();
    });
}

void MainScreen::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();

    //发射子弹
    m_hero.shoot();

    //计算所有当前非空闲子弹坐标
    for(int i=0;i<BULLET_NUM;i++)
    {
        //如果非空闲，计算当前位置
        if(m_hero.m_bullets[i].m_Free==false)
        {
            m_hero.m_bullets[i].updatePosition();
        }
    }

    //测试子弹
     // temp_Bullet.m_Free = false;
     // temp_Bullet.updatePosition();
}

void MainScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //绘制英雄飞机
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);


    //绘制所有非空闲状态子弹
    for(int i=0;i<BULLET_NUM;i++)
    {
        //如果非空闲，计算当前位置
        if(m_hero.m_bullets[i].m_Free==false)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
        }
    }

    //绘制测试子弹
     // painter.drawPixmap(temp_Bullet.m_X,temp_Bullet.m_Y,temp_Bullet.m_Bullet);

}

void MainScreen::mouseMoveEvent(QMouseEvent * event)
{
    setMouseTracking(true);//不用一直按压鼠标飞机也可以移动

    int x=event->x()-m_hero.m_Rect.width()*0.5;
    int y=event->y()-m_hero.m_Rect.height()*0.5;

    //边界检测
    if(x<0) x=0;

    if(x>=GAME_WIDTH-m_hero.m_Rect.width())
    {
        x=GAME_WIDTH-m_hero.m_Rect.width();
    }

    if(y<0) y=0;

    if(y>GAME_HEIGHT-m_hero.m_Rect.height())
    {
        y=GAME_HEIGHT-m_hero.m_Rect.height();
    }
    m_hero.setPosition(x,y);
}
