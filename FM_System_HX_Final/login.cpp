#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    this->ui->lineEdit_username->setText("kylin");
    this->ui->lineEdit_pwd->setText("huan127013");
}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *event)
{
    //背景图设置
    QPainter p(this);
    //pixmap
    p.drawPixmap(0,0,width(),height(),QPixmap(":/images/b.jpg")); //绘制图片
    p.end();
}

//登录按钮响应槽
void Login::on_btn_login_clicked()
{
    QString userName=this->ui->lineEdit_username->text();
    QString pwd=this->ui->lineEdit_pwd->text();
    if(userName=="kylin"&&pwd=="huan127013")
    {
        qDebug()<<"登录成功";
        int res = QMessageBox::information(this,"提示","登录成功");
    }
    else
    {
        int res = QMessageBox::critical(this,"提示","信息错误！");
        return;
    }
    page1.setWindowTitle("家谱管理系统");
    page1.setWindowIcon(QIcon(":/images/fa.png"));  //更改页面的图标
    page1.show();
    this->hide();
}

void Login::on_btn_out_clicked()
{
    int res = QMessageBox::question(this,"提示","是否要关闭窗口？");  //弹出对话框进行确认是否退出
    if (res == QMessageBox::Yes){
        this->close();
    }
    else {
        this->show();
    }
}
