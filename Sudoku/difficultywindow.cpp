#include "difficultywindow.h"
#include "ui_difficultywindow.h"
#include "mainwindow.h"

DifficultyWindow::DifficultyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DifficultyWindow)
{
    ui->setupUi(this);
}

DifficultyWindow::~DifficultyWindow()
{
    delete ui;
}


void DifficultyWindow::on_pushButton_clicked()
{
    this->close();
    emit easy();
}

void DifficultyWindow::on_pushButton_2_clicked()
{
    this->close();
    emit medium();
}

void DifficultyWindow::on_pushButton_3_clicked()
{
    this->close();
    emit expert();
}


void DifficultyWindow::on_pushButton_4_clicked()
{
    this->close();
    emit mainWindow();
}


