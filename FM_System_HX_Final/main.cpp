#include "login.h"
#include<QSplashScreen>
#include <QApplication>
#include<QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/icoo.png"));
    QPixmap pix(":/images/icoo.png");
    QSplashScreen screen(pix);
    screen.show();
    a.processEvents();
    screen.showMessage("LOVE");

    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    do{
        now=QDateTime::currentDateTime();
    } while (n.secsTo(now)<=5);//6为需要延时的秒数

    Login w;
    w.setWindowTitle("登录");
    w.setWindowIcon(QIcon(":/images/ll.png"));  //更改页面的图标
    w.show();

    screen.finish(&w);
    return a.exec();
}
