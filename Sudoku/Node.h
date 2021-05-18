#ifndef NODE_H
#define NODE_H

struct Node
{
    int rowID;
    int colID;
    int count;
    Node* left;
    Node* right;
    Node* up;
    Node* down;
    Node() { left = nullptr; right = nullptr; up = nullptr; down = nullptr; rowID = -1; colID = -1; count = -1; };
    Node(Node* &node1) { left = nullptr; right = nullptr; up = nullptr; down = nullptr; rowID = node1->rowID; colID = node1->colID; count = node1->count; };
    ~Node() {left = nullptr; right = nullptr; up = nullptr; down = nullptr; }
};

#endif // NODE_H
