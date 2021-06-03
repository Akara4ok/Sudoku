#ifndef SOLVESUDOKUWINDOW_H
#define SOLVESUDOKUWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QValidator>
#include "sudoku.h"
#include <QRegularExpressionValidator>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QFont>

namespace Ui {
class SolveSudokuWindow;
}

class SolveSudokuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SolveSudokuWindow(QWidget *parent = nullptr); // Конструктор вікна розв'язання судоку(динамічно розміщує клітинки на екрані)
    ~SolveSudokuWindow();

signals:
    void mainWindow(); // Сигнал повернення до головного вікна

private slots:
    void on_quitButton_clicked(); // Викликється сигнал mainWindow
    void on_solveButton_clicked(); // Виклається створюється об'єкт класса судоку і викликається метод розв'язати судоку
    void on_clearButton_clicked(); // Очищує всі поля вводу
    void on_saveButton_clicked(); // Зберігає судоку відповідно до шляху, який вкаже користувач

private:
    Ui::SolveSudokuWindow *ui;
    QVector<QLineEdit*> cells; // Клітинки для вводу чисел
    Sudoku* sudoku; // Об'єкт класса судоку
};

#endif // SOLVESUDOKUWINDOW_H
