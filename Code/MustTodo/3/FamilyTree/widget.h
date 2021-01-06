#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "FamilyTree.h"
#include "showndialog.h"
#include "showfamilytree.h"
#include "showngeneration.h"
#include "shownamedialog.h"
#include "showbirthdaydialog.h"
#include "showdeletepersondialog.h"
#include "showaddchilddialog.h"
#include "showrelationdialog.h"
#include "showmodifydialog.h"
#include "showmodifypersondialog.h"
#include "ui_showmodifypersondialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void Coordinate();      //求坐标
    void print();           //打印
    void paintEvent(QPaintEvent *event);

    FamilyTree *ft;
    bool flag;
    ShowNDialog *dialog;
    ShowFamilyTree* container;
    ShowNGeneration* showNGeneration;
    ShowNameDialog* showNameDialog;
    ShowBirthdayDialog* showBirthdayDialog;
    showDeletePersonDialog *show_DeletePersonDialog;
    ShowAddChildDialog* showAddChildDialog;
    ShowRelationDialog* showRelationDialog;
    ShowModifyDialog* showModifyDialog;
    ShowModifyPersonDialog* showModifyPersonDialog;

    int value;
    void removeLabel();
private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
