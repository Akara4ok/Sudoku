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
    DLX matrix;
    QVector<int> stack;
    void fillExtraMatrix();
    void fillStack(int**, DLX&);
    bool algorithmX();
    void algorithmX(DLX&, int&);
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
    Sudoku(QList<QLineEdit*>);
    void solve(QList<QLineEdit*>&);
    void generate(QList<QLineEdit*>&, QString);
    bool equal(QList<QLineEdit*>);
    void hint(QList<QLineEdit*>, int&, int&);
    void showSolutions(QList<QLineEdit*>);

};

#endif // SUDOKU_H
