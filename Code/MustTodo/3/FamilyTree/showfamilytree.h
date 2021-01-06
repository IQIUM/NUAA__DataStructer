#ifndef SHOWFAMILYTREE_H
#define SHOWFAMILYTREE_H

#include <QWidget>

namespace Ui {
class ShowFamilyTree;
}

class ShowFamilyTree : public QWidget
{
    Q_OBJECT

public:
    explicit ShowFamilyTree(QWidget *parent = nullptr);
    ~ShowFamilyTree();

private:
    Ui::ShowFamilyTree *ui;
};

#endif // SHOWFAMILYTREE_H
