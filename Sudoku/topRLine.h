#ifndef TOPRLINE_H
#define TOPRLINE_H

#include <QString>

struct topRLine
{
    int difficulty; // Рівень складності (0 - легкий, 1 - середній, 2 - експерт)
    QString name; // Ім'я користувача
    int time; // Час витрачений на розв'язання
    int mistakes; // Кількість помилок
    int hints; // Кількість підказок
    topRLine(){}; // Порожній конструктор
};

#endif // TOPRLINE_H
