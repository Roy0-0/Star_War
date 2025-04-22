#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <ctime>
#include <QSoundEffect>

#include <QFile>
#include <QDebug>
#include <QApplication>

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

    //敌机出场时间间隔初始化
    m_recorder=0;

    //添加随机数种子控制敌机出场位置
    srand((unsigned int) time (NULL));
}

void MainScreen::playGame()
{

    //启动背景音乐
    //Qsound::play(SOUND_BACKGROUND);
    /*QString filePath = "F:/Cs/StarWar/StarWar/Resource/bg.wav";
    if(QFile::exists(filePath))
    {
        qDebug()<<"文件存在！";
    }
    else{
        qDebug()<<"文件不存在或路径错误！";
    }*/
    QSoundEffect* effect1 = new QSoundEffect;
    /*effect1.setSource(QUrl::fromLocalFile("F:/Cs/StarWar/StarWar/Resource/bg.wav"));
    QObject::connect(&effect1 , &QSoundEffect::statusChanged,[&](){
        qDebug()<<"状态："<<effect1.status();
    });*/
    QUrl fileUrl = QUrl::fromLocalFile(SOUND_BACKGROUND);
    effect1->setSource(fileUrl);
    // if(effect1.status()==QSoundEffect::Error)
    // {
    //     qDebug()<<"加载失败,错误代码："<<effect1.status();
    // }
    // else{
    //     qDebug()<<"文件已加载，状态："<<effect1.status();
    //     QTimer::singleShot(1000,[&]{
    //         qDebug()<<"文件已加载，当前状态为："<<effect1.status();
    //     });
    // }
    effect1->setLoopCount(QSoundEffect::Infinite);
    effect1->setVolume(0.1f);
    QObject::connect(effect1, &QSoundEffect::loadedChanged, [=](){
        if(effect1->isLoaded()) {
            effect1->play();
        }
    });

    //启动定时器
    m_Timer.start();

    //每隔十毫秒监听信号槽中的TimeOut信号
    connect(&m_Timer,&QTimer::timeout,[=]()
            {
                //敌机出场
                enemyToScene();
                //更新坐标并绘制
                updatePosition();
                update();
                //碰撞检测
                collisionDetection();
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

    //敌机出场
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free==false)
        {
            m_enemys[i].updatePosition();
        }
    }

    //计算爆炸播放的图片
    for(int i=0;i<BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free==false)
        {
            m_bombs[i].updateInfo();//更新信息
        }
    }
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

    //绘制敌机
    /*QSoundEffect* effect3 = new QSoundEffect();

    QUrl fileUrl = QUrl::fromLocalFile(SOUND_ENEMY_ARRIVE);
    effect3->setSource(fileUrl);
    effect3->setVolume(0.3f);*/
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free==false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
            /*effect3->play();*/
        }
    }

    //绘制爆炸
    for(int i=0;i<BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free==false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,
                               m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }

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

void MainScreen::enemyToScene()
{
    m_recorder++;
    //未达到出场间隔
    if(m_recorder<ENEMY_INTERVAL)
    {
        return;
    }

    // QSoundEffect* effect3 = new QSoundEffect();

    // QUrl fileUrl = QUrl::fromLocalFile(SOUND_ENEMY_ARRIVE);
    // effect3->setSource(fileUrl);
    // effect3->setVolume(0.3f);

    m_recorder=0;
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            m_enemys[i].m_Free=false;

            //坐标设置
            m_enemys[i].m_X=rand()%(GAME_WIDTH-m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y=-m_enemys[i].m_Rect.height();
            //effect3->play();
            break;
        }
    }
}

void MainScreen::collisionDetection()
{
    //遍历所有非空闲状态的敌机
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free) continue;

        for(int j=0;j<BULLET_NUM;j++)
        {
            //英雄子弹空闲
            if(m_hero.m_bullets[j].m_Free) continue;
            //矩形框相交
            if((m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))&&(m_enemys[i].m_Y>=0))
            {
                m_enemys[i].m_Free=true;//被消灭，状态重置为空闲
                m_hero.m_bullets[j].m_Free=true;

                //播放爆炸效果
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_Free)//炸弹空闲，可以播放爆炸动画
                    {
                        //开始播放爆炸音乐
                        //QSound::play(SOUND_BOMB);

                        QSoundEffect* effect2 = new QSoundEffect();

                        QUrl fileUrl = QUrl::fromLocalFile(SOUND_BOMB);
                        effect2->setSource(fileUrl);
                        effect2->setVolume(0.3f);

                       // QObject::connect(effect2, &QSoundEffect::loadedChanged, [=](){
                        //    if(effect2->isLoaded()) {
                       //        effect2->stop();
                               effect2->play();
                       //        qDebug()<<"1";

                      //      }
                      //  });
                       // delete effect2;


                        m_bombs[k].m_Free=false;
                        //更新爆炸位置
                        m_bombs[k].m_X=m_enemys[i].m_X;
                        m_bombs[k].m_Y=m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }
}
