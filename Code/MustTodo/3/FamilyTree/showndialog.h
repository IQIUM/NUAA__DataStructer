#ifndef SHOWNDIALOG_H
#define SHOWNDIALOG_H

#include <QDialog>

namespace Ui {
class ShowNDialog;
}

class ShowNDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowNDialog(QWidget *parent = nullptr);
    ~ShowNDialog();

    int value;

private slots:
    void on_btn_sure_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ShowNDialog *ui;
};

#endif // SHOWNDIALOG_H
