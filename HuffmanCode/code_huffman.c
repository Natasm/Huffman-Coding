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

void build_code(Node x, int i){
    if(isLeaf(x)){
        tabel = insertBeginningLinkedList(tabel, getKeyNode(x), i);
        return;
    }
    build_code(getLeftNode(x), i*10 + 0);
    build_code(getRightNode(x), i*10 + 1);
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

void writeText(char* buffer){
   for(int i = 0; i < strlen(buffer); i++){
       char c = buffer[i];
       char code_binary[1000];
       itoa(getContentLinkedList(searchLinkedList(tabel, c)), code_binary, 10);
       for(int j = 0; j < strlen(code_binary); j++){
           if(code_binary[j] == '0') writeBit(false);
           else if(code_binary[j] == '1') writeBit(true);
       }
   }
}

void huffman_compress(char* buffer){
    LinkedList ll = newLinkedList();
    ll = count_freq(buffer, strlen(buffer), ll);

    PriorityQueue pq = build_priority_queue(ll);

    Node parent = build_trie(pq);

    build_code(parent, 0);

    create_or_open_file("teste_huffman.dat");
    writeTrie(parent);
    writeByte(strlen(buffer));
    writeText(buffer);
    close_file();
}

int main(){
    char buffer[] = "aabcddd";
    huffman_compress(buffer);
}



