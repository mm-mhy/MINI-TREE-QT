//程序运行窗口类头文件声明
#ifndef WIDGET_H
#define WIDGET_H

//导入相应的包，包含时间、标签等
#include <QWidget>
#include<QPushButton>
#include<QTimer>
#include<QLabel>
#include<QListWidget>

//边类，包含起始点，终点，权重
class edge{
public:
    int start;
    int end;
    int weight;
};
//程序运行窗口类声明，继承窗口类
class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();

    //函数声明
    void paintEvent(QPaintEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void gettreevalue();
//私有成员变量声明
private:
    int flag=1;
    //权值和
    int treevalue=0;
    //节点数
    int count=0;
    //线条数
    int lineNum=0;
    //起点
    int start;
    //终点
    int end;
    int currentlines=0;
    //绘制的网的邻接矩阵
    QVector<QVector<int>> m;
    //得到的普利姆最小生成树邻接矩阵
    QVector<QVector<int>> Prim_m;
    //开始动画，绘图事件调用
    bool m_animation=false;
    //按下drawline，开始连接顶点
    bool m_alreadyBuild=false;
    //已经连接顶点
    bool m_isget=false;
    //已经点击了按钮（顶点按钮）
    bool m_isButtonPressed=false;
    //已经按下Prim键供绘图事件调用
    bool m_paintPrim=false;
    //已经按下Kruskal键供绘图事件调用
    bool m_paintKruskal=false;
    //已经按下Prim键
    bool m_Primdone=false;
    //已经按下Kruskal键
    bool m_Kruskaldone=false;
    //线起点
    QPoint m_startPoint;
    //线终点
    QPoint m_endPoint;
    //按钮指针数组
    QVector<QPushButton*> BTN;
    //线
    QVector<QPair<QPoint,QPoint>> LINE;
    //节点访问顺序数组
    QVector<int> P_order;
    //普利姆画线顺序
    QVector<QPoint> Prim_points;
    //克鲁斯卡尔画线顺序
    QVector<QPoint> Kruskal_points;
    //普利姆画线次序编号数组
    QVector<QString> P_string;
    //克鲁斯卡尔画线次序编号
    QVector<QString> K_string;
    //定时器
    QTimer *timer;
    //提示
    QLabel *Title;
    //操作实时监控
    QLabel *draw;
    //监控连线状态
    QLabel *linestatus;
    //画线记录，顺序
    QListWidget *plist;
    //信号函数，执行画线
//相应槽函数，按键出发后生成
private slots:
    //普利姆算法用于动画绘制，定时器
    void nextline(){
        if(++currentlines<=Prim_points.size()/2){
            plist->addItem("Prim方法画线从 "+P_string[2*(currentlines-1)]+" 到 "+P_string[2*(currentlines-1)+1]);
            update();
        }
        else{
            timer->stop();
        }
    }
    //克鲁斯卡尔算法用于动画绘制，定时器
    void krusnextline(){
        if(++currentlines<=Kruskal_points.size()/2){
            plist->addItem("Kruskal方法画线从 "+K_string[2*(currentlines-1)]+" 到 "+K_string[2*(currentlines-1)+1]);
            update();
        }
        else{
            timer->stop();
        }
    }
//信号，监听返回
signals:
    void back();
};

#endif // WIDGET_H
