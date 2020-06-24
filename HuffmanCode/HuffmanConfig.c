#include <stdlib.h>
#include "HuffmanConfig.h"
#include "NodeFreq.h"
#include "Tabel.h"

#define SIZE_ALPHABETIC 256

struct codehuffman{
    NodeFreq nodesfreq[SIZE_ALPHABETIC];
    Tabel tabel[SIZE_ALPHABETIC];
};

CodeHuffman newCodeHuffman(){
    CodeHuffman ch = (CodeHuffman) malloc(sizeof(struct codehuffman));
    for(int i = 0; i < SIZE_ALPHABETIC; i++){
        ch->nodesfreq[i] = NULL;
        ch->tabel[i] = NULL;
    }
    return ch;
}

int getNodeFreqValid(CodeHuffman ch){
    int soma = 0;
    for(int i = 0; i < SIZE_ALPHABETIC; i++) if(ch->nodesfreq[i] != NULL) soma++;
    return soma;
}

void insertNodeFreq(CodeHuffman ch, int c){
    if(ch->nodesfreq[c] == NULL) {
        ch->nodesfreq[c] = newNodeFreq(c, 1);
    }
    else ch->nodesfreq[c] = addContentNodeFreq(ch->nodesfreq[c], 1);
}

NodeFreq getNodeFreq(CodeHuffman ch, int i) { return ch->nodesfreq[i]; }

void insertTabel(CodeHuffman ch, int key, char* content){
    if(ch->tabel[key] == NULL) ch->tabel[key] = newTabel(key, content);
}

Tabel getTabel(CodeHuffman ch, int i) { return ch->tabel[i]; }
