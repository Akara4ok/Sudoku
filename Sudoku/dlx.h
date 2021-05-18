#ifndef DLX_H
#define DLX_H

#include "Node.h"

class DLX
{
private:
    Node* goToNode(int, int);
public:
    DLX();
    DLX(DLX*&);
    ~DLX();
    Node* head;
    //DLX(int n);
    void push(int*, int, int);
    void print();
    void cover(Node*);
    void uncover(Node*);
    Node* findMin();
    Node* getColumn(Node*);
    Node* getNode(int);
};

#endif // DLX_H
