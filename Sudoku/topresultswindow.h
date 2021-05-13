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
#include "quartet.h"

namespace Ui {
class TopResultsWindow;
}

class TopResultsWindow : public QDialog
{
    Q_OBJECT

signals:
    void mainWindow();

public:
    explicit TopResultsWindow(QWidget *parent = nullptr, QString s = "Top Results", int time = 0, QString difficulty="", int hints = 0);
    ~TopResultsWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

private:
    Ui::TopResultsWindow *ui;
    QStringList res;
    QVector<Quartet> table;
    QStandardItemModel* model;
    bool difficultySort = false;
    bool nameSort = false;
    bool timeSort = true;
    bool hintsSort = false;
    void sort();
    void setTable();
};

#endif // TOPRESULTSWINDOW_H
