#pragma execution_character_set("utf-8")
#include "childwidgetg.h"
#include "ui_childwidgetg.h"
#include "../mainwidget.h"
#include "../qxmessagebox/qxmessagebox.h"
#include "../database/userdatabase.h"

ChildWidgetG::ChildWidgetG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChildWidgetG)
{
    ui->setupUi(this);
}

ChildWidgetG::~ChildWidgetG()
{
    delete ui;
}

//QWidget的showEvent方法是在显示前触发的。
void ChildWidgetG::showEvent(QShowEvent *event)
{
    QVector<QVector<QString>>  allinfo = queryAll("teacher_information");
    for(int i =0;i < allinfo.size();i++){
        //currentuser当前用户;Widget部件
        if(MainWidget::currentuser == allinfo.at(i).at(0)){
            //可以设置lineEdit的当前显示文字
            ui->lineEdit_1->setText(allinfo.at(i).at(0));
            ui->lineEdit_2->setText(allinfo.at(i).at(1));
            ui->lineEdit_3->setText(allinfo.at(i).at(2));
            ui->lineEdit_4->setText(allinfo.at(i).at(3));
            ui->lineEdit_5->setText(allinfo.at(i).at(4));
            ui->lineEdit_6->setText(allinfo.at(i).at(5));
            ui->lineEdit_7->setText(allinfo.at(i).at(6));
            ui->lineEdit_8->setText(allinfo.at(i).at(7));
            ui->lineEdit_9->setText(allinfo.at(i).at(8));
        }
    }
}

QVector<QVector<QString>> ChildWidgetG::queryAll(QString tablename)
{
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }
    QSqlQuery query(userDataBasePri::database);
    //作为条件直接在数据库中查找
    QString statement = QString("SELECT * FROM %1").arg(tablename);//记录属性字段名
    query.exec(statement);//查询执行(声明);
    //QVector<T>是Qt普通容器类的一种。它将自己的每个对象存储在连续的内存中。能够使用索引號来高速訪问它们
    QVector<QVector<QString>> retvector;
    QVector<QString> vectorstr;
    int midsize = 0;
    while(query.next())
    {
        vectorstr.clear();
        midsize = query.size();
        for(int i = 0; i < 40;i++ ){
            vectorstr.append(query.value(i).toByteArray());
        }
        retvector.append(vectorstr);
    }
    userDataBasePri::database.close();
    return retvector;
}

void ChildWidgetG::on_btn_resiger_clicked()
{
    //输入：可以读取当前框中所输入的文字
    QString tstr1 = ui->lineEdit_1->text();
    QString tstr2 = ui->lineEdit_2->text();
    QString tstr3 = ui->lineEdit_3->text();
    QString tstr4 = ui->lineEdit_4->text();
    QString tstr5 = ui->lineEdit_5->text();
    QString tstr6 = ui->lineEdit_6->text();
    QString tstr7 = ui->lineEdit_7->text();
    QString tstr8 = ui->lineEdit_8->text();
    QString tstr9 = ui->lineEdit_9->text();
    if (! userDataBasePri::database.open()){//打开数据库
        QXMessageBox message;
        //对话框
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("数据库链接失败!");
        message.exec();
        qCritical() << userDataBasePri::database.lastError().text();
        return;
    }
    QSqlQuery query(userDataBasePri::database);

    QString updataStr = QString("update teacher_information set teacher_name = '%2' "
                                ", teacher_password = '%3' "
                                ", teacher_sex = '%4' "
                                ", teacher_age = '%5' "
                                ", teacher_phone = '%6' "
                                ", teacher_email = '%7' "
                                ", teacher_level = '%8' "
                                ", teacher_info = '%9' "
                                "where teacherid = '%1'")
            .arg(tstr1).arg(tstr2).arg(tstr3)
            .arg(tstr4).arg(tstr5).arg(tstr6)
            .arg(tstr7).arg(tstr8).arg(tstr9);
//arg函数应该是用参数替代字符串中的百分值，从小到大替换，%1--%99
    bool ret = query.exec(updataStr);
    if (ret == false){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("更新失败!");
        message.exec();
    }else{
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("更新成功!");
        message.exec();
    }
    userDataBasePri::database.close();
}
