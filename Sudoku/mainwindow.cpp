#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    difficulty = new DifficultyWindow();
    connect(difficulty, &DifficultyWindow::mainWindow, this, &MainWindow::show);
    connect(difficulty, &DifficultyWindow::easy, this, &MainWindow::easySudoku);
    connect(difficulty, &DifficultyWindow::medium, this, &MainWindow::mediumSudoku);
    connect(difficulty, &DifficultyWindow::expert, this, &MainWindow::expertSudoku);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::easySudoku()
{
    sudokuGeneration = new SudokuGenerationWindow();
    sudokuGeneration->setDifficulty("Easy");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
}

void MainWindow::mediumSudoku()
{
    sudokuGeneration = new SudokuGenerationWindow();
    sudokuGeneration->setDifficulty("Medium");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
}

void MainWindow::expertSudoku()
{
    sudokuGeneration = new SudokuGenerationWindow();
    sudokuGeneration->setDifficulty("Expert");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
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
