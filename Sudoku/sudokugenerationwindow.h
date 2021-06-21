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
#include <QFileDialog>

namespace Ui {
class SudokuGenerationWindow;
}

class SudokuGenerationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SudokuGenerationWindow(QWidget *parent = nullptr, QString difficulty1 = "", bool continueGame = false, QString path = ""); // Конструктор, створює вікно, заповнює його клітинками, якщо це продовження гри, то зчитує всі дані з файлу і встановлює в об'єкт
    ~SudokuGenerationWindow(); // Деструктор
    int getTime(); // Повертає час, який пройшов з початку розв'язання
    QString getDifficulty(); // Повертає складність судоку
    int getHints(); // Повертає кількість підказок
    int getMistakes(); // Повертає кількість помилок


signals:
    void mainWindow(); // Сигнал для повернення в головне меню
    void showResults(); // Сигнал для відкривання вікна зі статистикою після розв'язання
    void saveGame(); // Сигнал, що повідомлює головне вікно про збережену гру

private slots:
    void onTimeout(); // При проходженні однієї секунди час збільшується на один
    void on_quitButton_clicked(); // Видаляє об'єкт, викликає сигнал mainWindow
    void on_clearButton_clicked(); // Очищує всі поля, які ввів користувач
    void on_checkButton_clicked(); // Перевіряє чи правильно користувач розв'язав головоломку
    void on_hintButton_clicked(); // Відображує підказку
    void on_showSolutionButton_clicked(); // Відображує розв'язання судоку(Всі інші кнопки стають недоступними).
    void on_rulesButton_clicked(); // Відображує правила гри
    void on_saveButton_clicked(); // Зберігає всі дані про гру в файл, викликає сигнал saveGame
    void checkForCorrect(); // Перевіряє чи правильне число записене в клітинці


private:
    Ui::SudokuGenerationWindow *ui;
    QVector<QLineEdit*> cells; // Клітинки судоку
    QString difficulty; // Рівень складності
    int time; // Час, який пройшов з початку головоломки
    QTimer *timer; // Об'єкт, який рахує час
    Sudoku sudoku; // Об'єкт судоку
    int hints; // Кількість підказок
    int mistakes; // Кількість помилок
    QVector<int> lastMistake;
    QString path;
    //QLineEdit* lineEdit = new QLineEdit();
};

#endif // SUDOKUGENERATIONWINDOW_H
