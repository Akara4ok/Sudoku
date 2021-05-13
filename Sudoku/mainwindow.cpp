#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    if(!saveFile.exists())
        ui->pushButton_2->setEnabled(false);
    else
        ui->pushButton_2->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::easySudoku()
{
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    if(saveFile.exists())
    {
        saveFile.remove();
        ui->pushButton_2->setEnabled(false);
    }
    sudokuGeneration = new SudokuGenerationWindow(nullptr, "Easy");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::showResults, this, &MainWindow::showR);
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
    connect(sudokuGeneration, &SudokuGenerationWindow::saveGame, this, &MainWindow::enableButton);
}

void MainWindow::mediumSudoku()
{
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    if(saveFile.exists())
    {
        saveFile.remove();
        ui->pushButton_2->setEnabled(false);
    }
    sudokuGeneration = new SudokuGenerationWindow(nullptr, "Medium");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::showResults, this, &MainWindow::showR);
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
    connect(sudokuGeneration, &SudokuGenerationWindow::saveGame, this, &MainWindow::enableButton);
}

void MainWindow::expertSudoku()
{
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    if(saveFile.exists())
    {
        saveFile.remove();
        ui->pushButton_2->setEnabled(false);
    }
    sudokuGeneration = new SudokuGenerationWindow(nullptr, "Expert");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::showResults, this, &MainWindow::showR);
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
    connect(sudokuGeneration, &SudokuGenerationWindow::saveGame, this, &MainWindow::enableButton);
}

void MainWindow::on_pushButton_clicked()
{
    difficulty = new DifficultyWindow();
    connect(difficulty, &DifficultyWindow::mainWindow, this, &MainWindow::show);
    connect(difficulty, &DifficultyWindow::easy, this, &MainWindow::easySudoku);
    connect(difficulty, &DifficultyWindow::medium, this, &MainWindow::mediumSudoku);
    connect(difficulty, &DifficultyWindow::expert, this, &MainWindow::expertSudoku);
    this->close();
    difficulty->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_3_clicked()
{
    solveSudoku = new SolveSudokuWindow();
    this->close();
    connect(solveSudoku, &SolveSudokuWindow::mainWindow, this, &MainWindow::show);
    solveSudoku->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    topResults = new TopResultsWindow();
    this->close();
    connect(topResults, &TopResultsWindow::mainWindow, this, &MainWindow::show);
    topResults->show();
}

void MainWindow::showR()
{
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    if(saveFile.exists())
    {
        saveFile.remove();
        ui->pushButton_2->setEnabled(false);
    }
    topResults = new TopResultsWindow(nullptr, "Congratulations!!!!", sudokuGeneration->getTime(), sudokuGeneration->getDifficulty(), sudokuGeneration->getHints());
    connect(topResults, &TopResultsWindow::mainWindow, this, &MainWindow::closeR);
    topResults->show();
}

void MainWindow::closeR()
{
    sudokuGeneration->close();
    delete sudokuGeneration;
    this->show();
}

void MainWindow::enableButton()
{
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    sudokuGeneration = new SudokuGenerationWindow(nullptr, "", true);
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::showResults, this, &MainWindow::showR);
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
    connect(sudokuGeneration, &SudokuGenerationWindow::saveGame, this, &MainWindow::enableButton);

}
