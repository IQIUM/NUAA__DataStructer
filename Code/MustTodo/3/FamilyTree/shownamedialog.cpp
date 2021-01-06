#include "shownamedialog.h"
#include "ui_shownamedialog.h"

ShowNameDialog::ShowNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowNameDialog)
{
    ui->setupUi(this);
}

ShowNameDialog::~ShowNameDialog()
{
    delete ui;
}

void ShowNameDialog::on_pushButton_2_clicked()
{
    this->close();
}

void ShowNameDialog::on_pushButton_clicked()
{
    name = ui->lineEdit->text();
    this->close();
}
