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

private slots:
    void on_pushButton_clicked();

private:
    Ui::DifficultyWindow *ui;
};

#endif // DIFFICULTYWINDOW_H
