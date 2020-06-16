#include <stdlib.h>
#include "Tabel.h"

struct tabel {
   char ch;
   char* content;
};

Tabel newTabel(char c, char* content){
    Tabel createNode = (Tabel) malloc(sizeof(struct tabel));
    createNode->content = malloc(sizeof(strlen(content)));

    createNode->ch = c;
    strcpy(createNode->content, content);

    return createNode;
}

char getKeyTabel(Tabel t){
    return t->ch;
}

char* getContentTabel(Tabel t){
    return t->content;
}
