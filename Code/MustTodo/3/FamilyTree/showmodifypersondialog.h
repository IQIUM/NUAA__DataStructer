#ifndef SHOWMODIFYPERSONDIALOG_H
#define SHOWMODIFYPERSONDIALOG_H

#include <QDialog>

namespace Ui {
class ShowModifyPersonDialog;
}

class ShowModifyPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowModifyPersonDialog(QWidget *parent = nullptr);
    ~ShowModifyPersonDialog();

    Ui::ShowModifyPersonDialog *ui;


    bool flag;

    QString name;
    QString sex;
    QString birth_year;
    QString birth_month;
    QString birth_day;
    QString isMarriage;
    QString address;
    QString islive;
    QString die_year;
    QString die_month;
    QString die_day;
    QString parent;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // SHOWMODIFYPERSONDIALOG_H
