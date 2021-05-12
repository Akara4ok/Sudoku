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

namespace Ui {
class SudokuGenerationWindow;
}

class SudokuGenerationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SudokuGenerationWindow(QWidget *parent = nullptr, QString difficulty = "");
    ~SudokuGenerationWindow();
    int getTime();

signals:
    void mainWindow();
    void showResults();

private slots:
    void onTimeout();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::SudokuGenerationWindow *ui;
    QList<QLineEdit*> list;
    QString difficulty;
    int time;
    QTimer *timer;
    Sudoku sudoku;

    //QLineEdit* lineEdit = new QLineEdit();
};

#endif // SUDOKUGENERATIONWINDOW_H
