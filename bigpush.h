//初始邻接矩阵类头文件声明
#ifndef BIGPUSH_H
#define BIGPUSH_H
#include"mypushbutton.h"
#include <QWidget>
#include<QMessageBox>
#include<QTimer>

//类声明
class bigpush : public mypushbutton
{
    Q_OBJECT
public:
    explicit bigpush()
    {

    }
    virtual void foo(QVector<QVector<int>> m,QWidget *t){
        //QMessageBox::information(this,"error","bigpush.cpp\nlittlepush.cpp\nmainwindow.cpp\nmypushbutton.cpp\nwidhet.cpp");
            QString str="";
            for(int i=0;i<m.size();i++){
                for(int j=0;j<m.size();j++){
                    str+=QString::number(m[i][j])+" ";
                }
                str+="\n";
            }
            QTimer::singleShot(500,[=](){
                QMessageBox::information(t,"初始邻接矩阵",str);
            });        
    }
signals:

};

#endif // BIGPUSH_H
