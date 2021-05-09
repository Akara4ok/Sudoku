#ifndef TOPRESULTSWINDOW_H
#define TOPRESULTSWINDOW_H

#include <QDialog>
#include <QTableView>
#include <QTableWidget>
#include <QStandardItemModel>


namespace Ui {
class TopResultsWindow;
}

class TopResultsWindow : public QDialog
{
    Q_OBJECT

signals:
    void mainWindow();

public:
    explicit TopResultsWindow(QWidget *parent = nullptr);
    ~TopResultsWindow();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::TopResultsWindow *ui;
};

#endif // TOPRESULTSWINDOW_H
