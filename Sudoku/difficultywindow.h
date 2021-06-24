#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QDialog>

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
    void mainWindow();// Сигнал, після якого відкривається головне меню
    void easy();// Сигнал, після якого генерується судоку легкої складності
    void medium();// Сигнал, після якого генерується судоку середньої складності
    void expert();// Сигнал, після якого генерується судоку важкої складності
    void giant();// Сигнал, після якого генерується судоку останньої складності

private slots:
    void on_easyButton_clicked(); // При натисненні кнопки "easy" викликається сигнал easy() та закривається вікно
    void on_mediumButton_clicked();// При натисненні кнопки "medium" викликається сигнал medium() та закривається вікно
    void on_expertButton_clicked();// При натисненні кнопки "expert" викликається сигнал expert() та закривається вікно
    void on_giantButton_clicked();// При натисненні кнопки "giant" викликається сигнал giant() та закривається вікно
    void on_backButton_clicked();// При натисненні кнопки "back" викликається сигнал mainWindow() та закривається вікно

private:
    Ui::DifficultyWindow *ui;
};

#endif // DIFFICULTYWINDOW_H
