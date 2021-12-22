#include "family.h"


Family::Family()
{
    this->ancestor->name="";
    this->ancestor->sex="";
    this->ancestor->sexStatus=-1;
    this->ancestor->age=-1;
    this->ancestor->spouseName="";
    this->ancestor->intro="";
    this->ancestor->address="";
    this->ancestor->degree="";
    this->ancestor->birth="";

    this->ancestor->child=nullptr;
    this->ancestor->childrenAmount=0;
    this->ancestor->father=nullptr;
    this->ancestor->brotherPre=nullptr;
    this->ancestor->brotherNext=nullptr;
    this->num++;
}

Family::~Family()
{
    //
}

//寻找成员
Person* Family::FindMember(QString TarName, Person *key)
{
    //如果要查找的人就是祖先的话
    Person* p = key;
    Person* ans = nullptr;
    Person* temp = p;

    if (p->name == TarName)
    {
        qDebug()<<"要找的人就是祖先";
        return p;
    }

    //先从兄弟中找
    while (temp->brotherNext != nullptr)
    {
        //在哥哥兄弟指针中递归查找要查找的结点
        ans = FindMember(TarName,temp->brotherNext);
        if (ans != nullptr)
        {
            return ans;
        }
        temp = temp->brotherNext;
    }

    //再从孩子中找
    temp = p;
    if (temp->child != nullptr)
    {
        ans = FindMember(TarName,temp->child);
    }
    return ans;
}

//初始化新成员
Person* Family::CreateMember()
{
    Person* p = new Person;
    p->name = "";
    p->childrenAmount = 0;
    p->sex="";
    p->sexStatus=-1;
    p->age=-1;
    p->spouseName="";
    p->intro="";
    p->address="";
    p->degree="";
    p->birth="";

    p->father = nullptr;
    p->child = nullptr;
    p->brotherPre = nullptr;
    p->brotherNext = nullptr;

    this->num++;
    return p;
}

//解散局部家庭
void Family::DeleteSmallFamily(QString TarName)
{
    //解散局部小家庭  遣散这一家族分支
    Person* p = FindMember(TarName, ancestor);

    //如果被删人既有哥哥也有弟弟的话
    if (p->brotherPre != nullptr && p->brotherNext != nullptr)
    {
        p->brotherPre->brotherNext = p->brotherNext;    //被删人上一级哥哥的下一级弟弟变更为被删人的下一级弟弟
        p->brotherNext->brotherPre = p->brotherPre;     //被删人弟弟的上一级哥哥等于被删人的上一级哥哥
        p->father->childrenAmount--;                    //被删人的父亲的孩子数量-1
    }

    //如果被删人只有哥哥没有弟弟的话
    if (p->brotherPre != nullptr && p->brotherNext == nullptr)
    {
        p->brotherPre->brotherNext = nullptr;           //被删人的哥哥不再有弟弟
        p->father->childrenAmount--;                    //被删人的父亲的孩子数量-1
    }

    //如果被删人没有哥哥只有弟弟的话
    if (p->brotherPre == nullptr && p->brotherNext != nullptr)
    {
        p->father->child = p->brotherNext;              //被删人的父亲的长子变更为被删人的下一级弟弟
        p->brotherNext->brotherPre = nullptr;           //被删人的下一级弟弟不再有哥哥
        p->father->childrenAmount--;                    //被删人的父亲的孩子数量-1
    }

    //如果被删人既没有哥哥也没有弟弟
    if (p->brotherPre == nullptr && p->brotherNext == nullptr)
    {
        p->father->child = nullptr;                     //被删人的父亲不再有孩子
        p->father->childrenAmount--;                    //被删人的父亲的孩子数量-1
    }

    //

    //删除孩子
    if (p->child != nullptr)
    {
        DeleteMember(p->child);
    }
    this->num--;

    delete(p);

}


void Family::DeleteMember(Person* p)
{
    Person* temp = p;   //111

    //第一个while是找到这一辈分中最小的兄弟结点
    while (temp->brotherNext != nullptr)
    {
        temp = temp->brotherNext;   //112
    }

    //从后往前删除
    while (temp->brotherPre !=nullptr)
    {
        temp = temp->brotherPre;    //111

        temp->brotherNext->brotherPre = nullptr;    //112

        temp->brotherNext->brotherNext = nullptr;

        DeleteMember(temp->brotherNext);
    }


    //删除子结点
    if (temp->child)
    {
        DeleteMember(temp->child);
    }
    this->num--;
    delete p;
}

