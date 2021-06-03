#ifndef NODE_H
#define NODE_H

struct Node
{
    int rowID; //Номер рядку
    int colID; //Номер стовпчика
    int count; //Кількість елементів у стовпчику
    Node* left; // Покажчик на лівий елемент
    Node* right; // Покажчик на правий елемент
    Node* up; // Покажчик на верхній елемент
    Node* down; // Покажчик на нижній елемент
    Node() { left = nullptr; right = nullptr; up = nullptr; down = nullptr; rowID = -1; colID = -1; count = -1; }; // Конструктор створення порожнього вузла
    Node(Node* &node1) { left = nullptr; right = nullptr; up = nullptr; down = nullptr; rowID = node1->rowID; colID = node1->colID; count = node1->count; }; // Конструктор копіювання
    ~Node() {left = nullptr; right = nullptr; up = nullptr; down = nullptr; }// Видалення вузла
};

#endif // NODE_H
