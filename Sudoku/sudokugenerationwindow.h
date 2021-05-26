#ifndef SUDOKUGENERATIONWINDOW_H
#define SUDOKUGENERATIONWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QValidator>
#include <QTimer>
#include <QString>
#include <QLCDNumber>
#include <QMessageBox>
#include "sudoku.h"
#include <QFile>
#include <qdir.h>
#include <QGridLayout>

namespace Ui {
class SudokuGenerationWindow;
}

class SudokuGenerationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SudokuGenerationWindow(QWidget *parent = nullptr, QString difficulty1 = "", bool continueGame = false);
    ~SudokuGenerationWindow();
    int getTime();
    QString getDifficulty();
    int getHints();
    int getMistakes();


signals:
    void mainWindow();
    void showResults();
    void saveGame();

private slots:
    void onTimeout();
    void on_quitButton_clicked();
    void on_clearButton_clicked();
    void on_checkButton_clicked();
    void on_hintButton_clicked();
    void on_showSolutionButton_clicked();
    void on_rulesButton_clicked();
    void on_saveButton_clicked();
    void checkForCorrect();


private:
    Ui::SudokuGenerationWindow *ui;
    QVector<QLineEdit*> cells;
    QString difficulty;
    int time;
    QTimer *timer;
    Sudoku sudoku;
    int hints;
    int mistakes;
    QVector<QGridLayout*> grids;
    //QLineEdit* lineEdit = new QLineEdit();
};

#endif // SUDOKUGENERATIONWINDOW_H
