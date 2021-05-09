#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    difficulty = new DifficultyWindow();
    connect(difficulty, &DifficultyWindow::mainWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   this->close();
   difficulty->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    this->close();
}
