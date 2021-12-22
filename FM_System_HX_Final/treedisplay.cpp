#include "treedisplay.h"
#include "ui_treedisplay.h"

//样式表
const QString VSCROLLBAR_STYLE =
        "QTreeWidget{background: #1d1d1d;border: 1px solid #3c3c3c;border-radius: 4px;color:#ffffff;}";


TreeDisplay::TreeDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeDisplay)
{
    ui->setupUi(this);
    this->InitTreeStructure();
    ui->treeWidget->setStyleSheet(VSCROLLBAR_STYLE);    //为TreeWidget应用样式表
}

TreeDisplay::~TreeDisplay()
{
    delete ui;
}

/**
 * 函数功能：初始化QTreeWidget的结构表头
 * 输入参数：无
 * 输出参数：无
 * 返回值：  void
 * 调用关系：调用Qt内置API setHeaderLabels()
 */
void TreeDisplay::InitTreeStructure()
{
    //初始化树表结构
    QStringList strList;
    strList<<"姓名"<<"性别"<<"年龄"<<"配偶姓名";
    this->ui->treeWidget->setHeaderLabels(strList);
}

void TreeDisplay::AddItemTest()
{
    QString name="张起灵";
    QString sex="男";
    int age=100;
    QString agee=QString::number(age);
    QStringList testList;
    testList<<name<<sex<<agee;
    QTreeWidgetItem* item1=new QTreeWidgetItem(testList);
    this->ui->treeWidget->addTopLevelItem(item1);
}


/**
 * 函数功能：在QTreeWidget中初始化先祖结点
 * 输入参数：先祖相关信息
 * 输出参数：是否添加成功 弹窗提示
 * 返回值：  void
 * 调用关系：无
 */
void TreeDisplay::InitAncestor(QString iname, QString isex, QString iage,QString spouseName)
{
    QStringList strList;
    strList<<iname<<isex<<iage<<spouseName;

    //初始化家族树的结点信息
    this->f1.ancestor->name=iname;
    this->f1.ancestor->sex=isex;
    this->f1.ancestor->age=iage.toInt();
    this->f1.ancestor->spouseName=spouseName;

    topItem=new QTreeWidgetItem(strList);
    this->ui->treeWidget->addTopLevelItem(topItem);

    //将QTreeWidgetItem与人类结构体Person绑定
    topItem->setData(0,Qt::UserRole+1,QVariant::fromValue(f1.ancestor));
    Person* tem=topItem->data(0,Qt::UserRole+1).value<Person*>();
    qDebug()<<"背后的结点信息:"<<tem->name<<" "<<tem->sex<<" "<<tem->age;
    qDebug()<<topItem->text(0);
}


/**
 * 函数功能：在QTreeWidget中寻找对应的Item
 * 输入参数：目标姓名    范围根结点
 * 输出参数：无
 * 返回值：  void
 * 调用关系：递归算法调用自身 深度优先
 */
QTreeWidgetItem* TreeDisplay::FindTreeItem(QString targetName, QTreeWidgetItem *father)
{
    //如果要查找的结点就是顶层结点的话
    QTreeWidgetItem* p=father;
    QTreeWidgetItem* ans=nullptr;
    QTreeWidgetItem* temp=p;

    if(p->text(0)==targetName)      //递归终止条件
    {
        qDebug()<<"找到了";
        return p;
    }

     //深度优先遍历查找
    while(temp->child(0)!=nullptr)
    {
        int count=temp->childCount();   //调用API 设置循环次数
        for(int i=0;i<count;i++)
        {
            ans=FindTreeItem(targetName,temp->child(i));    //递归调用
            if(ans!=nullptr)
            {
                qDebug()<<"找到了"<<endl;
                return ans;
            }
        }
        temp=temp->child(0);
    }
    return ans;
}

void TreeDisplay::InitMember(Person *father, Person *self)
{
    QTreeWidgetItem* fa=FindTreeItem(father->name,this->topItem);
    QStringList strList;
    strList<<self->name<<self->sex<<QString::number(self->age)<<self->spouseName;

    QTreeWidgetItem* newItem=new QTreeWidgetItem(strList);
    fa->addChild(newItem);

    newItem->setData(0,Qt::UserRole+1,QVariant::fromValue(self));
    Person* tem=newItem->data(0,Qt::UserRole+1).value<Person*>();
    qDebug()<<"Behind:"<<tem->name<<" "<<tem->sex<<" "<<tem->age;

    Person* temp=father;
    temp = temp->child;
    if (father->child == nullptr)    //如果该家长之前没有孩子的话
    {
        father->child = self;       //上下级相接 很关键
        return;
    }

    while (temp->brotherNext != nullptr)
    {
        //直到找到最小的弟弟
        temp = temp->brotherNext;
    }
    temp->brotherNext = self;
}

void TreeDisplay::paintEvent(QPaintEvent *event)
{
    //背景图设置
    QPainter p(this);
    //pixmap
    p.drawPixmap(0,0,width(),height(),QPixmap(":/images/sn.jpeg")); //绘制图片
    p.end();
}

/**
 * 函数功能：添加成员按钮对应的槽函数
 * 输入参数：接收输入框的数据并传递
 * 输出参数：是否成功 弹窗提示 异常情况也会弹窗
 * 返回值：  void
 * 调用关系：调用FindMember()  查找是否存在该人  FindItem()找到结点
 */
void TreeDisplay::on_btn_add_clicked()
{
    //获取用户输入
    QString input_Name=this->ui->Edit_name->text();
    QString input_Father=this->ui->Edit_father->text();
    QString input_Sex=this->ui->Edit_sex->text();
    QString input_Age=this->ui->Edit_age->text();
    QString input_spouse=this->ui->Edit_spouse->text();

    //如果输入信息不健全
    if(input_Name=="")
    {
        int res = QMessageBox::critical(this,"提示","必须输入姓名！");       //弹出消息提示框
        //Critical 警告    information 信息提示  question  询问
        return;
    }
    //校验信息合法性
    if(input_Sex!="男" && input_Sex!="女")
    {
        int res = QMessageBox::critical(this,"提示","性别信息有误！");
        return;
    }
    //如果添加的是祖先的话
    if(input_Father=="")
    {
        qDebug()<<"要添加的是祖先";
        if(topItem!=nullptr)
        {
            int res = QMessageBox::critical(this,"提示","祖先已有！");
            return;
        }
        InitAncestor(input_Name,input_Sex,input_Age,input_spouse);
        int res = QMessageBox::information(this,"提示","先祖结点添加成功！");
        return ;
    }
    //查找父亲是否存在
    Person* p=f1.FindMember(input_Father,this->f1.ancestor);
    if(p==nullptr)
    {
        int res = QMessageBox::critical(this,"提示","父亲不存在！");
        return;
    }
    Person* newp=this->f1.CreateMember();
    newp->father=p;     //指定父亲  接链操作
    newp->name=input_Name;
    newp->age=input_Age.toInt();
    newp->sex=input_Sex;
    newp->spouseName=input_spouse;
    InitMember(p,newp);     //初始化一般成员
    int res = QMessageBox::information(this,"提示","子代结点添加成功！");
}


//单击树控件item
void TreeDisplay::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //设置文本
    this->ui->change_name->setText(item->text(0));
    this->ui->change_age->setText(item->text(2));
    this->ui->change_spouse->setText(item->text(3));
    this->tempItem=item;

    Person* tem=tempItem->data(0,Qt::UserRole+1).value<Person*>();
    qDebug()<<"Behind:"<<tem->name<<" "<<tem->sex<<" "<<tem->age;
}

void TreeDisplay::on_btn_change_clicked()
{
    if(tempItem==nullptr)
    {
        qDebug()<<"请选中要修改的结点";
        int res = QMessageBox::critical(this,"提示","请选中要修改的结点！");
        return;
    }
    tempItem->setText(0,this->ui->change_name->text());
    tempItem->setText(2,this->ui->change_age->text());
    tempItem->setText(3,this->ui->change_spouse->text());

    Person* temm=tempItem->data(0,Qt::UserRole+1).value<Person*>();
    temm->name=this->ui->change_name->text();
    temm->age=this->ui->change_age->text().toInt();
    temm->spouseName=this->ui->change_spouse->text();
    int res = QMessageBox::information(this,"提示","修改成功！");
}

void TreeDisplay::on_btn_delete_clicked()
{
    if(tempItem==nullptr)
    {
        qDebug()<<"请选中要修改的结点";
        int res = QMessageBox::critical(this,"提示","请选中要修改的结点！");
        return;
    }

    if(tempItem==topItem)
    {
        qDebug()<<"祖先结点不可删除";
        int res = QMessageBox::critical(this,"提示","祖先结点不可删除！");
        return;
    }
    QString TarName=tempItem->text(0);
    tempItem->parent()->removeChild(tempItem);
    this->f1.DeleteSmallFamily(TarName);
    tempItem=nullptr;
    int res = QMessageBox::information(this,"提示","删除成功！");
}

void TreeDisplay::on_btn_analysis_clicked()
{
    this->ui->info_num->setText(QString::number(this->f1.num));
    //this->ui->info_sexrate->setText(QString::number(this->f1.num_man));
    this->ui->info_ancestor->setText(this->f1.ancestor->name);
}

//双击QTreeWidgetItem后 相关信息会展示再完善信息部分内
void TreeDisplay::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    //为信息部分的编辑框设置文本
    Person* temm=tempItem->data(0,Qt::UserRole+1).value<Person*>();
    this->ui->label_name->setText(temm->name);
    this->ui->label_sex->setText(temm->sex);
    this->ui->Edit_birth->setText(temm->birth);
    this->ui->Edit_Address->setText(temm->address);
    this->ui->Edit_Degree->setText(temm->degree);
    this->ui->Edit_Intro->setText(temm->intro);
    AnoItem=item;
}

void TreeDisplay::on_btn_refine_clicked()
{
    QString n_Birth=this->ui->Edit_birth->text();
    QString n_Degree=this->ui->Edit_Degree->text();
    QString n_Intro=this->ui->Edit_Intro->text();
    QString n_Address=this->ui->Edit_Address->text();

    if(AnoItem==nullptr)
    {
        int res = QMessageBox::critical(this,"提示","请选中要完善的结点！");
        return;
    }

    //校验参数完整度
    Person* temm=AnoItem->data(0,Qt::UserRole+1).value<Person*>();
    temm->birth=n_Birth;
    temm->degree=n_Degree;
    temm->intro=n_Intro;
    temm->address=n_Address;
    int res = QMessageBox::information(this,"提示","完善成功！");
}

void TreeDisplay::on_btn_search_clicked()
{
    QString TarName=this->ui->Edit_Search->text();
    if(TarName=="")
    {
        int res = QMessageBox::critical(this,"提示","请输入要查找的人的姓名！");
        return;
    }
    Person* temp=this->f1.FindMember(TarName,f1.ancestor);
    if(temp==nullptr)
    {
        int res = QMessageBox::critical(this,"提示","查无此人！");
        return;
    }
    this->ui->search_name->setText(temp->name);
    this->ui->search_sex->setText(temp->sex);
    this->ui->search_spouse->setText(temp->spouseName);
    this->ui->search_age->setText(QString::number(temp->age));
    this->ui->search_degree->setText(temp->degree);
    this->ui->search_address->setText(temp->address);
    this->ui->search_intro->setText(temp->intro);
    this->ui->search_birth->setText(temp->birth);

}

void TreeDisplay::on_btn_show_clicked()
{
    this->page2.setWindowTitle("关于我们");
    page2.setWindowIcon(QIcon(":/images/about.png"));  //更改页面的图标
    this->page2.show();
}
