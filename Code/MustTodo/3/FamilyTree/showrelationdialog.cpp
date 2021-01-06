#include "showrelationdialog.h"
#include "ui_showrelationdialog.h"

ShowRelationDialog::ShowRelationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowRelationDialog)
{
    ui->setupUi(this);
}

ShowRelationDialog::~ShowRelationDialog()
{
    delete ui;
}

void ShowRelationDialog::on_pushButton_2_clicked()
{
    this->close();
}

void ShowRelationDialog::on_pushButton_clicked()
{
    name1 = ui->lineEdit->text();
    name2 = ui->lineEdit_2->text();
    this->close();
}
