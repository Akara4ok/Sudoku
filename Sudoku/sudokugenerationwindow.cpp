#include "sudokugenerationwindow.h"
#include "ui_sudokugenerationwindow.h"

SudokuGenerationWindow::SudokuGenerationWindow(QWidget *parent, QString difficulty1, bool continueGame) :
    QDialog(parent),
    ui(new Ui::SudokuGenerationWindow)
{
    ui->setupUi(this);
    ui->gridLayout->setSpacing(10);
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
            ui->gridLayout->addLayout(grids.back(), i, j);
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
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    if (!continueGame)
    {
        difficulty = difficulty1;
        int** randomSudoku = sudoku.generate(difficulty);
        hints = 0;
        ui->label->setText("Sudoku("+difficulty+")");
        timer->start(1000);
        mistakes = 0;
        time = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (randomSudoku[i][j]!=0)
                {
                    cells[i*9 + j]->setText(QString::number(randomSudoku[i][j]));
                    cells[i*9 + j]->setReadOnly(true);
                    cells[i*9 + j]->setStyleSheet("color: black");
                }
    }
    else
    {
        QFile saveFile(QDir::currentPath() + "\\saves.txt");
        if ((saveFile.exists())&&(saveFile.open(QIODevice::ReadOnly)))
        {
           QString s = "";
           int**grid1 = new int*[9];
           for (int i = 0; i < 9; i++)
           {
                grid1[i] = new int[9];
                s = saveFile.readLine();
                for (int j = 0; j < 9; j++)
                    grid1[i][j] = s[j*2].digitValue();
           }
           while(!saveFile.atEnd())
           {
                s = saveFile.readLine();
                if (s[0].isDigit())
                {
                    int last = 0;
                    int next = s.indexOf(" ", last);
                    int ind = s.mid(last, next - last).toInt();
                    last = next + 1;
                    next = s.indexOf(" ", last);
                    cells[ind]->setText(s.mid(last, next - last));
                    QString st = s.mid(next, s.length() - next - 1);
                    cells[ind]->setStyleSheet(st);
                    if ((st.indexOf("black")!= -1)||(st.indexOf("purple")!= -1))
                    {
                        cells[ind]->setReadOnly(true);
                    }
                }
                else
                {
                    int last = 0;
                    int next = s.indexOf(" ", last);
                    difficulty = s.mid(last, next - last);
                    last = next + 1;
                    next = s.indexOf(" ", last);
                    time = (s.mid(last, next - last)).toInt();
                    last = next + 1;
                    next = s.indexOf(" ", last);
                    mistakes = (s.mid(last, next - last)).toInt();
                    hints = (s.mid(next, s.length() - next - 1)).toInt();
                    ui->label->setText("Sudoku("+difficulty+")");
                    ui->lcdNumber->display(time);
                    timer->start(1000);
                }
           }
           sudoku.setGrid(grid1);
        }
    }
    for (int i = 0; i < 81; i++)
    {
         connect(cells[i], SIGNAL(textEdited(const QString &)), this, SLOT(checkForCorrect()));
    }
}

SudokuGenerationWindow::~SudokuGenerationWindow()
{
    delete ui;
    delete timer;
}

void SudokuGenerationWindow::onTimeout()
{
    time++;
    ui->lcdNumber->display(time);
}

void SudokuGenerationWindow::on_quitButton_clicked()
{
    this->close();
    emit mainWindow();
    delete this;
}

void SudokuGenerationWindow::on_clearButton_clicked()
{
    for (int i = 0; i < cells.size(); i++)
        if (!cells[i]->isReadOnly())
            cells[i]->clear();
}

void SudokuGenerationWindow::on_checkButton_clicked()
{
    if (sudoku.equal(cells))
    {
        timer->stop();
        emit showResults();
    }
    else
    {
        timer->stop();
        QMessageBox::about(0, "Incorrect", "You've made some mistakes. Try again");
        timer->start(1000);
    }
}

int SudokuGenerationWindow::getTime()
{
    return time;
}

void SudokuGenerationWindow::on_hintButton_clicked()
{
    hints++;
    int ind, value;
    int**grid = sudoku.getGrid();
    QVector<int> avail;
    for (int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if ((cells[i*9 + j]->text()).toInt() != grid[i][j])
                avail.push_back(i*9 + j);
    ind = -1;
    if (!avail.empty())
    {
        int r = rand()%(avail.size());
        ind = avail.at(r);
        value = grid[ind / 9][ind % 9];
    }
    if (ind != -1)
    {
    cells[ind]->setText(QString::number(value));
    cells[ind]->setStyleSheet("color: purple");
    cells[ind]->setReadOnly(true);
    int r, c;
    r = ind / 9 + 1;
    c = ind% 9 + 1;
    QMessageBox::about(0, "Hint", "In (" + QString::number(r) + " row, " + QString::number(c) + " column) you sholud put: " + QString::number(value));
    }
}

void SudokuGenerationWindow::on_showSolutionButton_clicked()
{
    timer->stop();
    //sudoku.showSolutions(cells);
    int**result = sudoku.getGrid();
    for (int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
        {
            cells[i*9 + j]->setReadOnly(true);
            if ((cells[i*9 + j]->text()).toInt() != result[i][j])
            {
                cells[i*9 + j]->setText(QString::number(result[i][j]));
                cells[i*9 + j]->setStyleSheet("background-color: white; color: black");
            }
        }
    ui->hintButton->setEnabled(false);
    //ui->checkButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->showSolutionButton->setEnabled(false);
}

void SudokuGenerationWindow::on_rulesButton_clicked()
{
    if (timer->isActive())
    {
        timer->stop();
        QMessageBox::about(0, "Rules", "Судоку – це головоломка з числами. Ігрове поле – це квадрат 9х9, який розділений на менші квадрати 3х3. На початку гри в деяких клітинках вже стоять числа(підсказки). Гравець повинен вписати числа в пусті клітинки, так щоб в кожному рядку, стовпчику та квадраті 3х3 кожна цифра зустрічалась тільки один раз.");
        timer->start(1000);
    }
    else
        QMessageBox::about(0, "Rules", "Судоку – це головоломка з числами. Ігрове поле – це квадрат 9х9, який розділений на менші квадрати 3х3. На початку гри в деяких клітинках вже стоять числа(підсказки). Гравець повинен вписати числа в пусті клітинки, так щоб в кожному рядку, стовпчику та квадраті 3х3 кожна цифра зустрічалась тільки один раз.");
}

QString SudokuGenerationWindow::getDifficulty()
{
    return difficulty;
}
int SudokuGenerationWindow::getHints()
{
    return hints;
}
int SudokuGenerationWindow::getMistakes()
{
    return mistakes;
}

void SudokuGenerationWindow::on_saveButton_clicked()
{
    int** grid1 = sudoku.getGrid();
    QFile saveFile(QDir::currentPath() + "\\saves.txt");
    saveFile.open(QIODevice::WriteOnly);
    QString s = "";
    for (int i = 0; i < 9; i++)
    {
        s = "";

        for (int j = 0; j < 9; j++)
            s = s + QString::number(grid1[i][j]) + " ";
        s = s + "\n";
        saveFile.write(s.toUtf8());
    }
    for (int  i = 0; i < 81; i++)
    {
        s = "";
        if (cells[i]->text()!="")
            s = QString::number(i) + " " + cells[i]->text() + " " + cells[i]->styleSheet() + "\n";
        saveFile.write(s.toUtf8());
    }
    s = difficulty + " " + QString::number(time) + " "+ QString::number(mistakes) + " " + QString::number(hints) + "\n";
    saveFile.write(s.toUtf8());
    saveFile.close();
    emit saveGame();
}

void SudokuGenerationWindow::checkForCorrect()
{
    QLineEdit *line = (QLineEdit*) sender();
    int ind;
    for (int i = 0; i < 81; i++)
        if (cells[i] == line)
            ind = i;
    if ((!sudoku.isCorrect(ind, (cells[ind]->text()).toInt()))&&(line->text()!=""))
    {
        line -> setStyleSheet("color: red; background-color:white");
        mistakes++;
    }
    else
        line -> setStyleSheet("color: blue; background-color:white");
}

