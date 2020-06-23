#ifndef HUFFMANCONFIG_H_INCLUDED
#define HUFFMANCONFIG_H_INCLUDED
#include "NodeFreq.h"
#include "Tabel.h"

typedef struct codehuffman* CodeHuffman;

CodeHuffman newCodeHuffman();

int getNodeFreqValid(CodeHuffman ch);

void insertNodeFreq(CodeHuffman ch, char c);

NodeFreq getNodeFreq(CodeHuffman ch, int i);

void insertTabel(CodeHuffman ch, char key, char* content);

Tabel getTabel(CodeHuffman ch, int i);

#endif // HUFFMANCONFIG_H_INCLUDED
