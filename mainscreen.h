#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QTimer>
#include "Map.h"

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

    //地图对象
    Map m_map;

    //QT Timer
    QTimer m_Timer;//刷新屏幕时间相当于帧率

private:
    Ui::MainScreen *ui;
};
#endif // MAINSCREEN_H
