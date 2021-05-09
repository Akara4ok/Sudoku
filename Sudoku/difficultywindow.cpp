#include "difficultywindow.h"
#include "ui_difficultywindow.h"
#include "sudokugenerationwindow.h"

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
    SudokuGenerationWindow generation;
    generation.setModal(true);
    generation.exec();
}
