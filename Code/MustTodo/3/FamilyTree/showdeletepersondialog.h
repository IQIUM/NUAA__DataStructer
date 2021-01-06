#ifndef SHOWDELETEPERSONDIALOG_H
#define SHOWDELETEPERSONDIALOG_H

#include <QDialog>

namespace Ui {
class showDeletePersonDialog;
}

class showDeletePersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit showDeletePersonDialog(QWidget *parent = nullptr);
    ~showDeletePersonDialog();


    QString name;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::showDeletePersonDialog *ui;
};

#endif // SHOWDELETEPERSONDIALOG_H
