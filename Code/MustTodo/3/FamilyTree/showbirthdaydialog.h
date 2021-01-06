#ifndef SHOWBIRTHDAYDIALOG_H
#define SHOWBIRTHDAYDIALOG_H

#include <QDialog>

namespace Ui {
class ShowBirthdayDialog;
}

class ShowBirthdayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowBirthdayDialog(QWidget *parent = nullptr);
    ~ShowBirthdayDialog();


    int year;
    int month;
    int day;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ShowBirthdayDialog *ui;
};

#endif // SHOWBIRTHDAYDIALOG_H
