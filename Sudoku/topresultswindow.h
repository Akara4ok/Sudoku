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

private:
    Ui::TopResultsWindow *ui;
    QStringList res;
    QVector<Quartet> table;
    void sort();
};

#endif // TOPRESULTSWINDOW_H
