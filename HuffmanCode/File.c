#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "File.h"

struct filestream{
    FILE* pont_arq;
    int buffer;
    int n;
};

FileStream create_or_open_file(char* path, char* mode){
    FileStream fs = malloc(sizeof(struct filestream));

    fs->buffer = 0;
    fs->n = 0;
    fs->pont_arq = fopen(path, mode);

    return fs;
}

//Start functions of write of file binary

void clearBuffer(FileStream fs){
   if(fs->n == 0) return;

   if(fs->n > 0) fs->buffer <<= (8 - fs->n);
   fwrite(&fs->buffer, sizeof(char),1,fs->pont_arq);

   fs->buffer = 0;
   fs->n = 0;
}

void writeBit(FileStream fs, bool bit){
    fs->buffer <<= 1;
    if(bit) fs->buffer |= 1;

    fs->n++;
    if(fs->n == 8) clearBuffer(fs);
}

void writeByte(FileStream fs, int x){
     if(fs->n == 0){
        fwrite(&x,sizeof(char),1, fs->pont_arq);
        return;
     }

     for(int i = 0; i < 8; i++){
         bool bit = ((x >> (8 - i - 1)) & 1) == 1;
         writeBit(fs, bit);
     }
}

void writeInt(FileStream fs, int x){
    writeByte(fs, (x >> 24) & 0xff);
    writeByte(fs, (x >> 16) & 0xff);
    writeByte(fs, (x >> 8) & 0xff);
    writeByte(fs, (x >> 0) & 0xff);
}

void writeChar(FileStream fs, char c){
    writeByte(fs, c);
}

//End functions of write of file binary

//Start functions of read of file binary

void fillBuffer(FileStream fs){
    fs->buffer = fgetc(fs->pont_arq);
    fs->n = 8;
}

int readChar(FileStream fs){
    if(fs->n == 8){
        int x = fs->buffer;
        fillBuffer(fs);
        return x;
    }

    int x = fs->buffer;
    x <<= (8 - fs->n);
    int cache = fs->n;

    fillBuffer(fs);

    fs->n = cache;
    x |= (fs->buffer >> fs->n);

    return x;
}

int readInt(FileStream fs){
    int x = 0;
    for(int i = 0; i < 4; i++){
        int c = readChar(fs);
        x <<= 8;
        x |= c;
    }
    return x;
}

bool readBit(FileStream fs){
    fs->n--;
    bool x = ((fs->buffer >> fs->n) & 1) == 1;

    if(fs->n == 0) fillBuffer(fs);

    return x;
}

//Close file

void close_file(FileStream fs, char* mode){
    if(strcmp(mode, "wb") == 0) clearBuffer(fs);
    if(fs->pont_arq != NULL) fclose(fs->pont_arq);
}
