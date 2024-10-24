//最小生成树邻接矩阵类声明
#ifndef LITTLEPUSH_H
#define LITTLEPUSH_H
#include"mypushbutton.h"
#include <QWidget>
#include<QMessageBox>
#include<QTimer>

class littlepush : public mypushbutton
{
    Q_OBJECT
public:
    explicit littlepush();

    virtual void foo(QVector<QVector<int>> Prim_m,QWidget *t){
        //QMessageBox::information(this,"push","bigpush.h\nlittlepush.h\nmainwindow.h\nmypushbutton.h\nwidhet.h");
            QString str="";
            for(int i=0;i<Prim_m.size();i++){
                for(int j=0;j<Prim_m.size();j++){
                    str+=QString::number(Prim_m[i][j])+" ";
                }
                str+="\n";
            }
            QTimer::singleShot(500,[=](){
                QMessageBox::information(t,"最小生成树邻接矩阵",str);
            });       
    }
signals:

};

#endif // LITTLEPUSH_H
