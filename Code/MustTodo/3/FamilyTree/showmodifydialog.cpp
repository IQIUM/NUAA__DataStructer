#include "showmodifydialog.h"
#include "ui_showmodifydialog.h"

ShowModifyDialog::ShowModifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowModifyDialog)
{
    ui->setupUi(this);
}

ShowModifyDialog::~ShowModifyDialog()
{
    delete ui;
}

void ShowModifyDialog::on_pushButton_clicked()
{
    name = ui->lineEdit->text().toStdString();
    this->close();
}

void ShowModifyDialog::on_pushButton_2_clicked()
{
    this->close();
}
