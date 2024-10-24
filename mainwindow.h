//主窗口类头文件声明
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"widget.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//继承QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *ev);
private:
    Ui::MainWindow *ui;
    widget *mywidget=nullptr;
};

#endif // MAINWINDOW_H
