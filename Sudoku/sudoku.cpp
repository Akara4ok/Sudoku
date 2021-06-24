#include "sudoku.h"

Sudoku::Sudoku()
{
}

void Sudoku::setGrid(int**grid1)
{
    grid = grid1;
}

Sudoku::Sudoku(QVector<QLineEdit*> cells)
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

    for (int i = 0; i < cells.size(); i++)
        grid[i / 9][i % 9] = (cells[i]->text()).toInt();
    extraMatrix = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        extraMatrix[i] = new int[columns];
    }
    fillExtraMatrix();
    for (int i = 0; i < rows; i++)
        matrix->push(extraMatrix[i], i, columns);

    fillStack(grid, matrix);
}

void Sudoku::fillExtraMatrix()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            extraMatrix[i][j] = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < pow(size, 4); j++)
            extraMatrix[i][i / (int)pow(size, 2)] = 1;

    for (int i = 0; i < rows; i++)
        for (int j = pow(size, 4); j < 2*pow(size, 4); j++)
            extraMatrix[i][(int)pow(size, 4) + (int)(i / pow(size, 4)) * (int)pow(size, 2) + i % (int)pow(size, 2)] = 1;

    for (int i = 0; i < rows; i++)
        for (int j = 2*pow(size, 4); j < 3*pow(size, 4); j++)
            extraMatrix[i][(int)(2*pow(size, 4)) + i % (int)pow(size, 4)] = 1;

    for (int i = 0; i < rows; i++)
        for (int j = 3*pow(size, 4); j < columns; j++)
            extraMatrix[i][(int)(3*pow(size, 4)) + ((i / (int)pow(size, 4)) / size) * (int)pow(size, 3) + (((i / (int)pow(size, 2)) % (int)pow(size, 2)) / size) * (int)pow(size, 2) + i % (int)pow(size, 2)] = 1;
}

void Sudoku::fillStack(int**grid, DLX* matrix)
{
    int r;
    for (int i = 0; i < pow(size, 2); i++)
    {
        for (int j = 0; j < pow(size, 2); j++)
            if (grid[i][j] != 0)
            {

                r = i * pow(size, 4) + j * pow(size, 2) + grid[i][j] - 1;
                stack.push_back(r);

                Node* currentRow = matrix->getNode(r);
                if (currentRow->rowID != -1)
                {
                    matrix->cover(matrix->getColumn(currentRow));

                    Node* currentColumn = currentRow->right;
                    while (currentColumn != currentRow)
                    {
                        matrix->cover(matrix->getColumn(currentColumn));
                        currentColumn = currentColumn->right;
                    }
                }

            }
    }
}

bool Sudoku::algorithmX()
{
    if (matrix->head->right == matrix->head)
    {
        return true;
    }
    Node* node = matrix->findMin();
    matrix->cover(node);
    Node* currentRow = node->down;
    while (currentRow != node)
    {
        stack.push_back(currentRow->rowID);
        Node* currentColumn = currentRow->right;
        while (currentColumn != currentRow)
        {
            matrix->cover(matrix->getColumn(currentColumn));
            currentColumn = currentColumn->right;
        }
        if (!algorithmX())
        {
            stack.pop_back();
            currentColumn = currentRow->left;
            while (currentColumn != currentRow)
            {
                matrix->uncover(matrix->getColumn(currentColumn));
                currentColumn = currentColumn->left;
            }
            currentRow = currentRow->down;
        }
        else
        {
            return true;
        }

    }
    matrix->uncover(node);
    return false;
}

void Sudoku::algorithmX(DLX* matrix, int&count)
{
    if (matrix->head->right == matrix->head)
    {
        count++;
        return;
    }
    Node* node = matrix->findMin();
    matrix->cover(node);
    Node* currentRow = node->down;
    while (currentRow != node)
    {
        stack.push_back(currentRow->rowID);
        Node* currentColumn = currentRow->right;
        while (currentColumn != currentRow)
        {
            matrix->cover(matrix->getColumn(currentColumn));
            currentColumn = currentColumn->right;
        }
        algorithmX(matrix, count);
        stack.pop_back();
        currentColumn = currentRow->left;
        while (currentColumn != currentRow)
        {
            matrix->uncover(matrix->getColumn(currentColumn));
            currentColumn = currentColumn->left;
        }
        currentRow = currentRow->down;
    }
    matrix->uncover(node);
}

bool Sudoku::solve(QVector<QLineEdit*>&cells)
{
    bool fl = true;
    if (algorithmX())
    {
        for (int i = 0; i < stack.size(); i++)
        {
            grid[stack[i] / 81][(stack[i] / 9) % 9] = stack[i] % 9 + 1;
        }

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                for (int l = 0; l < 9; l++)
                    if ((grid[i][j] == grid[i][l])&&(j!=l))
                        fl = false;
                for (int l = 0; l < 9; l++)
                    if ((grid[i][j] == grid[l][j])&&(i!=l))
                        fl = false;
                for (int l = (i / 3) * 3; l < (i / 3 + 1) * 3; l++)
                    for (int m = (j / 3) * 3; m < (j / 3 + 1) * 3; m++)
                        if ((grid[i][j] == grid[l][m]) && (l != i) && (m != j))
                            fl = false;
            }
        }
        if (fl)
        {
            return true;
        }
        else
            return false;
     }
    else
        return false;
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
    for (int k = 0; k < pow(size, 2); k++)
    {
        temp = grid[k][i];
        grid[k][i] = grid[k][j];
        grid[k][j] = temp;
    }
}

void Sudoku::swapTripleRows(int i, int j)
{
    for (int k = 0; k < size; k++)
    {
        swapRows(i + k, j + k);
    }
}

void Sudoku::swapTripleColumns(int i, int j)
{
    for (int k = 0; k < size; k++)
    {
        swapColumns(i + k, j + k);
    }
}

void Sudoku::transposing()
{
    int temp;
    for (int i = 0; i < pow(size, 2); i++)
    {
        for (int j = i; j < pow(size, 2); j++)
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
        int k = rand() % size;
        int n = rand() % size;
        int m = rand() % size;
        if (operation == 0)
        {
            swapRows(n + k*size, m + k*size);
        }
        if (operation == 1)
        {
            swapTripleRows(n*size, m*size);
        }
        if (operation == 2)
        {
            swapColumns(n + k * size, m + k * size);
        }
        if (operation == 3)
        {
            swapTripleColumns(n*size, m*size);
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
    for (int i = 0; i < pow(size, 2); i++)
    {
        k = rand() % (int)pow(size, 2);
        grid[k][i] = i + 1;
    }
    fillExtraMatrix();
    for (int i = 0; i < rows; i++)
        matrix->push(extraMatrix[i], i, columns);
    fillStack(grid, matrix);
    if (algorithmX())
    {
        for (int i = 0; i < stack.size(); i++)
        {
            grid[(int)(stack[i] / pow(size, 4))][(int)((int)(stack[i] / pow(size, 2)) % (int)pow(size, 2))] = stack[i] % (int)pow(size, 2) + 1;
        }
    }
    randomizeGrid(100);
}

int** Sudoku::deleteCells(int total)
{
    int** result = new int*[(int)pow(size, 2)];
    for (int i = 0; i < pow(size, 2); i++)
    {
        result[i] = new int[(int)pow(size, 2)];
        for (int j = 0; j < pow(size, 2); j++)
            result[i][j] = grid[i][j];
    }
    stack.clear();
    int i, j;
    int zeroCells = 0;
    fillExtraMatrix();
    QVector<int> indexes;
    for (int i = 0; i < pow(size, 4); i++)
        indexes.push_back(i);
    DLX* matrix1 = new DLX(size);
    for (int i = 0; i < rows; i++)
        matrix1->push(extraMatrix[i], i, columns);
    while (zeroCells < total)
    {
        if (!indexes.empty())
        {

            int k = indexes[rand() % indexes.size()];
            i = k / pow(size, 2);
            j = k % (int)pow(size, 2);
            stack.clear();
            DLX* matrix = new DLX(matrix1);
            int temp = result[i][j];
            result[i][j] = 0;
            fillStack(result, matrix);
            int count = 0;
            algorithmX(matrix, count);
            //count = 1;
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
            delete matrix;
        }
        else
            break;
    }
    delete matrix1;
    return result;
}

int** Sudoku::generate(QString difficulty)
{
    if(QString::compare(difficulty, "Giant") == 0)
        size = 4;
    else
        size = 3;
    rows = pow(size, 6);
    columns = pow(size, 4)*4;
    grid = new int*[(int)pow(size, 2)];
    for (int i = 0; i < pow(size, 2); i++)
    {
        grid[i] = new int [(int)pow(size, 2)];
        for (int j = 0; j < pow(size, 2); j++)
            grid[i][j] = 0;
    }

    extraMatrix = new int* [rows];
    for (int i = 0; i < rows; i++)
    {
        extraMatrix[i] = new int[columns];
    }
    randSudoku();
    int**randomSudoku;
    if (QString::compare(difficulty, "Easy") == 0)
        randomSudoku = deleteCells(38);
    if (QString::compare(difficulty, "Medium") == 0)
        randomSudoku = deleteCells(47);
    if (QString::compare(difficulty, "Expert") == 0)
        randomSudoku = deleteCells(55);
    if (QString::compare(difficulty, "Giant") == 0)
        randomSudoku = deleteCells(5);
    return randomSudoku;
}

bool Sudoku::equal(QVector<QLineEdit*>cells)
{
    bool result = true;
    for (int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if ((cells[i*9 + j]->text()).toInt() != grid[i][j])
                result = false;
    return result;
}

int** Sudoku::getGrid()
{
    return grid;
}

bool Sudoku::isCorrect(int ind, int value)
{
    if (grid[ind / 9][ind % 9]==value)
        return true;
    else
        return false;
}

Sudoku::~Sudoku()
{
    for (int i = 0; i < 9; i++)
        delete grid[i];
    delete grid;

    for (int i = 0; i < 729; i++)
        delete extraMatrix[i];
    delete extraMatrix;

    delete matrix;
}
