#include "topresultswindow.h"
#include "ui_topresultswindow.h"

TopResultsWindow::TopResultsWindow(QWidget *parent, QString s, int time, QString difficulty, int hints) :
    QDialog(parent),
    ui(new Ui::TopResultsWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 4, this);
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
        Quartet q;
        model->insertRow(i);
        table.push_back(q);
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
        QString s;
        s = model->data(model->index(i,0)).toString();
        if (QString::compare(s, "Easy") == 0)
            table[i].difficulty = 0;
        if (QString::compare(s, "Medium") == 0)
            table[i].difficulty = 1;
        if (QString::compare(s, "Expert") == 0)
            table[i].difficulty = 2;
        table[i].name = model->data(model->index(i,1)).toString();
        table[i].time = model->data(model->index(i,2)).toInt();
        table[i].hints = model->data(model->index(i,3)).toInt();
    }
    sort();
    setTable();
    ui->tableView->verticalHeader()->setStyleSheet("background-color: white");
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

void TopResultsWindow::sort()
{
    Quartet temp;
    if (timeSort)
    {
        for (int i = 0; i < table.size(); i++)
            for(int j = i + 1; j < table.size(); j++)
                if (table[i].time > table[j].time)
                {
                   temp = table[i];
                   table[i] = table[j];
                   table[j] = temp;
            }
    }
    if (difficultySort)
    {
        for (int i = 0; i < table.size(); i++)
            for(int j = i + 1; j < table.size(); j++)
                if (table[i].difficulty < table[j].difficulty)
                {
                   temp = table[i];
                   table[i] = table[j];
                   table[j] = temp;
            }
    }
    if (hintsSort)
    {
        for (int i = 0; i < table.size(); i++)
            for(int j = i + 1; j < table.size(); j++)
                if (table[i].hints > table[j].hints)
                {
                   temp = table[i];
                   table[i] = table[j];
                   table[j] = temp;
            }
    }
    if (nameSort)
    {
        for (int i = 0; i < table.size(); i++)
            for(int j = i + 1; j < table.size(); j++)
                if (QString::compare(table[i].name, table[j].name)>0)
                {
                   temp = table[i];
                   table[i] = table[j];
                   table[j] = temp;
            }
    }
}

void TopResultsWindow::setTable()
{
    for (int i = 0; i < table.size(); i++)
    {
        QString s;
        if(table[i].difficulty == 0)
            s = "Easy";
        if(table[i].difficulty == 1)
            s = "Medium";
        if(table[i].difficulty == 2)
            s = "Expert";
        QStandardItem *item= new QStandardItem();
        item -> setText(s);
        item->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 0, item);
        QStandardItem *item1= new QStandardItem();
        item1 -> setText(table[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 1, item1);
        QStandardItem *item2= new QStandardItem();
        item2 -> setText(QString::number(table[i].time));
        item2->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 2, item2);
        QStandardItem *item3= new QStandardItem();
        item3 -> setText(QString::number(table[i].hints));
        item3->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 3, item3);
    }
    ui->tableView->setModel(model);
}

void TopResultsWindow::on_radioButton_clicked()
{
    difficultySort = true;
    nameSort = false;
    timeSort = false;
    hintsSort = false;
    sort();
    setTable();
}

void TopResultsWindow::on_radioButton_2_clicked()
{
    difficultySort = false;
    nameSort = true;
    timeSort = false;
    hintsSort = false;
    sort();
    setTable();
}

void TopResultsWindow::on_radioButton_3_clicked()
{
    difficultySort = false;
    nameSort = false;
    timeSort = true;
    hintsSort = false;
    sort();
    setTable();
}

void TopResultsWindow::on_radioButton_4_clicked()
{
    difficultySort = false;
    nameSort = false;
    timeSort = false;
    hintsSort = true;
    sort();
    setTable();
}
