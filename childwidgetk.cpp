#pragma execution_character_set("utf-8")
#include "childwidgetk.h"
#include "ui_childwidgetk.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../database/userdatabase.h"
#define TAB_WIDGET_STYLE "QHeaderView::section{background:gray;color: white; \
padding-left: 5px; \
border-left:0px solid #000; \
border-right:1px solid white; \
border-top:0px solid #000; }"

//tian jia shu ju
ChildWidgetK::ChildWidgetK(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetK)
{
    // setupUi(this)是由.ui文件生成的类的构造函数，作用是对界面进行初始化，

    // 它按照Qt设计器里设计的样子把窗体画出来，把Qt设计器里面定义的信号和槽建立起来。

    // 也可以说，setupUi是界面和写程序之间的桥梁。
    ui->setupUi(this);

    selectrow = 0;
    //设置列数
    //创建表格头
    QStringList header;
    header  << "编号" << "学生编号" << "需求名称"<<"科目"<<"开始时间"<<"结束时间"<<"费用"<<"年级"<<"需求说明";
    ui->tableWidget->setColumnCount(9);//hangshu
    ui->tableWidget->setHorizontalHeaderLabels(header);//创建表格头
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格为整行选中
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//选中单个目标
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许双击修改表格
    //有滚动条的控件都有setVerticalScrollBarPolicy和setHorizontalScrollBarPolicy函数
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条

    ui->tableWidget->horizontalHeader()->setFixedHeight(50);//设置表头的高度
    ui->tableWidget->horizontalHeader()->resizeSection(0,ui->tableWidget->width()*0.1);//biao kuan du
    ui->tableWidget->horizontalHeader()->resizeSection(1,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(2,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(3,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(4,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(5,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(6,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(7,ui->tableWidget->width()*0.1);
    ui->tableWidget->horizontalHeader()->resizeSection(8,ui->tableWidget->width()*0.2);
    ui->tableWidget->horizontalHeader()->setStyleSheet(TAB_WIDGET_STYLE);//设置表头背景色

    ui->tableWidget->verticalHeader()->setHidden(true);//行名隐藏
    //函数函数：setSectionResizeMode()，表示均匀拉直表头
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//Fixed(固定);Stretch(拉伸)
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);//设置行高
    updateDisplay();

//加一个信号,当用户选中某一行时,提取该行的数据并执行相应操作
    //连接表头的信号和槽
    connect(ui->tableWidget, SIGNAL(cellClicked(int , int )),
            this, SLOT(onHeaderClicked(int,int)));
}

ChildWidgetK::~ChildWidgetK()
{
    delete ui;
}


//
void ChildWidgetK::showEvent(QShowEvent *event)
{
    updateDisplay();
}

void ChildWidgetK::updateDisplay()
{
    QString tstr0 = "teacher_" + MainWidget::currentuser + "_information";
    ui->tableWidget->clearContents();//只清除表格中的数据，不包括表头名称
    QVector<QVector<QString>>  allinfo = queryAll(tstr0);//queryAll()查询所有信息
    //cha ru shu ju
    ui->tableWidget->setRowCount(allinfo.size());//allinfo.size()所有信息daxiao
    //setRowCount()增加行数
    for(int i =0;i < allinfo.size();i++){
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(allinfo.at(i).at(0)));//设置文本
        //QTableWidget是QT程序中常用的显示数据表格的空间,
        //设置具体单元格的值 ui.qtablewidget->setItem(1, 0, new QTableWidgetItem(str));
        //QTableWidgetItem用来表示表格中的一个单元格，正个表格都需要用逐个单元格构建起来。
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(allinfo.at(i).at(1)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(allinfo.at(i).at(2)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(allinfo.at(i).at(3)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(allinfo.at(i).at(4)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(allinfo.at(i).at(5)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(allinfo.at(i).at(6)));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(allinfo.at(i).at(7)));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(allinfo.at(i).at(8)));
    }
}

QVector<QVector<QString> > ChildWidgetK::queryAll(QString tablename)
{
    if (! userDataBasePri::database.open()){//打开数据库
        //qCritical: 严重错误提示
        qCritical() << userDataBasePri::database.lastError().text();
    }

    QSqlQuery query(userDataBasePri::database);
    QString statement = QString("SELECT * FROM %1").arg(tablename);
    query.exec(statement);
    QVector<QVector<QString>> retvector;
    QVector<QString> vectorstr;
    int midsize = 0;
    while(query.next())//查询
    {
        vectorstr.clear();
        midsize = query.size();
        for(int i = 0; i < 40;i++ ){
            vectorstr.append(query.value(i).toByteArray());
        }//使用append()添加文本
        retvector.append(vectorstr);
    }
    userDataBasePri::database.close();
    return retvector;
}

//onHeaderClicked在标题点击
void ChildWidgetK::onHeaderClicked(int row,int column)//column栏
{
    selectrow = row;
}
