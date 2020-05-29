#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE* pont_arq;
static int buffer = 0;
static int n = 0;

void create_or_open_file(char* path){
    pont_arq = fopen(path, "a");
}

void clearBuffer(){
   if(n == 0) return;

   if(n > 0) buffer <<= (8 - n);
   fwrite(&buffer,sizeof(int),1,pont_arq);

   buffer = 0;
   n = 0;
}

void writeBit(bool bit){
    buffer <<= 1;
    if(bit) buffer |= 1;

    n++;
    if(n == 8) clearBuffer();
}

void writeByte(int x){
     if(n == 0){
        fwrite(&buffer,sizeof(int),1,pont_arq);
        return;
     }
     for(int i = 0; i < 8; i++){
         bool bit = ((x >> (8 - i - 1)) & 1) == 1;
         writeBit(bit);
     }
}

void writeChar(char c){
    writeByte(c);
}

void close_file(){
    if(pont_arq != NULL) fclose(pont_arq);
}
