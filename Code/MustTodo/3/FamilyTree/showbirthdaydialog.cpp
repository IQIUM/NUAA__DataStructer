#include "showbirthdaydialog.h"
#include "ui_showbirthdaydialog.h"

ShowBirthdayDialog::ShowBirthdayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowBirthdayDialog)
{
    ui->setupUi(this);
}

ShowBirthdayDialog::~ShowBirthdayDialog()
{
    delete ui;
}

void ShowBirthdayDialog::on_pushButton_2_clicked()
{
    this->close();
}

void ShowBirthdayDialog::on_pushButton_clicked()
{
    year = ui->le_year->text().toInt();
    month = ui->le_month->text().toInt();
    this->close();
}
