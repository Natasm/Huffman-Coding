#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Node.h"
#include "PriorityQueue.h"
#include "LinkedList.h"
#include "NodeFreq.h"
#include "Tabel.h"
#include "File.h"

#define SIZE_ALPHABETIC 256

NodeFreq nodesfreq[SIZE_ALPHABETIC];
int nodesfreqValid = 0;

Tabel tabel[SIZE_ALPHABETIC];

void count_freq(FILE* input){
    int ch = getc(input);

    while(ch != EOF){
        if(nodesfreq[ch] == NULL) {
                nodesfreq[ch] = newNodeFreq(ch, 1);
                nodesfreqValid++;
        }
        else nodesfreq[ch] = addContentNodeFreq(nodesfreq[ch], 1);

        ch = getc(input);
    }
}

PriorityQueue build_priority_queue(){
    PriorityQueue pq = newPriorityQueue(nodesfreqValid);
    for(int i = 0; i < SIZE_ALPHABETIC; i++){
        if(nodesfreq[i] != NULL){
            Node node = newNode(getKeyNode(nodesfreq[i]), getContentNodeFreq(nodesfreq[i]), NULL, NULL);
            insertPriorityQueue(pq, getContentNodeFreq(nodesfreq[i]), node);
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

void build_code(Node x, char* string, int goToParent){
    if(isLeaf(x)){
        char key = getKeyNode(x);
        if(tabel[key] == NULL) tabel[key] = newTabel(key, string);
        if(goToParent) string[(strlen(string) - 1) - 1] = '\0';
        else string[strlen(string) - 1] = '\0';
        return;
    }
    build_code(getLeftNode(x), concatChar(string, "0"), false);
    build_code(getRightNode(x), concatChar(string, "1"), true);

    if(goToParent) string[(strlen(string) - 1)] = '\0';
}

void writeTrie(Node x){
     if(isLeaf(x)){
        writeBit(true);
        writeChar(getKeyNode(x));
        return;
     }
     writeBit(false);
     writeTrie(getLeftNode(x));
     writeTrie(getRightNode(x));
}

void writeText(FILE* input){
   int ch =  getc(input);

    while(ch != EOF){
       char* code_binary = getContentTabel(tabel[ch]);

       for(int j = 0; j < strlen(code_binary); j++){
           if(code_binary[j] == '0') writeBit(false);
           else if(code_binary[j] == '1') writeBit(true);
       }
       ch = getc(input);
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

    count_freq(file_input);

    PriorityQueue pq = build_priority_queue();

    Node parent = build_trie(pq);

    deletePriorityQueue(pq);

    char a[100];
    build_code(parent, a, false);

    create_or_open_file(output);

    writeTrie(parent);
    writeInt(nodesfreqValid);

    rewind(file_input);
    writeText(file_input);

    close_file();
    fclose(file_input);
}

int main(){
    huffman_compress("The_Bible.txt", "text_arithmetic_big.dat");
    return 0;
}



