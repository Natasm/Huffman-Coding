#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Node.h"
#include "PriorityQueue.h"
#include "LinkedList.h"
#include "File.h"

LinkedList count_freq(char* buffer, int size_buffer, LinkedList ll){
    for(int i = 0; i < size_buffer; i++) ll = updateLinkedList(ll, buffer[i], 1);
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

LinkedList tabel;

char aux[1000][1000];
int k = 0;

void build_code(Node x, char* string, int goToParent){
    if(isLeaf(x)){
        strcpy(aux[k], string);
        tabel = insertBeginningLinkedList(tabel, getKeyNode(x), aux[k]);
        k++;
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

void writeText(char* buffer, LinkedList tabel){
   for(int i = 0; i < strlen(buffer); i++){
       char c = buffer[i];
       char* code_binary = getContentLinkedList(searchLinkedList(tabel, c));
       for(int j = 0; j < strlen(code_binary); j++){
           if(code_binary[j] == '0') writeBit(false);
           else if(code_binary[j] == '1') writeBit(true);
       }
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

void huffman_compress(char* buffer){
    LinkedList ll = newLinkedList();
    ll = count_freq(buffer, strlen(buffer), ll);

    PriorityQueue pq = build_priority_queue(ll);

    Node parent = build_trie(pq);

    //toString(ll);
    //Node x = getRightNode(getLeftNode(getLeftNode(parent)));
    //if(x != NULL) printf("%c - %d\n", getKeyNode(x), getFrequence(x));
    char a[1000];
    //toString(ll);
    //print_code(parent, a, false);
    build_code(parent, a, false);
    toString(tabel);

    //printf("-> %c", getKeyLinkedList(getNextNodeLinkedList(tabel)));
    //toString(tabel);

    create_or_open_file("test_huffman.dat");
    writeTrie(parent);
    writeByte(strlen(buffer));
    writeText(buffer, tabel);
    close_file();
}

int main(){
    FILE* file = fopen("text_arithmetic_big.txt", "rt");
    fseek(file, 0L, SEEK_END);
    int sizeBuffer = ftell(file);
    char buffer[sizeBuffer];
    rewind(file);

    fread(&buffer, sizeof(char), sizeBuffer, file);
    close_file();

    huffman_compress(buffer);
    return 0;
}



