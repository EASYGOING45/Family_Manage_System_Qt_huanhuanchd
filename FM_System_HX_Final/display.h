#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>

namespace Ui {
class Display;
}

class Display : public QWidget
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = nullptr);
    ~Display();
    void paintEvent(QPaintEvent *event);

private:
    Ui::Display *ui;
};

#endif // DISPLAY_H
