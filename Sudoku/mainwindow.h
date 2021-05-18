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
    void on_newGameButton_clicked();
    void on_quitButton_clicked();
    void on_solveButton_clicked();
    void on_topResultsButton_clicked();
    void on_continueButton_clicked();

private:
    Ui::MainWindow *ui;
    DifficultyWindow* difficulty;
    SudokuGenerationWindow* sudokuGeneration;
    SolveSudokuWindow* solveSudoku;
    TopResultsWindow* topResults;
    void easySudoku();
    void mediumSudoku();
    void expertSudoku();
    void showR();
    void closeR();
    void enableButton();
};
#endif // MAINWINDOW_H
