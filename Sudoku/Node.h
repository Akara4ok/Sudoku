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
};

#endif // NODE_H
