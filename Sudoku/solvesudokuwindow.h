#ifndef SOLVESUDOKUWINDOW_H
#define SOLVESUDOKUWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QValidator>
#include "sudoku.h"
#include <QRegularExpressionValidator>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>

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
    void on_quitButton_clicked();
    void on_solveButton_clicked();
    void on_clearButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::SolveSudokuWindow *ui;
    QVector<QLineEdit*> cells;
};

#endif // SOLVESUDOKUWINDOW_H
