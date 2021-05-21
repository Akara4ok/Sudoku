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
    void mainWindow();

public:
    explicit TopResultsWindow(QWidget *parent = nullptr, QString s = "Top Results", int time = 0, QString difficulty="", int mistakes = 0, int hints = 0);
    ~TopResultsWindow();

private slots:
    void on_quitButton_clicked();
    void on_clearButton_clicked();
    void on_difficultyRadioButton_clicked();
    void on_nameRadioButton_clicked();
    void on_timeRadioButton_clicked();
    void on_hintsRadioButton_clicked();
    void on_mistakesRadioButton_clicked();

private:
    Ui::TopResultsWindow *ui;
    QStringList res;
    QVector<topRLine> table;
    QStandardItemModel* model;
    bool difficultySort = false;
    bool nameSort = false;
    bool timeSort = true;
    bool hintsSort = false;
    bool mistakesSort = false;
    void sort();
    void setTable();
};

#endif // TOPRESULTSWINDOW_H
