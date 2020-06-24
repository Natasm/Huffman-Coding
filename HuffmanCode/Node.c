#include <stdlib.h>
#include "Node.h"

struct node {
   char ch;
   int freq;
   Node left, right;
};

Node newNode(char c, int freq, Node left, Node right){
    Node createNode = (Node) malloc(sizeof(struct node));
    createNode->ch = c;
    createNode->freq = freq;
    createNode->left = left;
    createNode->right = right;
    return createNode;
}

Node newNodeJoin(Node left, Node right){
    Node createNode = (Node) malloc(sizeof(struct node));
    createNode->ch = '+';

    if(left != NULL && right != NULL) createNode->freq = left->freq + right->freq;
    else if (left != NULL) createNode->freq = left->freq;
    else createNode->freq = right->freq;

    createNode->left = left;
    createNode->right = right;
    return createNode;
}

int isLeaf(Node root){
    if(root->left == NULL && root->right == NULL) return 1;
    else return 0;
}

int getFrequence(Node root){
    if(isLeaf(root)) return root->freq;
    else return root->left->freq + root->right->freq;
}

char getKeyNode(Node root){
    return root->ch;
}

Node getLeftNode(Node root){
    return root->left;
}

Node getRightNode(Node root){
    return root->right;
}




