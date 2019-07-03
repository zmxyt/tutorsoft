#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

#include <QWidget>
#include "form/childwidgetg.h"
#include "form/childwidgeth.h"
#include "form/childwidgeti.h"
#include "form/childwidgetj.h"
#include "form/childwidgetk.h"

namespace Ui {
class TeacherWidget;
}

class TeacherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherWidget(QWidget *parent = 0);
    ~TeacherWidget();

signals:
    void sendQuit();
private slots:
    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_quit_clicked();

private:
    Ui::TeacherWidget *ui;
    ChildWidgetG *m_ChildWidgetG;
    ChildWidgetH *m_ChildWidgetH;
    ChildWidgetI *m_ChildWidgetI;
    ChildWidgetJ *m_ChildWidgetJ;
    ChildWidgetK *m_ChildWidgetK;
};

#endif // TEACHERWIDGET_H
