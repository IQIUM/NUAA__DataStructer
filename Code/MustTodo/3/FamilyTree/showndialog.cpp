#include "showndialog.h"
#include "ui_showndialog.h"

ShowNDialog::ShowNDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowNDialog)
{
    ui->setupUi(this);

}

ShowNDialog::~ShowNDialog()
{
    delete ui;
}

void ShowNDialog::on_btn_sure_clicked()
{
    value  = ui->lineEdit->text().toInt();
    this->close();
}

void ShowNDialog::on_pushButton_2_clicked()
{
    this->close();
}
