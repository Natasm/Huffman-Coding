#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Node.h"
#include "PriorityQueue.h"
#include "NodeFreq.h"
#include "Tabel.h"
#include "File.h"
#include "HuffmanConfig.h"

#define SIZE_ALPHABETIC 256

void count_freq(CodeHuffman ch, FILE* input){
    int c = getc(input);

    while(c != EOF){
        insertNodeFreq(ch, c);
        c = getc(input);
    }
}

PriorityQueue build_priority_queue(CodeHuffman ch){
    PriorityQueue pq = newPriorityQueue(getNodeFreqValid(ch));
    for(int i = 0; i < SIZE_ALPHABETIC; i++){
        NodeFreq nodefreq = getNodeFreq(ch, i);
        if(nodefreq != NULL){
            Node node = newNode(getKeyNodeFreq(nodefreq), getContentNodeFreq(nodefreq), NULL, NULL);
            insertPriorityQueue(pq, getContentNodeFreq(nodefreq), node);
        }
    }
    return pq;
}

Node build_trie(PriorityQueue pq){
    while(1){
        Node node1 = removeMinPriorityQueue(pq);
        Node node2 = removeMinPriorityQueue(pq);

        Node parent = newNodeJoin(node1, node2);

        if(isEmptyPriorityQueue(pq)) return parent;

        insertPriorityQueue(pq, getFrequence(parent), parent);
    }
}

char* concatChar(char* c1, char* c2){
    int i, j;
    for(i = 0; c1[i] != '\0'; i++);
    for(j = 0; c2[j] != '\0'; j++, i++){
        c1[i] = c2[j];
    }
    c1[i] = '\0';
    return c1;
}

void build_code(Node x, char* string, int goToParent, CodeHuffman ch){
    if(isLeaf(x)){
        char key = getKeyNode(x);
        insertTabel(ch, key, string);

        if(goToParent) string[(strlen(string) - 1) - 1] = '\0';
        else string[strlen(string) - 1] = '\0';
        return;
    }
    build_code(getLeftNode(x), concatChar(string, "0"), false, ch);
    build_code(getRightNode(x), concatChar(string, "1"), true, ch);

    if(goToParent) string[(strlen(string) - 1)] = '\0';
}

void writeTrie(Node x, FileStream fs){
     if(isLeaf(x)){
        writeBit(fs, true);
        writeChar(fs, getKeyNode(x));
        return;
     }
     writeBit(fs, false);
     writeTrie(getLeftNode(x), fs);
     writeTrie(getRightNode(x), fs);
}

void writeText(FILE* input, FileStream fs, CodeHuffman ch){
   int c =  getc(input);

    while(c != EOF){
       char* code_binary = getContentTabel(getTabel(ch, c));

       for(int j = 0; j < strlen(code_binary); j++){
           if(code_binary[j] == '0') writeBit(fs, false);
           else if(code_binary[j] == '1') writeBit(fs, true);
       }
       c = getc(input);
   }
}

void print_code(Node x, char* string, int goToParent){
    if(isLeaf(x)){
        printf("%c - %s\n", getKeyNode(x), string);
        if(goToParent) string[(strlen(string) - 1) - 1] = '\0';
        else string[strlen(string) - 1] = '\0';
        return;
    }
    print_code(getLeftNode(x), concatChar(string, "0"), false);
    print_code(getRightNode(x), concatChar(string, "1"), true);

    if(goToParent) string[(strlen(string) - 1)] = '\0';
}

void huffman_compress(char* input, char* output){
    FILE* file_input = fopen(input, "rt");
    fseek(file_input, 0L, SEEK_END);
    int sizeBuffer = ftell(file_input);

    rewind(file_input);

    CodeHuffman ch = newCodeHuffman();

    count_freq(ch, file_input);

    PriorityQueue pq = build_priority_queue(ch);

    Node parent = build_trie(pq);

    deletePriorityQueue(pq);

    char a[100];
    a[0] = '\0';
    build_code(parent, a, false, ch);

    FileStream fs = create_or_open_file(output, "wb");

    writeTrie(parent, fs);
    writeInt(fs, getNodeFreqValid(ch));

    rewind(file_input);
    writeText(file_input, fs, ch);

    close_file(fs, "wb");
    fclose(file_input);
}
