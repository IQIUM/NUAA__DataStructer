#include "showmodifypersondialog.h"
#include "ui_showmodifypersondialog.h"

ShowModifyPersonDialog::ShowModifyPersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowModifyPersonDialog)
{
    ui->setupUi(this);
    flag = false;
}

ShowModifyPersonDialog::~ShowModifyPersonDialog()
{
    delete ui;
}

void ShowModifyPersonDialog::on_pushButton_2_clicked()
{
    this->close();
}

void ShowModifyPersonDialog::on_pushButton_clicked()
{
    flag = true;
    //重新更新
    name = ui->le_name->text();
    sex = ui->le_sex->text();
    birth_year = ui->le_birth_year->text();
    birth_month = ui->le_birth_month->text();
    birth_day = ui->le_birth_day->text();
    isMarriage = ui->le_marriage->text();
    address = ui->le_address->text();
    islive  = ui->le_live->text();
    die_year = ui->le_die_year->text();
    die_month = ui->le_die_month->text();
    die_day = ui->le_die_day->text();
    parent = ui->le_father->text();

    this->close();
}
