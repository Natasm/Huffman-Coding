#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

typedef struct node* Node;

Node newNode(char c, int freq, Node left, Node right);
Node newNodeJoin(Node left, Node right);
int isLeaf(Node root);
int getFrequence(Node root);
char getKeyNode(Node root);
Node getLeftNode(Node root);
Node getRightNode(Node root);

#endif // NODE_H_INCLUDED
