#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QTimer>
#include "Map.h"
#include "heroplane.h"
#include "bullet.h"
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainScreen;
}
QT_END_NAMESPACE

class MainScreen : public QWidget
{
    Q_OBJECT

public:
    MainScreen(QWidget *parent = nullptr);
    ~MainScreen();

    //场景初始化配置
    void InitScreen();

    //启动游戏

    void playGame();

    //更新所有坐标

    void updatePosition();

    //绘制到屏幕中,采用绘图事件
    void paintEvent(QPaintEvent *);

    //捕获鼠标移动事件，用以控制飞机移动
    void mouseMoveEvent(QMouseEvent *);

    //地图对象
    Map m_map;

    //飞机对象显示
    HeroPlane m_hero;

    //QT Timer
    QTimer m_Timer;//刷新屏幕时间相当于帧率

    //子弹对象实现
    Bullet temp_Bullet;

private:
    Ui::MainScreen *ui;
};
#endif // MAINSCREEN_H
