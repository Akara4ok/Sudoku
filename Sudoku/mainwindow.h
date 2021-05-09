#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "difficultywindow.h"
#include "sudokugenerationwindow.h"
#include "solvesudokuwindow.h"
#include "topresultswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    DifficultyWindow* difficulty;
    SudokuGenerationWindow* sudokuGeneration;
    SolveSudokuWindow* solveSudoku;
    TopResultsWindow* topResults;

    void easySudoku();
    void mediumSudoku();
    void expertSudoku();
};
#endif // MAINWINDOW_H
