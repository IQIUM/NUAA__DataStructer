#ifndef SHOWNGENERATION_H
#define SHOWNGENERATION_H

#include <QDialog>

namespace Ui {
class ShowNGeneration;
}

class ShowNGeneration : public QDialog
{
    Q_OBJECT

public:
    explicit ShowNGeneration(QWidget *parent = nullptr);
    ~ShowNGeneration();

    QWidget* parent;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShowNGeneration *ui;
};

#endif // SHOWNGENERATION_H
