#ifndef SOLVESUDOKU_H
#define SOLVESUDOKU_H

#include <QDialog>
#include <QLineEdit>
#include <QValidator>

namespace Ui {
class SolveSudoku;
}

class SolveSudoku : public QDialog
{
    Q_OBJECT

public:
    explicit SolveSudoku(QWidget *parent = nullptr);
    ~SolveSudoku();

private:
    Ui::SolveSudoku *ui;
    QList<QLineEdit*> list;
};

#endif // SOLVESUDOKU_H
