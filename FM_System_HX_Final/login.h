#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QPainter>   //绘图工具   画笔 画刷
#include<QString>    //字符串
#include<QDebug>     //调试，输出打印
#include<QMessageBox>   //确认是否退出
#include<QIcon>
#include"treedisplay.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void paintEvent(QPaintEvent *event);   //背景图片的绘制  drawpixmap

private slots:
    void on_btn_login_clicked();


    void on_btn_out_clicked();

private:
    Ui::Login *ui;
    TreeDisplay page1;
};
#endif // LOGIN_H
