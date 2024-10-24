//导入相应的包，包含调试、标签、绘图、字体以及相应的头文件
//该代码为整个项目的按钮类
#include "mypushbutton.h"
#include<QPropertyAnimation>

//按钮构造函数声明
mypushbutton::mypushbutton()
{

}

//按钮的跳动函数
void mypushbutton::zoom1(){
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");

    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}
void mypushbutton::zoom2(){
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");

    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}
