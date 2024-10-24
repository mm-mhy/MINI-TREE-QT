//按钮类头文件声明
#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include<QPushButton>

//mypushbutton为QPushButton派生类
class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mypushbutton();
    void zoom1();
    void zoom2();
    virtual void foo(QVector<QVector<int>> m,QWidget *t){
        qDebug()<<"you push the button";
    }
signals:

};

#endif // MYPUSHBUTTON_H
