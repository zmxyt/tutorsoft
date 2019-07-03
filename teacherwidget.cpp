#pragma execution_character_set("utf-8")
#include "teacherwidget.h"
#include "ui_teacherwidget.h"

TeacherWidget::TeacherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherWidget)
{
    ui->setupUi(this);
    //buju
    m_ChildWidgetG = new ChildWidgetG(this);
    m_ChildWidgetH = new ChildWidgetH(this);
    m_ChildWidgetI = new ChildWidgetI(this);
    m_ChildWidgetJ = new ChildWidgetJ(this);
    m_ChildWidgetK = new ChildWidgetK(this);

    ui->stackedWidget->addWidget(m_ChildWidgetG);
    ui->stackedWidget->addWidget(m_ChildWidgetH);
    ui->stackedWidget->addWidget(m_ChildWidgetI);
    ui->stackedWidget->addWidget(m_ChildWidgetJ);
    ui->stackedWidget->addWidget(m_ChildWidgetK);

    ui->stackedWidget->setCurrentWidget(m_ChildWidgetG);
}

TeacherWidget::~TeacherWidget()
{
    delete ui;
}

void TeacherWidget::on_btn_1_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetG);
}

void TeacherWidget::on_btn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetH);
}

void TeacherWidget::on_btn_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetI);
}

void TeacherWidget::on_btn_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetJ);
}

void TeacherWidget::on_btn_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(m_ChildWidgetK);
}

void TeacherWidget::on_btn_quit_clicked()
{
    emit sendQuit();
}
