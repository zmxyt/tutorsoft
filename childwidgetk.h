#ifndef CHILDWIDGETK_H
#define CHILDWIDGETK_H

#include <QWidget>

namespace Ui {
class ChildWidgetK;
}

class ChildWidgetK : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWidgetK(QWidget *parent = 0);
    ~ChildWidgetK();

protected:
    void showEvent(QShowEvent *event);

private:
    void updateDisplay();
    QVector<QVector<QString>> queryAll(QString tablename);

private slots:
    void onHeaderClicked(int,int);


private:
    Ui::ChildWidgetK *ui;
      int selectrow;
};

#endif // CHILDWIDGETK_H
