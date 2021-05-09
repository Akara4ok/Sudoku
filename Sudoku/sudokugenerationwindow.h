#ifndef SUDOKUGENERATIONWINDOW_H
#define SUDOKUGENERATIONWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QValidator>
#include <QTimer>
#include <QString>
#include <QLCDNumber>

namespace Ui {
class SudokuGenerationWindow;
}

class SudokuGenerationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SudokuGenerationWindow(QWidget *parent = nullptr, QString s = "");
    ~SudokuGenerationWindow();

signals:
    void difficulty();

private slots:
    void onTimeout();

    void on_pushButton_4_clicked();

private:
    Ui::SudokuGenerationWindow *ui;
    QList<QLineEdit*> list;
    int time;

    //QLineEdit* lineEdit = new QLineEdit();
};

#endif // SUDOKUGENERATIONWINDOW_H
