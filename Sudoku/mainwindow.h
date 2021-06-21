#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "difficultywindow.h"
#include "sudokugenerationwindow.h"
#include "solvesudokuwindow.h"
#include "topresultswindow.h"
#include <QFileDialog>
#include <QFile>

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
    void on_newGameButton_clicked(); // Відкриває вікно з вибором складності
    void on_quitButton_clicked(); // Закриває програму
    void on_solveButton_clicked(); // Відкриває вікно розв'язання судоку
    void on_topResultsButton_clicked(); // Відкриває вікно зі статистикою
    void on_continueButton_clicked(); // Відкриває вікно генерації судоку в режимі продовження гри

private:
    Ui::MainWindow *ui;
    DifficultyWindow* difficulty; // Вікно вибору складності
    SudokuGenerationWindow* sudokuGeneration;// Вікно генерації судоку
    SolveSudokuWindow* solveSudoku;// Вікно розв'язання судоку
    TopResultsWindow* topResults;// Вікно зі статистикою судоку
    void easySudoku(); //Відкриває вікно з генерацією судоку та передає, що рівень складності легкий
    void mediumSudoku(); //Відкриває вікно з генерацією судоку та передає, що рівень складності середній
    void expertSudoku();//Відкриває вікно з генерацією судоку та передає, що рівень складності важкий
    void showR(); //Показує статистику після завершення гри
    void closeR();//Закриває статистику після завершення гри
    void enableContinue();//Активує кнопку продовжити
};
#endif // MAINWINDOW_H
