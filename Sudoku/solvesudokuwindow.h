#ifndef SOLVESUDOKUWINDOW_H
#define SOLVESUDOKUWINDOW_H

#include <QDialog>

namespace Ui {
class SolveSudokuWindow;
}

class SolveSudokuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SolveSudokuWindow(QWidget *parent = nullptr);
    ~SolveSudokuWindow();

signals:
    void mainWindow();

private slots:
    void on_pushButton_7_clicked();

private:
    Ui::SolveSudokuWindow *ui;
};

#endif // SOLVESUDOKUWINDOW_H
