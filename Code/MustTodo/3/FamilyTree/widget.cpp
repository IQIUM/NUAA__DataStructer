#include "widget.h"
#include "ui_widget.h"
#include "FamilyTree.h"
#include "readFile.h"
#include "Person.h"
#include <QDebug>
#include <QPushButton>
#include <QPainter>
#include <QFont>
#include <QDialog>
#include <QPlainTextEdit>
#include <string>
#include <QMessageBox>
#include <QGridLayout>
#include <math.h>
using namespace std;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ft = new FamilyTree();
    readFile(ft->root);
    flag = false;
}

Widget::~Widget()
{
    delete ui;
}


/**
 * @brief Widget::on_pushButton_8_clicked
 * 取消
 */
void Widget::on_pushButton_8_clicked()
{
    this->close();
}

/**
 * @brief Widget::on_pushButton_clicked
 * 家谱显示
 */
void Widget::on_pushButton_clicked()
{
    print();
    flag = true;
    update();
}

/**
 * @brief Widget::Coordinate
 * 计算每个人的坐标
 */
void Widget::Coordinate()
{
    if(ft->root == NULL){
        return;
    }
    queue<Person *> que;
    que.push(ft->root);
    int x = 10;
    int y = 0;
    int size = 0;
    int preGener = 0;

    while (!que.empty()) {
        Person* front = que.front();
        if(front->generation != preGener){
            y += 100;
            x = 10;
            size = que.size();
            preGener = front->generation;
        }
        if(front->generation == 1){
            x += 550 / (float)(size + 1) ;
            front->x = x;
            front->y = 10;
            y = 20;
        } else {
            x += 550 / (float)(size + 1) ;
            front->x = x;
            front->y = y;
        }
        que.pop();
        for (int i = 0; i < front->count; ++i) {
            que.push(front->children[i]);
        }
    }
}

/**
 * @brief Widget::print
 * 标签显示
 */
void Widget::print()
{
    Coordinate();

    if(ft->root == NULL){
        return;
    }

    QFont font("SimSun", 10, 75);
    queue<Person* > que;

    que.push(ft->root);
    while (!que.empty()) {
        Person* front = que.front();
        que.pop();
        QLabel* label = new QLabel(ui->container);
        QString content(front->name.c_str());
        label->setText(content);
        label->setFont(font);
        label->setGeometry(front->x,front->y,60,40);
        label->show();
        for (int i = 0; i < front->count; ++i) {
            que.push(front->children[i]);
        }
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    if(!flag || !ft->root){
        return;
    }

    QPainter painter(this);
    QPen pen;  // creates a default pen

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);

    queue<Person* > que;
    que.push(ft->root);
    while (!que.empty()) {
        Person* front = que.front();
        que.pop();
        if(front->parent != NULL) {
            painter.drawLine(QPoint(front->parent->x + 20,front->parent->y + 20),QPoint(front->x+20,front->y+20));
        }
        for (int i = 0; i < front->count; ++i) {
            que.push(front->children[i]);
        }
    }
}


/**
 * @brief Widget::removeLabel
 * 在对页面标签进行删除或者修改时，要把所有标签删除完了再去重新构建
 */
void Widget::removeLabel()
{
    QList<QLabel*> btns = ui->container->findChildren<QLabel*>();
    foreach(QLabel* btn, btns)
    {
        delete btn;
    }

}


/**
 * @brief Widget::on_pushButton_2_clicked
 * 显示第n代人所有信息
 */
void Widget::on_pushButton_2_clicked()
{
    dialog= new ShowNDialog();
    dialog->show();
    dialog->exec();

    this->value = dialog->value;

    int n = this->value;
    queue<Person *> que;
    if(!ft->root){
        QMessageBox::information(NULL, "查找", "家谱人员显示非法！" , QMessageBox::Yes);
        return;
    }
    que.push(ft->root);

    int x = 20;
    int y = 100;
    this->hide();

    if(n <= 0){
        QMessageBox::information(NULL, "查找", "输入有误，请输入重试！", QMessageBox::Yes);
        this->show();
    } else{

        showNGeneration = new ShowNGeneration();
        showNGeneration->show();
        QString num = QString::number(n);
        QString title("显示第 " + num + " 代人所有信息");
        showNGeneration->setWindowTitle(title);
        showNGeneration->resize(800,800);
        showNGeneration->parent = this;

        while (!que.empty()) {
            Person *p = que.front();
            que.pop();
            if (p->generation == n) {

                QFont font("SimSun", 10);
                QString name1(p->name.c_str());
                QString sex(p->sex.c_str());
                QString year = QString::number(p->birthday.year);
                QString month = QString::number(p->birthday.month);
                QString day = QString::number(p->birthday.day);
                QString isMarrige;
                isMarrige = p->marriage?"已婚":"未婚";
                QString address = QString::fromStdString(p->address);
                QString health = p->live?"健在":"死亡";
                QString content;
                if(p->live){
                    content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health);
                }else{
                    QString die_year = QString::number(p->dieDay.year);
                    QString die_month = QString::number(p->dieDay.month);
                    QString die_day = QString::number(p->dieDay.day);

                    content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8  死亡日期：%9年%10月%11日").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health).arg(die_year).arg(die_month).arg(die_day);
                }
                QLabel* label = new QLabel(showNGeneration);
                label->setText(content);
                label->setFont(font);
                label->setGeometry(x,y,800,60);
                y += 50;
                label->show();
            } else {
                for (int i = 0; i < p->count; i++) {
                    que.push(p->children[i]);
                }
            }
        }

    }
}

/**
 * @brief Widget::on_pushButton_3_clicked
 * 按姓名查找
 */

void Widget::on_pushButton_3_clicked()
{
    showNameDialog = new ShowNameDialog();
    showNameDialog->show();
    showNameDialog->exec();

    QString name = showNameDialog->name;

    queue<Person *> que;
    if(!ft->root){
        QMessageBox::information(NULL, "查找", "家谱人员查找失败！" , QMessageBox::Yes);
        return;
    }
    que.push(ft->root);
    Person *p = NULL;
    while (!que.empty()) {
        Person *q = que.front();
        que.pop();
        QString tmpname = QString::fromStdString(q->name);
        if (QString::compare(name,tmpname) == 0) {
            p = q;
            break;
        }
        for (int i = 0; i < q->count; i++) {
            que.push(q->children[i]);
        }
    }
    if(!p){
        QMessageBox::information(NULL, "查找", "未找到此人，请输入重试！", QMessageBox::Yes);
    } else{
        showNGeneration = new ShowNGeneration();
        showNGeneration->show();
        QString title("显示 " + name + " 代人所有信息");
        showNGeneration->setWindowTitle(title);
        showNGeneration->resize(800,800);
        showNGeneration->parent = this;

        QFont font("SimSun", 10);
        QFont font1;
        font1.setPointSize(15);
        font1.setFamily("SimSun");
        QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::red);

        QString name1(p->name.c_str());
        QString sex(p->sex.c_str());
        QString year = QString::number(p->birthday.year);
        QString month = QString::number(p->birthday.month);
        QString day = QString::number(p->birthday.day);
        QString isMarrige = p->marriage?"已婚":"未婚";
        QString address = QString::fromStdString(p->address);
        QString health = p->live?"健在":"死亡";
        QString content;
        if(p->live){
            content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health);
        }else{
            QString die_year = QString::number(p->dieDay.year);
            QString die_month = QString::number(p->dieDay.month);
            QString die_day = QString::number(p->dieDay.day);

            content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8  死亡日期：%9年%10月%11日").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health).arg(die_year).arg(die_month).arg(die_day);
        }
        QLabel* label = new QLabel(showNGeneration);
        label->setText(content);
        label->setFont(font);
        label->setGeometry(50,100,600,60);
        label->show();

        QLabel* label1 = new QLabel(showNGeneration);
        label1->setText("本人：  ");
        label1->setFont(font1);
        label1->setGeometry(50,50,60,60);
        label1->setPalette(pe);
        label1->show();

        //显示父亲
        Person* tmp = p;
        if(p->parent){
            QLabel* label1 = new QLabel(showNGeneration);
            label1->setText("父亲：  ");
            label1->setFont(font1);
            label1->setGeometry(50,150,60,60);
            label1->setPalette(pe);
            label1->show();

            p = p->parent;
            QString name1(p->name.c_str());
            QString sex(p->sex.c_str());
            QString year = QString::number(p->birthday.year);
            QString month = QString::number(p->birthday.month);
            QString day = QString::number(p->birthday.day);
            QString isMarrige = p->marriage?"已婚":"未婚";
            QString address = QString::fromStdString(p->address);
            QString health = p->live?"健在":"死亡";
            QString content;
            if(p->live){
                content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health);
            }else{
                QString die_year = QString::number(p->dieDay.year);
                QString die_month = QString::number(p->dieDay.month);
                QString die_day = QString::number(p->dieDay.day);

                content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8  死亡日期：%9年%10月%11日").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health).arg(die_year).arg(die_month).arg(die_day);
            }
            QLabel* label = new QLabel(showNGeneration);
            label->setText(content);
            label->setFont(font);
            label->setGeometry(50,200,600,60);
            label->show();
        }


        {
            if(tmp->count != 0)
            {
                QLabel* label1 = new QLabel(showNGeneration);
                label1->setText("孩子：  ");
                label1->setFont(font1);
                label1->setGeometry(50,250,60,60);
                label1->setPalette(pe);
                label1->show();
            }
            p = tmp;
            for (int i = 0; i < tmp->count; ++i) {
                p = tmp->children[i];
                QString name1(p->name.c_str());
                QString sex(p->sex.c_str());
                QString year = QString::number(p->birthday.year);
                QString month = QString::number(p->birthday.month);
                QString day = QString::number(p->birthday.day);
                QString isMarrige = p->marriage?"已婚":"未婚";
                QString address = QString::fromStdString(p->address);
                QString health = p->live?"健在":"死亡";
                QString content;
                if(p->live){
                    content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health);
                }else{
                    QString die_year = QString::number(p->dieDay.year);
                    QString die_month = QString::number(p->dieDay.month);
                    QString die_day = QString::number(p->dieDay.day);

                    content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8  死亡日期：%9年%10月%11日").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health).arg(die_year).arg(die_month).arg(die_day);
                }
                QLabel* label = new QLabel(showNGeneration);
                label->setText(content);
                label->setFont(font);
                label->setGeometry(50,200 + 100 * (i + 1),600,60);
                label->show();
            }
        }

    }
}

/**
 * @brief Widget::on_pushButton_4_clicked
 * 根据生日查询
 */
void Widget::on_pushButton_4_clicked()
{
    showBirthdayDialog = new ShowBirthdayDialog();
    showBirthdayDialog->show();
    showBirthdayDialog->exec();

    int _year = showBirthdayDialog->year;
    int _month = showBirthdayDialog->month;

    queue<Person *> que;
    if(!ft->root){
        QMessageBox::information(NULL, "查找", "家谱人员查找失败！！" , QMessageBox::Yes);
        return;
    }
    que.push(ft->root);
    showNGeneration = new ShowNGeneration();
    showNGeneration->resize(800,800);
    showNGeneration->parent = this;
    QFont font("SimSun", 10);

    Person *p = NULL;
    int count = 1;
    while (!que.empty()) {
        Person *q = que.front();
        que.pop();
        if (q->birthday.year == _year && q->birthday.month == _month) {
            p = q;
            QString name1(p->name.c_str());
            QString sex(p->sex.c_str());
            QString year = QString::number(p->birthday.year);
            QString month = QString::number(p->birthday.month);
            QString day = QString::number(p->birthday.day);
            QString isMarrige;
            isMarrige = p->marriage?"已婚":"未婚";
            QString address = QString::fromStdString(p->address);
            QString health = p->live?"健在":"死亡";
            QString content;
            if(p->live){
                content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health);
            }else{
                QString die_year = QString::number(p->dieDay.year);
                QString die_month = QString::number(p->dieDay.month);
                QString die_day = QString::number(p->dieDay.day);

                content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8  死亡日期：%9年%10月%11日").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health).arg(die_year).arg(die_month).arg(die_day);
            }

            QLabel* label = new QLabel(showNGeneration);
            label->setText(content);
            label->setFont(font);
            label->setGeometry(50,100 * count,600,60);
            count++;
            label->show();

        }
        for (int i = 0; i < q->count; i++) {
            que.push(q->children[i]);
        }
    }
    if(!p){
        QMessageBox::information(NULL, "查找", "没有出生在此日期的人，请输入重试！", QMessageBox::Yes);
    } else {
        showNGeneration->show();
    }
}

/**
 * @brief Widget::on_pushButton_7_clicked
 * 删除某一成员
 */
void Widget::on_pushButton_7_clicked()
{
    show_DeletePersonDialog = new showDeletePersonDialog();
    show_DeletePersonDialog->show();
    show_DeletePersonDialog->exec();

    QString name = show_DeletePersonDialog->name;

    queue<Person *> que;
    que.push(ft->root);
    Person *p = NULL;
    while (!que.empty()) {
        Person *q = que.front();
        que.pop();
        QString tmpname = QString::fromStdString(q->name);
        if (QString::compare(name,tmpname) == 0) {
            p = q;
            break;
        }
        for (int i = 0; i < q->count; i++) {
            que.push(q->children[i]);
        }
    }

    if(!p){
        QMessageBox::information(NULL, "查找", "未找到此人，请输入重试！", QMessageBox::Yes);
    } else{
        flag = false;
        removeLabel();
        ft->deletePerson(p->name);
        print();
        flag = true;
        repaint();
    }

}

/**
 * @brief Widget::on_pushButton_9_clicked
 * 添加孩子
 */
void Widget::on_pushButton_9_clicked()
{

    showAddChildDialog = new ShowAddChildDialog();
    showAddChildDialog->show();
    showAddChildDialog->exec();

    Person* per = new Person();
    per->name = showAddChildDialog->name.toStdString();
    per->sex = showAddChildDialog->sex.toStdString();
    per->birthday.year = showAddChildDialog->live_year;
    per->birthday.month = showAddChildDialog->live_month;
    per->birthday.day = showAddChildDialog->live_day;
    per->marriage = showAddChildDialog->isMarriage == "是" ? true : false;
    per->address = showAddChildDialog->address.toStdString();
    per->live = showAddChildDialog->isLive == "是" ? true:false;
    per->dieDay.year = showAddChildDialog->die_year;
    per->dieDay.month = showAddChildDialog->die_month;
    per->dieDay.day = showAddChildDialog->die_day;
    per->count = 0;

    queue<Person *> que;
    que.push(ft->root);
    Person *p = NULL;
    while (!que.empty() && ft->root != NULL) {
        Person *q = que.front();
        que.pop();
        QString tmpname = QString::fromStdString(q->name);
        if (QString::compare(showAddChildDialog->parent,tmpname) == 0) {
            p = q;
            break;
        }
        for (int i = 0; i < q->count; i++) {
            que.push(q->children[i]);
        }
    }
    if(p == NULL){
        if(!ft->root){
            ft->root = per;
        }else{
            QMessageBox::information(NULL, "查找", "家谱人员添加非法！请确认本人是否属于该家谱！！" , QMessageBox::Yes);
        }
    }else{
        p->children[p->count++] = per;
        per->parent = p;
        per->generation = p->generation +1;
    }
    flag = false;
    removeLabel();
    print();
    flag = true;
    update();
}


/**
 * @brief Widget::on_pushButton_5_clicked
 * 确定两人关系
 */
void Widget::on_pushButton_5_clicked()
{
    showRelationDialog = new ShowRelationDialog();
    showRelationDialog->show();
    showRelationDialog->exec();

    string name1 = showRelationDialog->name1.toStdString();
    string name2 = showRelationDialog->name2.toStdString();

    if(!ft->root){
        QMessageBox::information(NULL, "查找", "家谱为空！请创建" , QMessageBox::Yes);
        return;
    }
    if(name1 == "" || name2 == ""){
        QMessageBox::information(NULL, "查找", "输入有误！请尝试重新输入！" , QMessageBox::Yes);
        return ;
    }
    Person *p1 = NULL;
    Person* p2 = NULL;
    queue<Person *> que;
    que.push(ft->root);
    while (!que.empty()) {
        Person *q = que.front();
        que.pop();
        if (q->name == name1) {
            p1 = q;
        }else if(q->name == name2){
            p2 = q;
        }
        for (int i = 0; i < q->count; i++) {
            que.push(q->children[i]);
        }
    }

    //比较
    int disc = abs(p1->generation - p2->generation);
    if(disc== 0){
        QMessageBox::information(NULL, "关系", "他们是兄弟关系" , QMessageBox::Yes);
    }else if(disc == 1){
       if(p1->generation - p2->generation < 0){
           if(p2->parent == p1){
               QMessageBox::information(NULL, "关系", QString::fromStdString(p1->name) + "是" +  QString::fromStdString(p2->name) + "的父亲" , QMessageBox::Yes);
           }else{
               QMessageBox::information(NULL, "关系",  QString::fromStdString(p1->name) + "是" +  QString::fromStdString(p2->name) + "的叔叔" , QMessageBox::Yes);
           }
       }else{
           if(p1->parent == p2){
               QMessageBox::information(NULL, "关系",  QString::fromStdString(p2->name) + "是" +  QString::fromStdString(p1->name) + "的父亲" , QMessageBox::Yes);
           }else{
               QMessageBox::information(NULL, "关系",  QString::fromStdString(p2->name) + "是" +  QString::fromStdString(p1->name) + "的叔叔" , QMessageBox::Yes);
           }
       }
    }else if(disc == 2){
        if(p1->generation - p2->generation < 0){
            QMessageBox::information(NULL, "关系", QString::fromStdString(p1->name) + "是" +  QString::fromStdString(p2->name) + "的爷爷" , QMessageBox::Yes);
        }else{
            QMessageBox::information(NULL, "关系", QString::fromStdString(p2->name) + "是" +  QString::fromStdString(p1->name) + "的爷爷" , QMessageBox::Yes);
        }
    }else if(disc == 3){
        if(p1->generation - p2->generation < 0){
            QMessageBox::information(NULL, "关系", QString::fromStdString(p1->name) + "是" +  QString::fromStdString(p2->name) + "的太爷爷" , QMessageBox::Yes);
        }else{
            QMessageBox::information(NULL, "关系", QString::fromStdString(p2->name) + "是" +  QString::fromStdString(p1->name) + "的太爷爷" , QMessageBox::Yes);
        }
    }else if(disc == 4){
        if(p1->generation - p2->generation < 0){
            QMessageBox::information(NULL, "关系", QString::fromStdString(p1->name) + "是" +  QString::fromStdString(p2->name) + "的太太爷爷" , QMessageBox::Yes);
        }else{
            QMessageBox::information(NULL, "关系", QString::fromStdString(p2->name) + "是" +  QString::fromStdString(p1->name) + "的太太爷爷" , QMessageBox::Yes);
        }
    }else if(disc == 5){
        if(p1->generation - p2->generation < 0){
            QMessageBox::information(NULL, "关系", QString::fromStdString(p1->name) + "是" +  QString::fromStdString(p2->name) + "的太太太爷爷" , QMessageBox::Yes);
        }else{
            QMessageBox::information(NULL, "关系", QString::fromStdString(p2->name) + "是" +  QString::fromStdString(p1->name) + "的太太太爷爷" , QMessageBox::Yes);
        }
    }else if(disc == 6){
        if(p1->generation - p2->generation < 0){
            QMessageBox::information(NULL, "关系", QString::fromStdString(p1->name) + "是" +  QString::fromStdString(p2->name) + "的太太太太爷爷" , QMessageBox::Yes);
        }else{
            QMessageBox::information(NULL, "关系", QString::fromStdString(p2->name) + "是" +  QString::fromStdString(p1->name) + "的太太太太爷爷" , QMessageBox::Yes);
        }
    }else if(disc == 7){
        if(p1->generation - p2->generation < 0){
            QMessageBox::information(NULL, "关系", QString::fromStdString(p1->name) + "是" +  QString::fromStdString(p2->name) + "的太太太太太爷爷" , QMessageBox::Yes);
        }else{
            QMessageBox::information(NULL, "关系", QString::fromStdString(p2->name) + "是" +  QString::fromStdString(p1->name) + "的太太太太太爷爷" , QMessageBox::Yes);
        }
    }

}


void Widget::on_pushButton_6_clicked()
{
    showModifyDialog = new ShowModifyDialog();
    showModifyDialog->show();
    showModifyDialog->exec();

    string name = showModifyDialog->name;
    if(!ft->root){
        QMessageBox::information(NULL, "查找", "未查找到此人！" , QMessageBox::Yes);
        return;
    }
    Person* p = NULL;
    queue<Person *> que;
    que.push(ft->root);
    while (!que.empty()) {
        Person *q = que.front();
        que.pop();
        if (q->name == name) {
            p = q;
            break;
        }
        for (int i = 0; i < q->count; i++) {
            que.push(q->children[i]);
        }
    }

    if(!p){
        QMessageBox::information(NULL, "查找", "未查找到此人！" , QMessageBox::Yes);
    }else{
        showModifyPersonDialog = new ShowModifyPersonDialog();

        QFont font("SimSun", 10);
        QString name1(p->name.c_str());
        QString sex(p->sex.c_str());
        QString year = QString::number(p->birthday.year);
        QString month = QString::number(p->birthday.month);
        QString day = QString::number(p->birthday.day);
        QString isMarrige;
        isMarrige = p->marriage?"已婚":"未婚";
        QString address = QString::fromStdString(p->address);
        QString health = p->live?"健在":"死亡";
        QString content;
        if(p->live){
            content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health);
        }else{
            QString die_year = QString::number(p->dieDay.year);
            QString die_month = QString::number(p->dieDay.month);
            QString die_day = QString::number(p->dieDay.day);

            content = QString("姓名:%1  性别： %2  出生日期：%3年%4月%5日 %6 %7 %8  死亡日期：%9年%10月%11日").arg(name1).arg(sex).arg(year).arg(month).arg(day).arg(isMarrige).arg(address).arg(health).arg(die_year).arg(die_month).arg(die_day);
        }
        showModifyPersonDialog->ui->label_preInfo->setText(content);
        showModifyPersonDialog->ui->label_preInfo->setFont(font);
        showModifyPersonDialog->ui->label_preInfo->show();

        //下面是信息填入
        showModifyPersonDialog->ui->le_name->setText(name1);
        showModifyPersonDialog->ui->le_sex->setText(sex);
        showModifyPersonDialog->ui->le_birth_year->setText(year);
        showModifyPersonDialog->ui->le_birth_month->setText(month);
        showModifyPersonDialog->ui->le_birth_day->setText(day);
        showModifyPersonDialog->ui->le_marriage->setText(isMarrige);
        showModifyPersonDialog->ui->le_address->setText(address);
        showModifyPersonDialog->ui->le_live->setText(health);
        if(!p->live){
            QString die_year = QString::number(p->dieDay.year);
            QString die_month = QString::number(p->dieDay.month);
            QString die_day = QString::number(p->dieDay.day);
            showModifyPersonDialog->ui->le_die_year->setText(die_year);
            showModifyPersonDialog->ui->le_die_month->setText(die_month);
            showModifyPersonDialog->ui->le_die_day->setText(die_day);
        }
        if(p->parent){
            showModifyPersonDialog->ui->le_father->setText(QString::fromStdString(p->parent->name));
        }
        showModifyPersonDialog->show();
        showModifyPersonDialog->exec();



        //点击修改后更新数据
        if(showModifyPersonDialog->flag){
            p->name = showModifyPersonDialog->name.toStdString();
            p->sex = showModifyPersonDialog->sex.toStdString();
            p->birthday.year = showModifyPersonDialog->birth_year.toInt();
            p->birthday.month = showModifyPersonDialog->birth_month.toInt();
            p->birthday.day = showModifyPersonDialog->birth_day.toInt();
            p->marriage = showModifyPersonDialog->isMarriage == "已婚" ? true:false;
            p->address = showModifyPersonDialog->address.toStdString();
            p->live = showModifyPersonDialog->islive == "健在" ? true: false;
            if(!p->live){
                p->dieDay.year = showModifyPersonDialog->die_year.toInt();
                p->dieDay.month = showModifyPersonDialog->die_month.toInt();
                p->dieDay.day = showModifyPersonDialog->die_day.toInt();
            }
            if(p->parent){
                Person* ptr = NULL;
                queue<Person *> que;
                que.push(ft->root);
                while (!que.empty()) {
                    Person *q = que.front();
                    que.pop();
                    if(showModifyPersonDialog->parent.toStdString() == q->name){
                        ptr = q;
                        break;
                    }
                    for (int i = 0; i < q->count; i++) {
                        que.push(q->children[i]);
                    }
                }
                if(p->parent != ptr){
                    int index = -1;
                    for (int i = 0; i < p->parent->count; ++i) {
                        if(p->children[i] == p){
                            index = i;
                            break;
                        }
                    }
                    for (int i = index + 1; i < p->parent->count; ++i) {
                        p->children[i-1] = p->children[i];
                    }
                    p->parent->count -= 1;
                    p->parent = ptr;
                    ptr->children[ptr->count++] = p;
                }
            }
            flag = false;
            removeLabel();
            print();
            flag = true;
            update();
        }

    }
}
