#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "difficultywindow.h"
#include "sudokugenerationwindow.h"

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

private:
    Ui::MainWindow *ui;
    DifficultyWindow* difficulty;
    SudokuGenerationWindow* sudokuGeneration;
    void easySudoku();
    void mediumSudoku();
    void expertSudoku();
};
#endif // MAINWINDOW_H
