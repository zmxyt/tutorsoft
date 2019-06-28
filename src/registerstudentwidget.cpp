#pragma execution_character_set("utf-8")
#include "registerstudentwidget.h"
#include "ui_registerstudentwidget.h"
#include "qxmessagebox/qxmessagebox.h"
#include "database/userdatabase.h"

RegisterStudentWidget::RegisterStudentWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterStudentWidget)
{
    ui->setupUi(this);
    setWindowTitle("注册学生信息");
}

RegisterStudentWidget::~RegisterStudentWidget()
{
    delete ui;
}

void RegisterStudentWidget::on_btn_resiger_clicked()
{
    QString tstr1 = ui->lineEdit_1->text();
    QString tstr2 = ui->lineEdit_2->text();
    QString tstr3 = ui->lineEdit_3->text();
    QString tstr4 = ui->lineEdit_4->text();
    QString tstr5 = ui->lineEdit_5->text();
    QString tstr6 = ui->lineEdit_6->text();
    QString tstr7 = ui->lineEdit_7->text();
    QString tstr8 = ui->lineEdit_8->text();

    if (! userDataBasePri::database.open()){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("数据库链接失败!");
        message.exec();
        qCritical() << userDataBasePri::database.lastError().text();
        return;
    }
    QSqlQuery query(userDataBasePri::database);

    QString insertser = QString("insert into student_information values(%1,%2,%3,%4,%5,%6,%7,%8)")
            .arg(tstr1).arg(tstr3).arg(tstr2)
            .arg(tstr4).arg(tstr5).arg(tstr6)
            .arg(tstr7).arg(tstr8);
    bool ret = query.exec(insertser);
    if (ret == false){//打开数据库
        QXMessageBox message;
        message.setlabelTitleStr("提示!");
        message.setlabelMsgStr("注册失败!");
        message.exec();
    }else{
        userDataBasePri::createStudentLoan(tstr1);
    }
    userDataBasePri::database.close();
}

void RegisterStudentWidget::on_btn_quit_clicked()
{
    done(0);
}
