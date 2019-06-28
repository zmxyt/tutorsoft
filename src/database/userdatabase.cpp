#pragma execution_character_set("utf-8")
/*******************************************
* @className
* @brief         Data Base
*                v1.0
* @author        cql
* @date          2019-01-17
********************************************/

#include "userdatabase.h"
#include <QDebug>
#define DATA_BASE_NAME ("tutorsystem.db")//数据库文件名
QSqlDatabase userDataBasePri::database;
userDataBasePri::userDataBasePri()
{
    if (QSqlDatabase::contains("cql_sqllite")) {//连接数据库
        database = QSqlDatabase::database("cql_sqllite");
    } else {
        database = QSqlDatabase::addDatabase("QSQLITE","cql_sqllite");
    }
    database.setDatabaseName(DATA_BASE_NAME);//设置数据库文件名
    database.setUserName("root");//用户
    database.setPassword("nopassword");//密码-无密码

    if (! database.open()){//打开数据库
        qCritical() << database.lastError().text();
        return;
    }

    QSqlQuery query(database);
    //教师
    bool ret = query.exec(QString::fromLocal8Bit("create table teacher_information(teacherid varchar(20) primary key,teacher_password varchar(20),"
                                                 "teacher_name varchar(50),teacher_sex varchar(10),teacher_age varchar(10),teacher_phone varchar(20),"
                                                 "teacher_email varchar(20),teacher_level varchar(20),teacher_info varchar(200))"));

    query.exec(QString::fromLocal8Bit("insert into teacher_information values('admin','passwd','张三','男','11','15566566556',"
                                      "'44444444@qq.com','小学','高级教师')"));
    query.exec(QString::fromLocal8Bit("insert into teacher_information values('admin1','passwd','张三1','男','11','15566566556',"
                                      "'44444444@qq.com','初中','高级教师')"));
    query.exec(QString::fromLocal8Bit("insert into teacher_information values('admin2','passwd','张三2','男','11','15566566556',"
                                      "'44444444@qq.com','高中','高级教师')"));
    //学生
    ret = query.exec(QString::fromLocal8Bit("create table student_information(studentid varchar(20) primary key,student_password varchar(20),"
                                            "student_name varchar(50),student_sex varchar(10),student_age varchar(10),student_phone varchar(20),"
                                            "student_email varchar(20),student_class varchar(20))"));
    query.exec(QString::fromLocal8Bit("insert into student_information values('admin','passwd','张三','男','11','15566566556',"
                                      "'44444444@qq.com','5年级')"));
    database.close();
    createStudentLoan("admin");
    createTeacherLoan("admin");
    qDebug()<<"ddddddddd"<<ret;
}

userDataBasePri::~userDataBasePri()
{

}

QVector<QVector<QString> > userDataBasePri::findTablenameRecord(QString tablename)
{
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }
    QSqlQuery query(userDataBasePri::database);
    QString statement = QString("SELECT * FROM %1").arg(tablename);
    query.exec(statement);
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

bool userDataBasePri::createStudentLoan(QString id)
{
    if (!database.open()){//打开数据库
        return 0;
    }
    bool ret = false;
    QString t_str = "student_" + id + "_information";
    QSqlQuery query(database);
    ret = query.exec(QString::fromLocal8Bit("create table %1(needid varchar(50) primary key,need_name varchar(50),course varchar(50),start_time varchar(50),stop_time varchar(50),cost varchar(50),needgrade varchar(50),needstr varchar(200),teachername varchar(10))").arg(t_str));
    database.close();
    return ret;
}

bool userDataBasePri::createTeacherLoan(QString id)
{
    if (!database.open()){//打开数据库
        return 0;
    }
    bool ret = false;
    QString t_str = "teacher_" + id + "_information";
    QSqlQuery query(database);
    ret = query.exec(QString::fromLocal8Bit("create table %1(acceptid varchar(50) primary key,needid varchar(50),need_name varchar(50),course varchar(50),start_time varchar(50),stop_time varchar(50),cost varchar(50),needgrade varchar(50),needstr varchar(200))").arg(t_str));
    database.close();
    return ret;
}

QVector<QVector<QString>> userDataBasePri::queryAll(QString tablename)
{
    if (! userDataBasePri::database.open()){//打开数据库
        qCritical() << userDataBasePri::database.lastError().text();
    }
    QSqlQuery query(userDataBasePri::database);
    QString statement = QString("SELECT * FROM %1").arg(tablename);
    query.exec(statement);
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
