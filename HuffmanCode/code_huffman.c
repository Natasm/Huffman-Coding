#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Node.h"
#include "PriorityQueue.h"
#include "LinkedList.h"
#include "File.h"

char tabel[256][100];
int k = 0;

LinkedList count_freq(FILE* input, LinkedList ll){
    int ch = getc(input);
    while(ch != EOF){
        ll = updateLinkedList(ll, ch, 1);
        ch = getc(input);
    }
    return ll;
}

PriorityQueue build_priority_queue(LinkedList ll){
    PriorityQueue pq = newPriorityQueue(sizeLinkedList(ll));
    while(ll != NULL){
        Node node = newNode(getKeyLinkedList(ll), getContentLinkedList(ll), NULL, NULL);
        insertPriorityQueue(pq, getFrequence(node),node);
        ll = getNextNodeLinkedList(ll);
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
        printf("%c - %s\n", getKeyNode(x), string);
        strcpy(tabel[getKeyNode(x)], string);
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
       char* code_binary = tabel[ch];

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

    int sizeBuffer = ftell(file_input) / 10;
    char buffer[sizeBuffer];

    rewind(file_input);

    fread(&buffer, sizeof(char), sizeBuffer, file_input);

    rewind(file_input);

    LinkedList ll = newLinkedList();
    ll = count_freq(file_input, ll);

    rewind(file_input);

    PriorityQueue pq = build_priority_queue(ll);

    Node parent = build_trie(pq);

    deletePriorityQueue(pq);
    deleteLinkedList(ll);

    char a[10000];
    //print_code(parent, a, false);
    build_code(parent, a, false);

    create_or_open_file(output);
    writeTrie(parent);
    writeByte(sizeBuffer);
    writeText(file_input);
    close_file();

    fclose(file_input);
}

int main(){
    huffman_compress("text_arithmetic_big.txt", "text_arithmetic_big.dat");
    return 0;
}



