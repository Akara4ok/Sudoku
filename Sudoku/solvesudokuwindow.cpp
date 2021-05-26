#include "solvesudokuwindow.h"
#include "ui_solvesudokuwindow.h"

SolveSudokuWindow::SolveSudokuWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolveSudokuWindow)
{
    ui->setupUi(this);
    ui->gridLayout_2->setSpacing(10);
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            grids.push_back(new QGridLayout);
            grids.back()->minimumSize().setHeight(90);
            grids.back()->minimumSize().setWidth(90);
            grids.back()->maximumSize().setHeight(90);
            grids.back()->maximumSize().setWidth(90);
            grids.back()->setSizeConstraint(QLayout::SetMaximumSize);
            grids.back()->setSpacing(0);
            ui->gridLayout_2->addLayout(grids.back(), i, j);
        }
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                cells.push_back(new QLineEdit);
                cells.back()->setFixedHeight(30);
                cells.back()->setFixedWidth(30);
                cells.back()->setAlignment(Qt::AlignCenter);
                QFont font;
                font.setPixelSize(17);
                cells.back()->setFont(font);
                cells.back()->setStyleSheet("QLineEdit{	border-width: 1px; background-color: white; border-color:black}  QLineEdit:hoover{border-width: 1px;	; color: blue; background-color: white; border-color:black}");
                grids[3*i + k / 3]->addWidget(cells.back(), j, k % 3);
            }
        }
    }

    QRegularExpression rx("[1-9]");
    for (int i = 0; i < 81; i++)
        cells[i]->setValidator(new QRegularExpressionValidator(rx, this));
}

SolveSudokuWindow::~SolveSudokuWindow()
{
    delete ui;
}

void SolveSudokuWindow::on_quitButton_clicked()
{
    this->close();
    emit mainWindow();
    delete this;
}

void SolveSudokuWindow::on_solveButton_clicked()
{
    sudoku = new Sudoku(cells);
    if(sudoku->solve(cells))
    {
        int**grid = sudoku->getGrid();
        for (int i = 0; i < 81; i++)
        {
            cells[i]->setText(QString::number(grid[i / 9][i % 9]));
            cells[i]->setReadOnly(true);
        }
        delete sudoku;
    }
    else
    {
        QMessageBox::about(0, "Error", "Wrong sudoku");
    }
}

void SolveSudokuWindow::on_clearButton_clicked()
{
    for (int i = 0; i < cells.size(); i++)
    {
        cells[i]->setReadOnly(false);
        cells[i]->clear();
    }
}

void SolveSudokuWindow::on_saveButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(0, "Save", "", "*.txt");
    QFile saveFile(path);
    saveFile.open(QIODevice::WriteOnly);
    QString s = "";
    for (int i = 0; i < 9; i++)
    {
        s = "";
        for (int j = 0; j < 9; j++)
            s = s + cells[i*9 + j]->text() + " ";
        s = s + "\n";
        saveFile.write(s.toUtf8());
    }
    saveFile.close();
}
