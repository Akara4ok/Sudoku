#ifndef TOPRESULTSWINDOW_H
#define TOPRESULTSWINDOW_H

#include <QDialog>
#include <QTableView>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QFile>
#include <QString>
#include <qdir.h>
#include <QMessageBox>
#include "topRLine.h"

namespace Ui {
class TopResultsWindow;
}

class TopResultsWindow : public QDialog
{
    Q_OBJECT

signals:
    void mainWindow(); // Сигнал для повернення в головне вікно

public:
    explicit TopResultsWindow(QWidget *parent = nullptr, QString s = "Top Results", int time = 0, QString difficulty="", int mistakes = 0, int hints = 0); //Конструктор, перевіряє, якщо вікно викликано після завершення гри, то записує статистику про цю гру в файл і читає всі дані з файлу. Інакше просто читає дані з файлу і вставляє в табличку.
    ~TopResultsWindow(); // Деструктор

private slots:
    void on_quitButton_clicked(); // Закриває вікно і викликає сигнал mainWindow
    void on_clearButton_clicked(); // Очищує всі дані в табличці
    void on_difficultyRadioButton_clicked(); // Змінює критерій сортування на сортування по складності. Викликає процедуру sort
    void on_nameRadioButton_clicked(); // Змінює критерій сортування на сортування по імені. Викликає процедуру sort
    void on_timeRadioButton_clicked(); // Змінює критерій сортування на сортування по часу. Викликає процедуру sort
    void on_hintsRadioButton_clicked(); // Змінює критерій сортування на сортування по кількості підказок . Викликає процедуру sort
    void on_mistakesRadioButton_clicked(); // Змінює критерій сортування на сортування по кількості помилок. Викликає процедуру sort

private:
    Ui::TopResultsWindow *ui;
    QStringList res; // Список рядків файлу
    QVector<topRLine> table; // Дані, які записані в таблиці
    QStandardItemModel* model; // Таблиця
    bool difficultySort = false; // Критерій сортування по складності
    bool nameSort = false; // Критерій сортування по складності
    bool timeSort = true; // Критерій сортування по часу
    bool hintsSort = false; // Критерій сортування по кількості підказок
    bool mistakesSort = false; // Критерій сортування по кількості помилок
    void sort(); // Сортує таблицю відповідно до критерію
    void setTable(); // Встановлює дані в таблицю
};

#endif // TOPRESULTSWINDOW_H
