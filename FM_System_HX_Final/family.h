#ifndef FAMILY_H
#define FAMILY_H

#include<iostream>
#include<QString>
#include<QDebug>

struct Person:public QObjectUserData
{
    //个人基本信息
    QString name;
    QString sex;
    int sexStatus;  //数字便于判断
    int age;
    QString spouseName; //配偶姓名
    QString address;    //籍贯
    QString intro;      //个人简介
    QString degree;     //学历
    QString birth;  //生日

    //家庭相关信息
    int childrenAmount;     //该家庭成员孩子个数
    Person* father;         //父指针
    Person* brotherNext;    //弟弟（妹妹）们
    Person* brotherPre;     //哥哥（姐姐）们
    Person* child;          //孩子指针 特指长子
};

//声明自定义数据类型
Q_DECLARE_METATYPE(Person)
Q_DECLARE_METATYPE(Person*)

class Family
{
public:
    Family();                       //构造函数 创建家族 也就是初始化祖先的信息
    ~Family();                      //销毁家族 这一操作不需要人为实现
    void AddMember();               //添加家族成员  具体操作为添加为谁谁谁的孩子
    Person* FindMember(QString TarName,Person* key);          //寻找家族成员并展示其信息
    void ChildrenInit();            //为家族成员初始化其孩子的信息
    void ShowInfo();                //展示家族信息概览
    void FindAndShow();             //寻找并展示其孩子信息
    void ChangeMemberInfo();        //更改某一成员的信息
    Person* CreateMember();         //创建家族成员并返回
    void ShowChild(Person* parent);  //展示p的第一代子女
    void DeleteSmallFamily(QString TarName);        //解散局部家庭
    void DeleteMember(Person* p);   //删除成员

    Person* ancestor=new Person;
    int num=0;
};

#endif // FAMILY_H
