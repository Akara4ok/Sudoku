#include "dlx.h"
#include <iostream>

using namespace std;

/*DLX::DLX()
{
    head = nullptr;
}*/

DLX::DLX()
{
    head = new Node();
    Node* current = head;
    for (int i = 0; i < 324; i++)
    {
        Node* newNode = new Node();
        newNode->colID = i;
        current->right = newNode;
        newNode->down = newNode;
        newNode->up = newNode;
        newNode->left = current;
        current = newNode;
        current->count = 0;
    }
    current->right = head;
    head->left = current;
}

DLX::DLX(DLX*&DLX1)
{
    head = new Node(DLX1->head);
    Node* current1 = DLX1->head->right;
    Node* current = new Node(current1);
    head->right = current;
    current->left = head;
    Node* headCol = current;
    while (current1 != DLX1->head)
    {
        current1 = current1->down;
        while (current1->rowID != -1)
        {
            Node* node = new Node(current1);
            current->down = node;
            node->up = current;
            current = node;
            current1 = current1->down;
        }
        current->down = headCol;
        headCol->up = current;
        current = headCol;
        current1 = current1->right;
        if (current1 != DLX1->head)
        {
            Node* node = new Node(current1);
            current->right = node;
            node->left = current;
            current = node;
        }
        else
        {
            current->right = head;
            head->left = current;
        }
        headCol = current;
     }

    current1 = DLX1->head->right;
    current = head->right;
    while (current1 != DLX1->head)
    {
        current1 = current1->down;
        current = current->down;
        while (current1->rowID != -1)
        {
            Node* node = goToNode(current1->right->rowID, current1->right->colID);
            current->right = node;
            node->left = current;
            current = current->down;
            current1 = current1->down;
        }
        current = current->right;
        current1 = current1->right;
     }
}

DLX::~DLX()
{
    Node* current = head->right;
    while (current != head)
    {
        current = current->down;
        while (current->rowID != -1)
        {
            Node* node = current->down;
            delete current;
            current = node;
        }
        Node* node = current->right;
        delete current;
        current = node;
    }
    delete head;
}

void DLX::push(int* row, int r, int n)
{
    Node* current = head;
    Node* firstInRow = nullptr;
    Node* lastInRow = nullptr;
    bool first = true;
    for (int i = 0; i < n; i++)
    {
        if (row[i])
        {
            if (first)
            {
                while (current->colID != i)
                {
                    current = current->right;
                }
                Node* headCol = current;
                while (current->down != headCol)
                {
                    current = current->down;
                }
                Node* newNode = new Node;
                newNode->colID = i;
                newNode->rowID = r;
                current->down = newNode;
                newNode->up = current;
                newNode->down = headCol;
                headCol->up = newNode;
                current = headCol;
                firstInRow = newNode;
                firstInRow->left = firstInRow;
                firstInRow->right = firstInRow;
                lastInRow = newNode;
                first = false;
                headCol->count++;
            }
            else
            {
                while (current->colID != i)
                {
                    current = current->right;
                }
                Node* headCol = current;
                while (current->down != headCol)
                {
                    current = current->down;

                }
                Node* newNode = new Node;
                newNode->colID = i;
                newNode->rowID = r;
                current->down = newNode;
                newNode->up = current;
                newNode->down = headCol;
                newNode->left = lastInRow;
                lastInRow->right = newNode;
                firstInRow->left = newNode;
                newNode->right = firstInRow;
                headCol->up = newNode;
                current = headCol;
                lastInRow = newNode;
                headCol->count++;
            }
        }
    }
}

void DLX::print()
{
    Node* current = head->right;
    while (current != head)
    {
        current = current->down;
        while (current->rowID != -1)
        {
            std::cout << current->rowID << " " << current->colID << std::endl;
            current = current->down;
        }

        current = current->right;
    }
}

void DLX::cover(Node* headCol)
{
    headCol->left->right = headCol->right;
    headCol->right->left = headCol->left;
    Node* currentRow = headCol->down;
    while (currentRow != headCol)
    {
        Node* currentColumn = currentRow->right;
        while (currentColumn != currentRow)
        {
            currentColumn->down->up = currentColumn->up;
            currentColumn->up->down = currentColumn->down;
            getColumn(currentColumn)->count--;
            currentColumn = currentColumn->right;
        }
        currentRow = currentRow->down;
    }
}

void DLX::uncover(Node* headCol)
{
    Node* currentRow = headCol->up;
    while (currentRow != headCol)
    {
        Node* currentColumn = currentRow->left;
        while (currentColumn != currentRow)
        {
            currentColumn->down->up = currentColumn;
            currentColumn->up->down = currentColumn;
            getColumn(currentColumn)->count++;
            currentColumn = currentColumn->left;
        }
        currentRow = currentRow->up;
    }
    headCol->left->right = headCol;
    headCol->right->left = headCol;

}

Node* DLX::findMin()
{
    Node* headCol = head->right;
    Node* current = head->right;
    int min = current->count;
    while (current != head)
    {
        if (min > current->count)
        {
            min = current->count;
            headCol = current;
        }
        current = current->right;
    }
    return headCol;
}

Node* DLX::getColumn(Node* current)
{
    while (current->rowID != -1)
        current = current->up;
    return current;
}

Node* DLX::getNode(int r)
{
    Node* current = head;
    while (current->colID < r / 9)
    {
        current = current->right;
    }
    current = current->down;
    while ((current->rowID < r) && (current->rowID!=-1))
    {
        current = current->down;
    }
    return current;
}

Node* DLX::goToNode(int i, int j)
{
    Node* current = head;
    while (current->colID != j)
    {
        current = current->right;
    }
    while (current->rowID != i)
    {
        current = current->down;
    }
    return current;
}
