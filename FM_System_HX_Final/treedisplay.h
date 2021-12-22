#ifndef TREEDISPLAY_H
#define TREEDISPLAY_H

#include <QWidget>
#include<QDebug>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include<QStringList>
#include<QMessageBox>
#include<QPaintEvent>
#include<QPainter>
#include"display.h"
#include"family.h"

namespace Ui {class TreeDisplay;}

class TreeDisplay : public QWidget
{
    Q_OBJECT

public:
    Family f1;      //家族对象
    explicit TreeDisplay(QWidget *parent = nullptr);
    ~TreeDisplay(); //析构
    void InitTreeStructure();   //初始化树的表头
    void AddItemTest();         //测试
    void InitAncestor(QString iname,QString isex,QString iage,QString spouseName);  //初始化祖先
    QTreeWidgetItem* FindTreeItem(QString targetName,QTreeWidgetItem* father);      //寻找控件树中的结点
    void InitMember(Person* father,Person* self);                                   //初始化成员
    void paintEvent(QPaintEvent *event);                        //绘制背景
    Display page2;              //关于我们页面
private slots:
    void on_btn_add_clicked();  //添加按钮
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_btn_change_clicked();   //修改按钮
    void on_btn_delete_clicked();   //删除按钮
    void on_btn_analysis_clicked(); //统计按钮
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_btn_refine_clicked();
    void on_btn_search_clicked();
    void on_btn_show_clicked();
private:
    Ui::TreeDisplay *ui;
    QTreeWidgetItem *topItem=nullptr;   //顶层结点
    QTreeWidgetItem* tempItem=nullptr;
    QTreeWidgetItem* AnoItem=nullptr;
};

#endif // TREEDISPLAY_H
