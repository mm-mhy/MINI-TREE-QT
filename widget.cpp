//导入相应的包，包含调试、标签、绘图、字体以及相应的头文件
//该代码为整个项目的用户操作窗口程序入口
#include "widget.h"
#include<QMouseEvent>
#include<QPainter>
#include<QLabel>
#include<QPainterPath>
#include<QInputDialog>
#include<QPropertyAnimation>
#include<QMessageBox>
#include<QTimer>
#include"mypushbutton.h"
#include"littlepush.h"
#include"bigpush.h"
#include<QListWidget>

//声明全局变量，用于控制邻接矩阵大小
const int INF=INT_MAX;

//程序构造函数，用户所有的交互在该函数内部执行
widget::widget(QWidget *parent)
    : QWidget{parent}
{

    //列表的构建
    plist=new QListWidget(this);
    plist->move(610,485);
    plist->resize(180,110);
    plist->hide();
    mypushbutton *list=new mypushbutton;
    //点击按钮打开列表查看记录
    list->setParent(this);
    list->resize(100,50);
    list->move(650,500);
    list->setText("画线记录");
    list->setStyleSheet("border-radius:20px;font-weight:bold;background-color:pink;border:4px solid black;");
    //邻接矩阵辅助按钮
    //查看最小生成树的邻接矩阵
    mypushbutton *b=new littlepush();
    b->setParent(this);
    b->resize(50,50);
    b->setText("最小");
    b->move(0,100);
    connect(b,&QPushButton::clicked,[=](){       
        b->foo(Prim_m,this);
    });
    //查看原始的邻接矩阵
    mypushbutton *c=new bigpush();
    c->setParent(this);
    c->resize(50,50);
    c->setText("原始");
    c->move(0,50);
    connect(c,&QPushButton::clicked,[=](){
        c->foo(m,this);
    });
     //操作顺序标题：
    Title=new QLabel(this);
    Title->resize(500,50);
    Title->move(50,10);
    Title->setText("请在空白区域绘制点");
    QFont font;
    font.setFamily("华文彩云");
    font.setBold(true);
    font.setPointSize(20);
    Title->setStyleSheet("color:white;");
    Title->setFont(font);
    linestatus=new QLabel(this);//连线状态：
    linestatus->resize(250,50);
    linestatus->move(60,510);
    linestatus->setText("连线状态：当前还未连接");
    //画线顺序标题：
    QFont font2;
    font2.setPointSize(13);
    draw=new QLabel(this);
    draw->resize(300,50);
    draw->move(525,10);
    draw->setText("当前画线：未开始动画");
    draw->setStyleSheet("color:white;");
    draw->setFont(font2);
    setFixedSize(800,600);//设置窗口固定大小：
    setWindowIcon(QIcon(":/PrimIcon.jpg"));
    //返回按钮：
    mypushbutton *back=new mypushbutton;
    back->setParent(this);
    back->resize(100,50);
    back->move(650,425);
    back->setText("返回主页");
    back->setStyleSheet("border-radius:20px;font-weight:bold;background-color:pink;border:4px solid black;");
    //点击按钮返回：
    connect(back,&QPushButton::clicked,[=](){
        back->zoom1();
        back->zoom2();       
        QTimer::singleShot(500,this,[=](){
            QMessageBox::StandardButton reply;
            reply=QMessageBox::question(this,"提示","确定退出，文件不能保存哦?",QMessageBox::Yes|QMessageBox::No);
            //退出交互事件
            if(reply==QMessageBox::No){

            }
            else if(reply==QMessageBox::Yes){
                QTimer::singleShot(500,[=](){
                     emit this->back();
                });
            }
        });
    });

    //展示记录
    connect(list,&QPushButton::clicked,[=]{
        list->zoom1();
        list->zoom2();
        QTimer::singleShot(500,[=](){
            list->hide();
            plist->show();
        });
    });
    //展示邻接矩阵按钮：
    mypushbutton *btn2=new mypushbutton;
    btn2->setParent(this);
    btn2->resize(100,50);
    btn2->move(650,125);
    btn2->setText("邻接矩阵");
    btn2->setStyleSheet("border-radius:20px;font-weight:bold;background-color:pink;border:4px solid black;");
    //开始画线开关：
    mypushbutton *drawline=new mypushbutton;
    drawline->setParent(this);
    drawline->resize(100,50);
    drawline->move(650,50);
    drawline->setText("画线");
    drawline->setStyleSheet("border-radius:20px;font-weight:bold;background-color:pink;border:4px solid black;");
    //点击后开始画线
    connect(drawline,&QPushButton::clicked,[=](){
        Title->setText("绘制好线后请点击普里姆或克鲁斯卡尔");
        drawline->zoom1();
        drawline->zoom2();
        //表明已经绘制完成节点
        this->m_alreadyBuild=true;
        //创建Prim按钮，按下时对线的数量进行判断，如果有线，执行普利姆算法绘图
        mypushbutton *prim=new mypushbutton;
        prim->setParent(this);
        prim->resize(100,50);
        prim->move(650,200);
        prim->setText("普里姆生成");
        prim->setStyleSheet("border-radius:20px;font-weight:bold;background-color:pink;border:4px solid black;");
        prim->show();
        //点击Prim按钮，生成最小生成树
        //创建kruskal按钮，按下时对线的数量进行判断，如果有线，执行克鲁斯卡尔算法绘图
        mypushbutton *kruskal=new mypushbutton;
        kruskal->setParent(this);
        kruskal->resize(100,50);
        kruskal->move(650,275);
        kruskal->setText("克鲁斯卡尔生成");
        kruskal->setStyleSheet("border-radius:20px;font-weight:bold;background-color:pink;border:4px solid black;");
        kruskal->show();
        //点击prim按钮，生成最小生成树
        connect(prim,&QPushButton::clicked,[=](){
            linestatus->setText("连线状态：连接完毕");
            Title->setText("点击动画实现普利姆(Prim)演示");
            prim->zoom1();
            prim->zoom2();
            //判定是否已经绘画完成节点，并且绘制了线条，执行已经按下Prim信号，强制重绘，绘制生成树
            if(m_alreadyBuild&&this->lineNum>0){
                this->m_paintPrim=true;
                this->m_Primdone=true;
                this->m_paintKruskal=false;
                this->m_Kruskaldone=false;
                update();
            }
            else{
                QMessageBox::critical(this,"错误","请先构建好网后再来生成");
            }
        });
        //点击kruskal按钮，生成最小生成树
        connect(kruskal,&QPushButton::clicked,[=](){
            linestatus->setText("连线状态：连接完毕");
            Title->setText("点击动画实现克鲁斯卡尔(Kruskal)演示");
            kruskal->zoom1();
            kruskal->zoom2();
            //判定是否已经绘画完成节点，并且绘制了线条，执行已经按下Prim信号，强制重绘，绘制生成树
            if(m_alreadyBuild&&this->lineNum>0){
                this->m_paintKruskal=true;
                this->m_Kruskaldone=true;
                this->m_paintPrim=false;
                this->m_Primdone=false;
                update();
            }
            else{
                QMessageBox::critical(this,"错误","请先构建好网后再来生成");
            }
        });
        //创建动画按钮，点击后可得到动态的生成树过程
        mypushbutton *active=new mypushbutton;
        active->setParent(this);
        active->resize(100,50);
        active->move(650,350);
        active->setStyleSheet("border-radius:20px;font-weight:bold;background-color:pink;border:4px solid black;");
        active->setText("动画过程演示");
        active->show();
        //点击动画按钮后，开始动画
        connect(active,&QPushButton::clicked,[=](){
            plist->clear();
            linestatus->setText("动画启动，执行中····");
            currentlines=0;
            Title->setText("需要再次画图请按返回");
            if(m_Primdone){
                //判定是否为第一次绘图，后续再次实现动画不需要数据重新进数组，避免冗余
                if(flag){
                    //得到画线次序数组，存储点的坐标
                    for(int i=0;i<P_order.size();i++){
                        for(int j=0;j<P_order.size();j++){
                            if(Prim_m[P_order[i]][P_order[j]]){
                                Prim_points.append(BTN[P_order[i]]->pos());
                                P_string.append(BTN[P_order[i]]->text());
                                Prim_points.append(BTN[P_order[j]]->pos());
                                P_string.append(BTN[P_order[j]]->text());
                                break;
                            }
                        }
                    }
                    flag=0;//置零，下次不执行数据进入数组
                }
                m_animation=true;//动画可执行信号
                timer=new QTimer(this);
                //接收定时器信号，每1000ms执行画线槽函数
                connect(this->timer,&QTimer::timeout,this,&widget::nextline);
                this->timer->start(1000);
            }
            //如果未生成最小生成树，弹出错误对话框
            else if(m_Kruskaldone){
                m_animation=true;//动画可执行信号
                timer=new QTimer(this);
                //接收定时器信号，每1000ms执行画线槽函数
                connect(this->timer,&QTimer::timeout,this,&widget::krusnextline);
                this->timer->start(1000);
            }
            else{
                QMessageBox::critical(this,"错误","您的方案未能实施");
            }
        });
        //初始化邻接矩阵（二维向量）
        QVector<QVector<int>> M(count,QVector<int>(count,0));
        this->m=M;
        for(int i=0;i<BTN.size();i++){
            //画线时监听，点击按钮生成一个线的起始点
            connect(BTN[i],&QPushButton::clicked,[=](){
                //如果未按下过按钮，执行代码块
                if(!m_isButtonPressed){
                    m_startPoint=QPoint(BTN[i]->pos().x()+15,BTN[i]->pos().y()+15);
                    //得到起点，记录该按钮
                    start=i;
                    //已经按下过按钮
                    m_isButtonPressed=true;
                    //初始化画线，表示还没有到达重点，未完成画线
                    m_isget=false;
                }
            });
        }
        //点击，控制台输除画线后得到的邻接矩阵
        connect(btn2,&QPushButton::clicked,[=](){           
            if(!m_Primdone&&!m_Kruskaldone){
                QString str="";
                for(int i=0;i<m.size();i++){
                    for(int j=0;j<m.size();j++){
                        str+=QString::number(m[i][j])+" ";
                    }
                    str+="\n";
                }
                QTimer::singleShot(500,[=](){
                    QMessageBox::information(this,"初始邻接矩阵",str);
                });
            }
            else{
                QString str="";
                for(int i=0;i<Prim_m.size();i++){
                    for(int j=0;j<Prim_m.size();j++){
                        str+=QString::number(Prim_m[i][j])+" ";
                    }
                    str+="\n";
                }
                QTimer::singleShot(500,[=](){
                    QMessageBox::information(this,"最小生成树邻接矩阵",str);
                });
            }
        });
    });
}
//在普利姆最小生成树动画执行完毕后，点击窗口下方按钮得到最小生成树的权值和
void widget::gettreevalue(){
    //如果已经点击了Prim，即生成了普利姆最小生成树，执行
    if(m_Primdone||m_Kruskaldone){
        //创建互动按钮
        mypushbutton *btn=new mypushbutton;
        btn->setParent(this);
        btn->resize(55,25);
        btn->setText("获取权和");
        btn->move(300,555);
        btn->show();
        //点击按钮，弹出权值和对话框
        connect(btn,&mypushbutton::clicked,[=](){
            btn->zoom1();
            btn->zoom2();
            QTimer::singleShot(1000,[=](){
                QMessageBox::information(this,"结果",QString("得到最小生成树的值为%1").arg(treevalue));
                btn->close();
            });
        });
    }
    else{
        QMessageBox::critical(this,"错误","很抱歉，您的执行方案未能实施");
    }
}
//普利姆算法区域，通过传入输入的具体形式数据转化得到的抽象邻接矩阵，主要得到最小生成树的邻接矩阵
//////////////////////////普利姆算法///////////////////////
int findMinKeyVertex(QVector<int>&key,QVector<bool>&mstSet, const int &n){
    int minkey=INF,minindex;
    for(int v=0;v<n;v++){
        if(!mstSet[v]&&key[v]<minkey){
            minkey=key[v];
            minindex=v;
        }
    }
    return minindex;
}
QVector<QVector<int>> primMST(const QVector<QVector<int>>& m,QVector<int> &P_order){
    int n=m.size();
    QVector<int> parent(n);
    QVector<int>key(n,INF);
    QVector<bool>mstSet(n,false);
    QVector<QVector<int>>mst(n,QVector<int>(n,0));
    key[0]=0;
    parent[0]=-1;
    for(int count=0;count<n-1;count++){
        int u=findMinKeyVertex(key,mstSet,n);
        mstSet[u]=true;
        P_order.append(u);
        for(int v=0;v<n;v++){
            //可排除再次访问已经访问的节点，防止回路//有权值，未被访问，权值小于键值，替换
            if(m[u][v]&&!mstSet[v]&&m[u][v]<key[v]){
                //设置父节点，加入最小生成树
                parent[v]=u;
                key[v]=m[u][v];
            }
        }
    }
    for(int i=1;i<m.size();i++){
        mst[parent[i]][i]=m[i][parent[i]];
        mst[i][parent[i]]=m[i][parent[i]];
    }
    //得到节点访问次序数组
    for(int i=0;i<n;i++){
        if(!mstSet[i]){
            P_order.append(i);
        }
    }
    return mst;
}
////////////////////////////克鲁斯卡尔算法/////////////////////////////////
bool compareEdges(edge e1,edge e2) {
    return e1.weight < e2.weight;
}
// 查找节点的根节点
int findRoot(QVector<int>& parent, int node) {
    if (parent[node] == -1)
        return node;
    return findRoot(parent, parent[node]);
}
// 合并两个节点所在的集合
void unionSets(QVector<int>& parent, int root1, int root2) {
    parent[root1] = root2;
}
QVector<QVector<int>> kruskalMST(const QVector<QVector<int>>& graph,QVector<QPoint> &Kruskal_points,const QVector<QPushButton*> &BTN,QVector<QString> & K_string) {
    Kruskal_points.clear();
    K_string.clear();
    int numNodes = graph.size();
    // 存储所有边的数组
    QVector<edge> edges;
    // 存储最小生成树的邻接矩阵
    QVector<QVector<int>> mst(numNodes, QVector<int>(numNodes, 0));
    // 将邻接矩阵中的边存储到edges数组中
    for (int i = 0; i < numNodes; i++) {
        for (int j = i + 1; j < numNodes; j++) {
            if (graph[i][j] != 0) {
                edge edge;
                edge.start = i;
                edge.end = j;
                edge.weight = graph[i][j];
                edges.push_back(edge);
            }
        }
    }
    // 对边按权重进行排序
    std::sort(edges.begin(), edges.end(), compareEdges);
    // 存储节点的父节点
    QVector<int> parent(numNodes, -1);
    // 记录已选择的边的数量
    int numEdges = 0;
    // 记录当前遍历到的边的索引
    int index = 0;
    // 选择numNodes-1条边，构建最小生成树
    while (numEdges < numNodes - 1) {
        edge nextEdge = edges[index++];
        int root1 = findRoot(parent, nextEdge.start);
        int root2 = findRoot(parent, nextEdge.end);
        // 如果两个节点的根节点不同，则选择该边
        //克鲁斯卡尔的画线顺序，类似普利姆的Prim_points
        if (root1 != root2) {
            mst[nextEdge.start][nextEdge.end] = nextEdge.weight;
            mst[nextEdge.end][nextEdge.start] = nextEdge.weight;
            Kruskal_points.append(BTN[nextEdge.start]->pos());
            K_string.append(BTN[nextEdge.start]->text());
            Kruskal_points.append(BTN[nextEdge.end]->pos());
            K_string.append(BTN[nextEdge.end]->text());
            unionSets(parent, root1, root2);
            numEdges++;
        }
    }
    return mst;
}
/////////////////////////克鲁斯卡尔算法/////////////////////////////
void widget::mousePressEvent(QMouseEvent *ev){
    //限制区域产生节点
    QRect limitedRect(50,50,500,500);
    if(!m_alreadyBuild){
        //如果还没有点击DrawLine按钮，即未完成画点
        Title->setText("绘制好点后请点击画线");
        //在限制区域内
        if(limitedRect.contains(ev->pos())){
            QPushButton *btn=new QPushButton(this);
            BTN.append(btn);
            btn->resize(30,30);
            btn->setText(QString("v%1").arg(count++));
            btn->move(ev->pos());
            btn->setStyleSheet("QPushButton{border-radius:15px;background-color:white;border:3px solid black;}");
            btn->show();
        }
        else{
            QMessageBox::critical(this,"你干嘛~哎呦~","请在区域内画图!!!");
            QWidget::mousePressEvent(ev);
        }
    }
}
//绘图事件
void widget::paintEvent(QPaintEvent *ev){
        //设置背景
        QPainter painter(this);
        QPixmap pix;
        pix.load(":/MainWindow.jpg");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
        //在限制区域绘画
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing,true);
        QRect limitedRect(50,50,500,500);
        p.drawRect(limitedRect);
        p.fillRect(limitedRect,Qt::white);
        p.drawLine(600,0,600,this->height());
        //LINE为存储线条的数组
        for(const auto&line:LINE){
        p.drawLine(line.first,line.second);
        }
        if(m_isButtonPressed&&!m_isget){
        p.drawLine(m_startPoint,m_endPoint);
        }
        if(m_paintPrim&&!m_animation){
        treevalue=0;
        QPen pen(Qt::red);
        pen.setWidth(3);
        p.setPen(pen);
        //通过普利姆最小生成树算法得到邻接矩阵
        QVector<QVector<int>> mm=primMST(this->m,this->P_order);
        //将最小生成树邻接矩阵赋值给成员变量
        this->Prim_m=mm;
        int n=mm.size();
        //绘制最小生成树（红）
         for(int i=0;i<n;i++){
             for(int j=i+1;j<n;j++){
                   if(mm[i][j]){
                        treevalue+=mm[i][j];
                       int x1=BTN[i]->pos().x()+15;
                       int y1=BTN[i]->pos().y()+15;
                       int x2=BTN[j]->pos().x()+15;
                       int y2=BTN[j]->pos().y()+15;
                       p.drawLine(x1,y1,x2,y2);
                                }
                            }
                        }
         //防止误触
        m_paintPrim=false;        
        }
        if(m_paintKruskal&&!m_animation){
        treevalue=0;
        QPen pen(Qt::green);
        pen.setWidth(3);
        p.setPen(pen);
        //通过克鲁斯卡尔最小生成树算法得到邻接矩阵
        QVector<QVector<int>> kk=kruskalMST(this->m,this->Kruskal_points,this->BTN,this->K_string);
        //将最小生成树邻接矩阵赋值给成员变量
        this->Prim_m=kk;
        int k=kk.size();
        //绘制最小生成树（绿）
        for(int i=0;i<k;i++){
            for(int j=i+1;j<k;j++){
                    if(kk[i][j]){
                       treevalue+=kk[i][j];
                       int x1=BTN[i]->pos().x()+15;
                       int y1=BTN[i]->pos().y()+15;
                       int x2=BTN[j]->pos().x()+15;
                       int y2=BTN[j]->pos().y()+15;
                       p.drawLine(x1,y1,x2,y2);
                                }
                            }
        }
        //防止误触
        m_paintKruskal=false;
        }
        //动画按钮，点击Animation，动画板块可执行(蓝)
        if(m_animation&&m_Primdone){
        QPen pen1(Qt::red);
        pen1.setWidth(6);
        p.setPen(pen1);
        //依次绘制线条
        for(int i=0;i<currentlines;i++){
            p.drawLine(Prim_points[2*i].x()+15,Prim_points[2*i].y()+15,Prim_points[i*2+1].x()+15,Prim_points[2*i+1].y()+15);
        if(i==currentlines-1)
            {
                QString str="当前画线: "+P_string[2*i]+" 到 "+P_string[2*i+1];
                draw->setText(str);
            }
        }
        //qDebug()<<"currentlines:"<<currentlines;
        //结束画线操作
        if(currentlines==Prim_points.size()/2){
            m_animation=false;
            qDebug()<<"close";
            //产生一个求权值和按钮
            draw->setText("当前画线：动画执行完毕");
            linestatus->setText("动画结束，正在结算权值和···");
            QTimer::singleShot(2000,[=](){
                linestatus->setText("已生成，请点击获取权和");
                gettreevalue();
            });
        }
        }
        if(m_animation&&m_Kruskaldone){
        QPen pen2(Qt::darkGreen);
        pen2.setWidth(6);
        p.setPen(pen2);
        //依次绘制线条
        for(int i=0;i<currentlines;i++){
            p.drawLine(Kruskal_points[2*i].x()+15,Kruskal_points[2*i].y()+15,Kruskal_points[i*2+1].x()+15,Kruskal_points[2*i+1].y()+15);
            if(i==currentlines-1)
            {
            QString str="当前画线: "+K_string[2*i]+" 到 "+K_string[2*i+1];
            draw->setText(str);
            }
        }
        //结束画线操作
        if(currentlines==Kruskal_points.size()/2){
            m_animation=false;
            qDebug()<<"kruskal close";
            //产生一个求权值和按钮
            draw->setText("当前画线：动画执行完毕");
            linestatus->setText("动画结束，正在结算权值和···");
            QTimer::singleShot(2000,[=](){
                linestatus->setText("已生成，请点击获取权和");
                gettreevalue();
            });
        }
        }
}
//鼠标移动事件：绘制线条
void widget::mouseMoveEvent(QMouseEvent *ev){
    //如果点击了按钮，启动！
    if(m_isButtonPressed){
        //遍历按钮，看鼠标移动到哪一个按钮区域，获得终点
        for(int i=0;i<BTN.size();i++){
            if((ev->pos().x()>=BTN[i]->pos().x()+10)&&(ev->pos().y()>=BTN[i]->pos().y()+10)&&(ev->pos().x()<=BTN[i]->pos().x()+20)&&(ev->pos().y()<=BTN[i]->pos().y()+20)&&!m_isget){
                m_isget=true;
                m_isButtonPressed=false;
                m_endPoint=QPoint(BTN[i]->pos().x()+15,BTN[i]->pos().y()+15);
                end=i;
                //权重
                QLabel *label=new QLabel(this);
                QFont font;
                font.setPointSize(15);
                label->setFont(font);
                label->move((m_startPoint.x()+m_endPoint.x())/2,(m_startPoint.y()+m_endPoint.y())/2);
                bool ok;
                int weight=QInputDialog::getInt(this,"长度输入",QString("请输入节点v%1到节点v%2的权重：").arg(start).arg(end),label->text().toInt(),0,120,1,&ok);
                if(ok){
                    label->setText(QString::number(weight));
                }
                label->show();
                linestatus->setText(QString("连线状态：开始:v%1 结束:v%2   权重:%3").arg(start).arg(end).arg(weight));
                //抽象化为邻接矩阵，后面计算普利姆生成树
                m[start][end]=weight;
                m[end][start]=weight;
                this->lineNum++;
                LINE.append(qMakePair(m_startPoint,m_endPoint));
                update();
            }
        }
        if(!m_isget){
            m_endPoint=ev->pos();
            update();
        }
    }
}
//析构函数，释放内存
widget::~widget()
{
    for(int i=0;i<m.size();i++){
        delete BTN[i];
    }
    delete timer;
   //由于该窗口绑定对象树上，程序结束后随着父亲自动销毁
}

