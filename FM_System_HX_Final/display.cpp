#include "display.h"
#include "ui_display.h"

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
}

Display::~Display()
{
    delete ui;
}

void Display::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    //pixmap
    p.drawPixmap(0,0,width(),height(),QPixmap(":/images/snow.jpg")); //绘制图片
    p.end();
}
