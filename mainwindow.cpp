//导入相应的包，包含调试、标签、绘图、字体以及相应的头文件
//该代码为整个项目的主窗口程序入口
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mypushbutton.h"
#include<QTimer>
#include"widget.h"
#include<QDebug>
#include<QPainter>
#include<QLabel>
#include<QFont>

//构造函数，主要用于实现软件的交互逻辑，继承主窗口MainWindow类
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //初始信息设置，包含背景、作者信息
    ui->setupUi(this);
    setWindowIcon(QIcon(":/PrimIcon.jpg"));
    QLabel *banben=new QLabel(this);
    banben->resize(200,50);
    banben->move(10,550);
    banben->setText("version 1.0");
    QLabel *label=new QLabel(this);
    label->resize(800,100);
    label->setText("基于QT框架开发的最小生成树\n         可视化动画教学软件");
    label->move(125,200);
    QFont font;
    font.setFamily("华文彩云");
    font.setBold(true);
    font.setPointSize(30);
    label->setFont(font);
    //进入程序
    setFixedSize(800,600);
    setWindowTitle("PMT");
    mypushbutton *btn=new mypushbutton();
    btn->setParent(this);
    btn->resize(100,50);
    btn->move(350,400);
    btn->show();
    btn->setText("创建新项目");
    btn->setStyleSheet("border-radius:20px;font-weight:bold;background-color:pink;border:4px solid black;");
    //按钮交互，点击按钮进入程序
    connect(btn,&mypushbutton::clicked,[=](){
        btn->zoom1();
        btn->zoom2();
        //实例化程序窗口
        mywidget=new widget;
        QTimer::singleShot(500,this,[=](){
            mywidget->setGeometry(this->geometry());
            this->hide();
            mywidget->show();
        });
        //按钮交互，点击“返回主页”按钮即可返回主页
        connect(mywidget,&widget::back,this,[=](){
            this->show();
            this->setGeometry(mywidget->geometry());
            mywidget->hide();
        });
    });
}
//设置背景
void MainWindow::paintEvent(QPaintEvent *ev){
    QPainter painter(this);
    QPixmap pix;
    //加载相同路径子文件
    pix.load(":/MainWindow.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
//析构函数，程序结束，删除所有对象，释放内存
MainWindow::~MainWindow()
{
    delete ui;
    qDebug()<<"delete all";
}

