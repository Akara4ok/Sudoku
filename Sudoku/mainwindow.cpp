#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    if(!saveFile.exists())
        ui->continueButton->setEnabled(false);
    else
        ui->continueButton->setEnabled(true);
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
        ui->continueButton->setEnabled(false);
    }
    sudokuGeneration = new SudokuGenerationWindow(nullptr, "Easy");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::showResults, this, &MainWindow::showR);
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
    connect(sudokuGeneration, &SudokuGenerationWindow::saveGame, this, &MainWindow::enableContinue);
}

void MainWindow::mediumSudoku()
{
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    if(saveFile.exists())
    {
        saveFile.remove();
        ui->continueButton->setEnabled(false);
    }
    sudokuGeneration = new SudokuGenerationWindow(nullptr, "Medium");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::showResults, this, &MainWindow::showR);
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
    connect(sudokuGeneration, &SudokuGenerationWindow::saveGame, this, &MainWindow::enableContinue);
}

void MainWindow::expertSudoku()
{
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    if(saveFile.exists())
    {
        saveFile.remove();
        ui->continueButton->setEnabled(false);
    }
    sudokuGeneration = new SudokuGenerationWindow(nullptr, "Expert");
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::showResults, this, &MainWindow::showR);
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
    connect(sudokuGeneration, &SudokuGenerationWindow::saveGame, this, &MainWindow::enableContinue);
}

void MainWindow::on_newGameButton_clicked()
{
    difficulty = new DifficultyWindow();
    connect(difficulty, &DifficultyWindow::mainWindow, this, &MainWindow::show);
    connect(difficulty, &DifficultyWindow::easy, this, &MainWindow::easySudoku);
    connect(difficulty, &DifficultyWindow::medium, this, &MainWindow::mediumSudoku);
    connect(difficulty, &DifficultyWindow::expert, this, &MainWindow::expertSudoku);
    this->close();
    difficulty->show();
}

void MainWindow::on_quitButton_clicked()
{
    this->close();
}

void MainWindow::on_solveButton_clicked()
{
    solveSudoku = new SolveSudokuWindow();
    this->close();
    connect(solveSudoku, &SolveSudokuWindow::mainWindow, this, &MainWindow::show);
    solveSudoku->show();
}

void MainWindow::on_topResultsButton_clicked()
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
        ui->continueButton->setEnabled(false);
    }
    topResults = new TopResultsWindow(nullptr, "Congratulations!!!!", sudokuGeneration->getTime(), sudokuGeneration->getDifficulty(),sudokuGeneration->getMistakes(), sudokuGeneration->getHints());
    connect(topResults, &TopResultsWindow::mainWindow, this, &MainWindow::closeR);
    topResults->show();
}

void MainWindow::closeR()
{
    sudokuGeneration->close();
    delete sudokuGeneration;
    this->show();
}

void MainWindow::enableContinue()
{
    ui->continueButton->setEnabled(true);
}

void MainWindow::on_continueButton_clicked()
{
    this->close();
    sudokuGeneration = new SudokuGenerationWindow(nullptr, "", true);
    sudokuGeneration->show();
    connect(sudokuGeneration, &SudokuGenerationWindow::showResults, this, &MainWindow::showR);
    connect(sudokuGeneration, &SudokuGenerationWindow::mainWindow, this, &MainWindow::show);
    connect(sudokuGeneration, &SudokuGenerationWindow::saveGame, this, &MainWindow::enableContinue);

}
