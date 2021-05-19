#ifndef SUDOKU_H
#define SUDOKU_H

#include<QVector>
#include<dlx.h>
#include<QLineEdit>
#include<QString>
#include<QLabel>

class Sudoku
{
    int** grid;
    int** extraMatrix;
    int rows, columns;
    DLX* matrix = new DLX();
    QVector<int> stack;
    void fillExtraMatrix();
    void fillStack(int**, DLX*);
    bool algorithmX();
    void algorithmX(DLX*, int&);
    void swapRows(int, int);
    void swapColumns(int, int);
    void swapTripleRows(int, int);
    void swapTripleColumns(int, int);
    void transposing();
    void randomizeGrid(int);
    void randSudoku();
    int** deleteCells(int);
public:
    Sudoku();
    Sudoku(QVector<QLineEdit*>);
    ~Sudoku();
    void setGrid(int**grid1);
    bool solve(QVector<QLineEdit*>&);
    void generate(QVector<QLineEdit*>&, QString);
    bool equal(QVector<QLineEdit*>);
    void hint(QVector<QLineEdit*>, int&, int&);
    void showSolutions(QVector<QLineEdit*>);
    int** getGrid();
    bool isCorrect(int, int);

};

#endif // SUDOKU_H
