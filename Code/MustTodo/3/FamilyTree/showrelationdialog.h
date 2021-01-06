#ifndef SHOWRELATIONDIALOG_H
#define SHOWRELATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ShowRelationDialog;
}

class ShowRelationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowRelationDialog(QWidget *parent = nullptr);
    ~ShowRelationDialog();

   QString name1;
   QString name2;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ShowRelationDialog *ui;
};

#endif // SHOWRELATIONDIALOG_H
