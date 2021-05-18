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


void DifficultyWindow::on_easyButton_clicked()
{
    this->close();
    emit easy();
}

void DifficultyWindow::on_mediumButton_clicked()
{
    this->close();
    emit medium();
}

void DifficultyWindow::on_expertButton_clicked()
{
    this->close();
    emit expert();
}


void DifficultyWindow::on_backButton_clicked()
{
    this->close();
    emit mainWindow();
}


