#ifndef SHOWNAMEDIALOG_H
#define SHOWNAMEDIALOG_H

#include <QDialog>

namespace Ui {
class ShowNameDialog;
}

class ShowNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowNameDialog(QWidget *parent = nullptr);
    ~ShowNameDialog();

    QString name;
    QWidget* parent;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ShowNameDialog *ui;
};

#endif // SHOWNAMEDIALOG_H
