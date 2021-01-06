#include "showdeletepersondialog.h"
#include "ui_showdeletepersondialog.h"

showDeletePersonDialog::showDeletePersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showDeletePersonDialog)
{
    ui->setupUi(this);
}

showDeletePersonDialog::~showDeletePersonDialog()
{
    delete ui;
}

void showDeletePersonDialog::on_pushButton_2_clicked()
{
    this->close();
}

void showDeletePersonDialog::on_pushButton_clicked()
{
    name = ui->lineEdit->text();
    this->close();
}
