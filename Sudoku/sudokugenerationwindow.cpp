#include "sudokugenerationwindow.h"
#include "ui_sudokugenerationwindow.h"

SudokuGenerationWindow::SudokuGenerationWindow(QWidget *parent, QString difficulty1, bool continueGame) :
    QDialog(parent),
    ui(new Ui::SudokuGenerationWindow)
{
    ui->setupUi(this);

    cells = {ui->lineEdit, ui->lineEdit_2, ui->lineEdit_3, ui->lineEdit_4, ui->lineEdit_5, ui->lineEdit_6, ui->lineEdit_7, ui->lineEdit_8, ui->lineEdit_9,
            ui->lineEdit_10, ui->lineEdit_11, ui->lineEdit_12, ui->lineEdit_13, ui->lineEdit_14, ui->lineEdit_15, ui->lineEdit_16, ui->lineEdit_17, ui->lineEdit_18,
            ui->lineEdit_19, ui->lineEdit_20, ui->lineEdit_21, ui->lineEdit_22, ui->lineEdit_23, ui->lineEdit_24, ui->lineEdit_25, ui->lineEdit_26, ui->lineEdit_27,
            ui->lineEdit_28, ui->lineEdit_29, ui->lineEdit_30, ui->lineEdit_31, ui->lineEdit_32, ui->lineEdit_33, ui->lineEdit_34, ui->lineEdit_35, ui->lineEdit_36,
            ui->lineEdit_37, ui->lineEdit_38, ui->lineEdit_39, ui->lineEdit_40, ui->lineEdit_41, ui->lineEdit_42, ui->lineEdit_43, ui->lineEdit_44, ui->lineEdit_45,
            ui->lineEdit_46, ui->lineEdit_47, ui->lineEdit_48, ui->lineEdit_49, ui->lineEdit_50, ui->lineEdit_51, ui->lineEdit_52, ui->lineEdit_53, ui->lineEdit_54,
            ui->lineEdit_55, ui->lineEdit_56, ui->lineEdit_57, ui->lineEdit_58, ui->lineEdit_59, ui->lineEdit_60, ui->lineEdit_61, ui->lineEdit_62, ui->lineEdit_63,
            ui->lineEdit_64, ui->lineEdit_65, ui->lineEdit_66, ui->lineEdit_67, ui->lineEdit_68, ui->lineEdit_69, ui->lineEdit_70, ui->lineEdit_71, ui->lineEdit_72,
            ui->lineEdit_73, ui->lineEdit_74, ui->lineEdit_75, ui->lineEdit_76, ui->lineEdit_77, ui->lineEdit_78, ui->lineEdit_79, ui->lineEdit_80, ui->lineEdit_81};

    QRegularExpression rx("[1-9]");
    for (int i = 0; i < 81; i++)
        cells[i]->setValidator(new QRegularExpressionValidator(rx, this));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    if (!continueGame)
    {
        difficulty = difficulty1;
        sudoku.generate(cells, difficulty);
        hints = 0;
        ui->label->setText("Sudoku("+difficulty+")");
        timer->start(1000);
        time = 0;
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
                    if ((st.indexOf("black")!= -1)||(st.indexOf("red")!= -1))
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
                    hints = (s.mid(next, s.length() - next - 1)).toInt();
                    ui->label->setText("Sudoku("+difficulty+")");
                    ui->lcdNumber->display(time);
                    timer->start(1000);
                }
           }
           sudoku.setGrid(grid1);
        }
    }
}

SudokuGenerationWindow::~SudokuGenerationWindow()
{
    delete ui;
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
    sudoku.hint(cells, ind, value);
    if (ind != -1)
    {
    cells[ind]->setText(QString::number(value));
    cells[ind]->setStyleSheet("color: red");
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
    sudoku.showSolutions(cells);
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
    s = difficulty + " " + QString::number(time) + " " + QString::number(hints) + "\n";
    saveFile.write(s.toUtf8());
    saveFile.close();
    emit saveGame();
}
