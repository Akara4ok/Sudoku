#ifndef SOLVESUDOKUWINDOW_H
#define SOLVESUDOKUWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QValidator>
#include "sudoku.h"
#include <QRegularExpressionValidator>

namespace Ui {
class SolveSudokuWindow;
}

class SolveSudokuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SolveSudokuWindow(QWidget *parent = nullptr);
    ~SolveSudokuWindow();

signals:
    void mainWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::SolveSudokuWindow *ui;
    QList<QLineEdit*> list;
};

#endif // SOLVESUDOKUWINDOW_H
