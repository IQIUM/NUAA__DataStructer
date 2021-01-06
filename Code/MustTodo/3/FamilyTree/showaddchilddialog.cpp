#include "showaddchilddialog.h"
#include "ui_showaddchilddialog.h"

ShowAddChildDialog::ShowAddChildDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAddChildDialog)
{
    ui->setupUi(this);
}

ShowAddChildDialog::~ShowAddChildDialog()
{
    delete ui;
}

void ShowAddChildDialog::on_pushButton_clicked()
{
    name = ui->le_name->text();
    sex = ui->le_sex->text();
    live_year = ui->le_birth_year->text().toInt();
    live_month = ui->le_birth_month->text().toInt();
    live_day = ui->le_birth_day->text().toInt();
    isMarriage = ui->le_marriage->text();
    address = ui->le_address->text();
    isLive = ui->le_live->text();
    if(isLive == "否"){
        die_year = ui->le_die_year->text().toInt();
        die_month = ui->le_die_month->text().toInt();
        die_day = ui->le_die_day->text().toInt();
    }else{
        die_year = 0;
        die_month= 0;
        die_day = 0;
    }
    parent = ui->le_father->text();
    this->close();
}

void ShowAddChildDialog::on_pushButton_2_clicked()
{
    this->close();
}
