#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <stdio.h>

// Define the structure that functions as the linked list:
typedef struct Node_t {
  struct Node_t* left;
  struct Node_t* right;
  char value;
} Node;

// Declare management methods:
Node* newNode();
void delNodeTree(Node*);
Node* moveLeft(Node*);
Node* moveRight(Node*);
void printNode(FILE* dest, const Node*);
int readNode(FILE* src, Node*);
void incrementNode(Node*);
void decrementNode(Node*);

#endif // NODE_H_INCLUDED
