#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QDialog>
#include "sudokugenerationwindow.h"

namespace Ui {
class DifficultyWindow;
}

class DifficultyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DifficultyWindow(QWidget *parent = nullptr);
    ~DifficultyWindow();

signals:
    void mainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::DifficultyWindow *ui;
    SudokuGenerationWindow* sudoku;
};

#endif // DIFFICULTYWINDOW_H
