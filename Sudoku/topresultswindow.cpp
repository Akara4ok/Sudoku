#include "topresultswindow.h"
#include "ui_topresultswindow.h"

TopResultsWindow::TopResultsWindow(QWidget *parent, QString s, int time) :
    QDialog(parent),
    ui(new Ui::TopResultsWindow)
{
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel(1, 3, this);
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Time");
    model->setHeaderData(2, Qt::Horizontal, "Hints");
    ui->tableView->setModel(model);
    ui->label->setText(s);
    if (time != 0)
        ui->label_3->setText("Your time: " + QString::number(time) + "s");
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
