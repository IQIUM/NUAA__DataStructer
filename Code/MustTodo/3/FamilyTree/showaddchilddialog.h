#ifndef SHOWADDCHILDDIALOG_H
#define SHOWADDCHILDDIALOG_H

#include <QDialog>

namespace Ui {
class ShowAddChildDialog;
}

class ShowAddChildDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAddChildDialog(QWidget *parent = nullptr);
    ~ShowAddChildDialog();

    QString name;
    QString sex;
    int live_year;
    int live_month;
    int live_day;
    QString isMarriage;
    QString address;
    QString isLive;
    int die_year;
    int die_month;
    int die_day;
    QString parent;






private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ShowAddChildDialog *ui;
};

#endif // SHOWADDCHILDDIALOG_H
