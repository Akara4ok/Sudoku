#include "sudoku.h"

Sudoku::Sudoku()
{
    rows = 729;
    columns = 324;
    grid = new int*[9];
    for (int i = 0; i < 9; i++)
    {
        grid[i] = new int [9];
        for (int j = 0; j < 9; j++)
            grid[i][j] = 0;
    }

    extraMatrix = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        extraMatrix[i] = new int[columns];
    }
}

Sudoku::Sudoku(QList<QLineEdit*> list)
{
    rows = 729;
    columns = 324;
    grid = new int*[9];
    for (int i = 0; i < 9; i++)
    {
        grid[i] = new int [9];
        for (int j = 0; j < 9; j++)
            grid[i][j] = 0;
    }

    for (int i = 0; i < list.size(); i++)
        grid[i / 9][i % 9] = (list.at(i)->text()).toInt();
    extraMatrix = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        extraMatrix[i] = new int[columns];
    }
    fillExtraMatrix();
    for (int i = 0; i < rows; i++)
        matrix.push(extraMatrix[i], i, columns);

    fillStack(matrix);
}

void Sudoku::fillExtraMatrix()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            extraMatrix[i][j] = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < 81; j++)
            extraMatrix[i][i / 9] = 1;

    for (int i = 0; i < rows; i++)
        for (int j = 81; j < 162; j++)
            extraMatrix[i][81 + (i / 81) * 9 + i % 9] = 1;

    for (int i = 0; i < rows; i++)
        for (int j = 162; j < 243; j++)
            extraMatrix[i][162 + i % 81] = 1;

    for (int i = 0; i < rows; i++)
        for (int j = 243; j < 324; j++)
            extraMatrix[i][243 + ((i / 81) / 3) * 27 + (((i / 9) % 9) / 3) * 9 + i % 9] = 1;
}

void Sudoku::fillStack(DLX& matrix)
{
    int r;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            if (grid[i][j] != 0)
            {

                r = i * 81 + j * 9 + grid[i][j] - 1;
                stack.push_back(r);

                Node* currentRow = matrix.getNode(r);
                matrix.cover(matrix.getColumn(currentRow));

                Node* currentColumn = currentRow->right;
                while (currentColumn != currentRow)
                {
                    matrix.cover(matrix.getColumn(currentColumn));
                    currentColumn = currentColumn->right;
                }

            }
    }
}

bool Sudoku::algorithmX()
{
    if (matrix.head->right == matrix.head)
    {
        return true;
    }
    Node* node = matrix.findMin();
    matrix.cover(node);
    Node* currentRow = node->down;
    while (currentRow != node)
    {
        stack.push_back(currentRow->rowID);
        Node* currentColumn = currentRow->right;
        while (currentColumn != currentRow)
        {
            matrix.cover(matrix.getColumn(currentColumn));
            currentColumn = currentColumn->right;
        }
        if (!algorithmX())
        {
            stack.pop_back();
            currentColumn = currentRow->left;
            while (currentColumn != currentRow)
            {
                matrix.uncover(matrix.getColumn(currentColumn));
                currentColumn = currentColumn->left;
            }
            currentRow = currentRow->down;
        }
        else
            return true;

    }
    matrix.uncover(node);
    return false;
}

void Sudoku::algorithmX(DLX&, int&count)
{
    if (matrix.head->right == matrix.head)
    {
        count++;
        return;
    }
    Node* node = matrix.findMin();
    matrix.cover(node);
    Node* currentRow = node->down;
    while (currentRow != node)
    {
        stack.push_back(currentRow->rowID);
        Node* currentColumn = currentRow->right;
        while (currentColumn != currentRow)
        {
            matrix.cover(matrix.getColumn(currentColumn));
            currentColumn = currentColumn->right;
        }
        algorithmX(matrix, count);
        stack.pop_back();
        currentColumn = currentRow->left;
        while (currentColumn != currentRow)
        {
            matrix.uncover(matrix.getColumn(currentColumn));
            currentColumn = currentColumn->left;
        }
        currentRow = currentRow->down;
    }
    matrix.uncover(node);
}

void Sudoku::solve(QList<QLineEdit*>&list)
{
    if (algorithmX())
    {
        for (int i = 0; i < stack.size(); i++)
        {
            grid[stack[i] / 81][(stack[i] / 9) % 9] = stack[i] % 9 + 1;
        }
        for (int i = 0; i < 81; i++)
            list.at(i)->setText(QString::number(grid[i / 9][i % 9]));
     }
}

void Sudoku::swapRows(int i, int j)
{
    int* temp;
    temp = grid[i];
    grid[i] = grid[j];
    grid[j] = temp;
}

void Sudoku::swapColumns(int i, int j)
{
    int temp;
    for (int k = 0; k < 9; k++)
    {
        temp = grid[k][i];
        grid[k][i] = grid[k][j];
        grid[k][j] = temp;
    }
}

void Sudoku::swapTripleRows(int i, int j)
{
    for (int k = 0; k < 3; k++)
    {
        swapRows(i + k, j + k);
    }
}

void Sudoku::swapTripleColumns(int i, int j)
{
    for (int k = 0; k < 3; k++)
    {
        swapColumns(i + k, j + k);
    }
}

void Sudoku::transposing()
{
    int temp;
    for (int i = 0; i < 9; i++)
    {
        for (int j = i; j < 9; j++)
        {

            temp = grid[i][j];
            grid[i][j] = grid[j][i];
            grid[j][i] = temp;
        }
    }
}

void Sudoku::randomizeGrid(int total)
{
    int operation;
    for (int i = 0; i < total; i++)
    {
        operation = rand() % 5;
        int k = rand() % 3;
        int n = rand() % 3;
        int m = rand() % 3;
        if (operation == 0)
        {
            swapRows(n + k*3, m + k*3);
        }
        if (operation == 1)
        {
            swapTripleRows(n*3, m*3);
        }
        if (operation == 2)
        {
            swapColumns(n + k * 3, m + k * 3);
        }
        if (operation == 3)
        {
            swapTripleColumns(n*3, m*3);
        }
        if (operation == 4)
        {
            transposing();
        }
    }
}

void Sudoku::randSudoku()
{
    int k;
    for (int i = 0; i < 9; i++)
    {
        k = rand() % 9;
        grid[k][i] = i + 1;
    }
    fillExtraMatrix();
    for (int i = 0; i < rows; i++)
        matrix.push(extraMatrix[i], i, columns);
    fillStack(matrix);
    if (algorithmX())
    {
        for (int i = 0; i < stack.size(); i++)
        {
            grid[stack[i] / 81][(stack[i] / 9) % 9] = stack[i] % 9 + 1;
        }
    }
    randomizeGrid(100);
}

int** Sudoku::deleteCells(int total)
{
    int** result = new int*[9];
    for (int i = 0; i < 9; i++)
    {
        result[i] = new int[9];
        for (int j = 0; j < 9; j++)
            result[i][j] = grid[i][j];
    }
    int i, j;
    int zeroCells = 0;
    fillExtraMatrix();
    QVector<int> indexes;
    for (int i = 0; i < 81; i++)
        indexes.push_back(i);
    while (zeroCells < total)
    {
        if (!indexes.empty())
        {

            int k = indexes[rand() % indexes.size()];
            i = k / 9;
            j = k % 9;
            stack.clear();
            DLX matrix1;
            for (int i = 0; i < rows; i++)
                matrix1.push(extraMatrix[i], i, columns);
            int temp = result[i][j];
            result[i][j] = 0;
            fillStack(matrix1);
            int count = 0;
            algorithmX(matrix, count);
            if (count == 1)
            {
                result[i][j] = 0;
                zeroCells++;
            }
            else
            {
                result[i][j] = temp;
            }
            indexes.erase(indexes.begin() + indexes.indexOf(k));
        }
        else
            break;
    }
    return result;
}

void Sudoku::generate(QList<QLineEdit*>&list, QString difficulty)
{
    randSudoku();
    int**randomSudoku;
    if (QString::compare(difficulty, "Easy") == 0)
        randomSudoku = deleteCells(38);
    if (QString::compare(difficulty, "Medium") == 0)
        randomSudoku = deleteCells(47);
    if (QString::compare(difficulty, "Expert") == 0)
        randomSudoku = deleteCells(55);

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (randomSudoku[i][j]!=0)
                list.at(i*9 + j)->setText(QString::number(randomSudoku[i][j]));
}
