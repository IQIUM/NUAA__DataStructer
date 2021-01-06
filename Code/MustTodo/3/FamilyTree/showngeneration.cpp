#include "showngeneration.h"
#include "ui_showngeneration.h"

ShowNGeneration::ShowNGeneration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowNGeneration)
{
    ui->setupUi(this);
}

ShowNGeneration::~ShowNGeneration()
{
    delete ui;
}

void ShowNGeneration::on_pushButton_clicked()
{
    this->close();
    parent->show();
}
