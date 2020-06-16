#include <stdlib.h>
#include "NodeFreq.h"

struct nodefreq {
   char ch;
   int frequence;
};

NodeFreq newNodeFreq(char c, int freq){
    NodeFreq createNode = (NodeFreq) malloc(sizeof(struct nodefreq));
    createNode->ch = c;
    createNode->frequence = freq;
    return createNode;
}

char getKeyNodeFreq(NodeFreq n){
    return n->ch;
}

int getContentNodeFreq(NodeFreq n){
    return n->frequence;
}

NodeFreq addContentNodeFreq(NodeFreq n, int add){
    n->frequence = n->frequence + 1;
    return n;
}
