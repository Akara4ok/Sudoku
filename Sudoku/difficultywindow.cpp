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
    sudoku = new SudokuGenerationWindow(nullptr, "Easy");
    connect(sudoku, &SudokuGenerationWindow::difficulty, this, &DifficultyWindow::show);
    this->close();
    sudoku->show();
}

void DifficultyWindow::on_pushButton_2_clicked()
{
    sudoku = new SudokuGenerationWindow(nullptr, "Medium");
    connect(sudoku, &SudokuGenerationWindow::difficulty, this, &DifficultyWindow::show);
    this->close();
    sudoku->show();
}

void DifficultyWindow::on_pushButton_3_clicked()
{
    sudoku = new SudokuGenerationWindow(nullptr, "Expert");
    connect(sudoku, &SudokuGenerationWindow::difficulty, this, &DifficultyWindow::show);
    this->close();
    sudoku->show();
}


void DifficultyWindow::on_pushButton_4_clicked()
{
    this->close();
    emit mainWindow();
}
