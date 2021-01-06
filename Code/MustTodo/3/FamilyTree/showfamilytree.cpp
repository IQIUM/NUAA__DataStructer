#include "showfamilytree.h"
#include "ui_showfamilytree.h"

ShowFamilyTree::ShowFamilyTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowFamilyTree)
{
    ui->setupUi(this);
}

ShowFamilyTree::~ShowFamilyTree()
{
    delete ui;
}
