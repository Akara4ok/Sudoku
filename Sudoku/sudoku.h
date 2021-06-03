#ifndef SUDOKU_H
#define SUDOKU_H

#include<QVector>
#include<dlx.h>
#include<QLineEdit>
#include<QString>
#include<QLabel>

class Sudoku
{
    int** grid; // Матриця для збереження судоку
    int** extraMatrix; // Додаткова матриця для відображення судоку, як задачі точного покриття
    int rows, columns; // Кількість рядків і стовпців в extraMatrix
    DLX* matrix = new DLX(); // Структура даних "Dancing Links" для збереження елементів extraMatrix
    QVector<int> stack; // Тут зберігається відповідь
    void fillExtraMatrix(); // Процедура заповнення extraMatrix
    void fillStack(int**, DLX*); // Процедура заповнення stack та matrix відповідно до початкових даниї
    bool algorithmX(); // Знаходить відповідь для задачі точного покриття для матриці matrix
    void algorithmX(DLX*, int&); // Знаходить всі можливі відповіді та повертає за посилання їх кількість
    void swapRows(int, int); // Змінює два рядки місцями
    void swapColumns(int, int); // Змінює два стовпці місцями
    void swapTripleRows(int, int); // Змінює два квадранти по горизонталі місцями
    void swapTripleColumns(int, int); // Змінює два квадранти по вертикалі місцями
    void transposing();  // Транспонування матриці
    void randomizeGrid(int); // Функція для перетворення судоку в біль випадкову
    void randSudoku(); // Функція для генерування судоку
    int** deleteCells(int); // Функція видалення клітинок із судоку
public:
    Sudoku(); // Конструктор, який створює матрицю grid та порожню матрицю extraMatrix
    Sudoku(QVector<QLineEdit*>); // Конструктор, який зчитує початкові дані у grid та створює порожню матрицю extraMatrix
    ~Sudoku();// Видаляє об'єкт судоку
    void setGrid(int**grid1); // Встановлює судоку, яка була передана як параметр
    bool solve(QVector<QLineEdit*>&); //Повертає true, якщо судоку можна розв'язати(а також за посиланням передає розв'язк). Інакше false
    int** generate(QString); // Генерує судоку уже із видаленими кліинками відповідно до рівня складності
    bool equal(QVector<QLineEdit*>); // Порівнює дві матриці і повертає true, якщо вони рівні. Інакше false
    int** getGrid(); // Повертає матрицю grid
    bool isCorrect(int, int); // Повертає true, якщо передене число і індекс співпадають із правильним розв'язком

};

#endif // SUDOKU_H
