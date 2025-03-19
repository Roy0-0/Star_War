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
}

void MainScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

}
