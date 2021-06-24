#ifndef DLX_H
#define DLX_H

#include "Node.h"

class DLX
{
private:
    Node* goToNode(int, int); //Повертає вузол у якого є відповідні значення рядка і стовпця
    int size;
public:
    DLX(int size1 = 3); //Створю заготовку DLX структури для подальшого заповнення
    DLX(DLX*&); // Конструктор копіювання
    ~DLX(); // Деструктор, який видаляє всі вузли матриці
    Node* head; // Вказівник на початок структури
    void push(int*, int, int); // Додає до даної структури рядок row під номером r довжини n
    void cover(Node*); // Закреслює всі суміжні рядки та стовпчики вузлу Node
    void uncover(Node*); // Відміняє закреслення від процедури cover
    Node* findMin(); //Поертає вказівник на стовпчик з мінімальною кількістю одиниць
    Node* getColumn(Node*); // Повертає вказівникна стовпчик у якому є елемент Node
    Node* getNode(int); // Повертає вказівник на перший єлемент у рядку r
    int getSize(){return size;};
};

#endif // DLX_H
