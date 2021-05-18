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
    void mainWindow();
    void easy();
    void medium();
    void expert();

private slots:
    void on_easyButton_clicked();
    void on_mediumButton_clicked();
    void on_expertButton_clicked();
    void on_backButton_clicked();

private:
    Ui::DifficultyWindow *ui;
};

#endif // DIFFICULTYWINDOW_H
