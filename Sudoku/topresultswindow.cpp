#include "topresultswindow.h"
#include "ui_topresultswindow.h"

TopResultsWindow::TopResultsWindow(QWidget *parent, QString s, int time, QString difficulty, int hints) :
    QDialog(parent),
    ui(new Ui::TopResultsWindow)
{
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel(0, 4, this);
    model->setHeaderData(0, Qt::Horizontal, "Difficulty");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Time");
    model->setHeaderData(3, Qt::Horizontal, "Hints");
    //ui->tableView->setModel(model);
    ui->label->setText(s);
    QString name;
    if (time != 0)
    {
        ui->label_3->setText("Your time: " + QString::number(time) + "s");
        name = QInputDialog::getText( 0, "Input", "Name:", QLineEdit::Normal);
    }
    QFile topRes(QDir::currentPath() + "\\topResults.txt");
    if(!topRes.exists())
    {
        topRes.open(QIODevice::WriteOnly);
        topRes.close();
    }
    if ((topRes.exists())&&(topRes.open(QIODevice::ReadOnly)))
    {
        while(!topRes.atEnd())
        {
        res << topRes.readLine();
        }
        topRes.close();
    }
    if ((topRes.exists())&&(topRes.open(QIODevice::WriteOnly)))
    {
        if (time != 0)
        {
            QString s = difficulty + "," + name + "," + QString::number(time) + "," + QString::number(hints) + "\n";
            res << s;
        }
        QTextStream fout(&topRes);
        foreach(QString s, res)
        {
            fout << s;
        }
        topRes.close();
    }
    QModelIndex ind;
    for (int i = 0; i < res.size(); i++)
    {
        int last = 0;
        int next = 0;
        model->insertRow(i);
        for (int j = 0; j < 4; j++)
        {
            QStandardItem *item= new QStandardItem();
            next = res[i].indexOf(",", last);
            if (next == -1)
                next = res[i].length() - 1;
            ind = model->index(i, j);
            item -> setText(res[i].mid(last, next - last));
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
            last = next + 1;
        }

    }
    ui->tableView->setModel(model);
}

TopResultsWindow::~TopResultsWindow()
{
    delete ui;
}

void TopResultsWindow::on_pushButton_2_clicked()
{
    this->close();
    emit mainWindow();
    delete this;
}

void TopResultsWindow::on_pushButton_clicked()
{
    QFile topRes(QDir::currentPath() + "\\topResults.txt");
    if ((topRes.exists())&&(topRes.open(QIODevice::WriteOnly)))
    {
        topRes.write("");
        topRes.close();
    }
    QStandardItemModel* model = new QStandardItemModel(0, 4, this);
    model->setHeaderData(0, Qt::Horizontal, "Difficulty");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Time");
    model->setHeaderData(3, Qt::Horizontal, "Hints");
    ui->tableView->setModel(model);
}
