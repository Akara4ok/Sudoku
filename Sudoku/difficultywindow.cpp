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
    delete this;
}

void DifficultyWindow::on_mediumButton_clicked()
{
    this->close();
    emit medium();
    delete this;
}

void DifficultyWindow::on_expertButton_clicked()
{
    this->close();
    emit expert();
    delete this;
}


void DifficultyWindow::on_backButton_clicked()
{
    this->close();
    emit mainWindow();
    delete this;
}


