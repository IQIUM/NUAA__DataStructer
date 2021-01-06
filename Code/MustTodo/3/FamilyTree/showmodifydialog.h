#ifndef SHOWMODIFYDIALOG_H
#define SHOWMODIFYDIALOG_H

#include <QDialog>
#include <string>
using namespace  std;
namespace Ui {
class ShowModifyDialog;
}

class ShowModifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowModifyDialog(QWidget *parent = nullptr);
    ~ShowModifyDialog();

    string name;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ShowModifyDialog *ui;
};

#endif // SHOWMODIFYDIALOG_H
