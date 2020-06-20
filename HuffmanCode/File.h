#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include <stdbool.h>

typedef struct filestream* FileStream;

FileStream create_or_open_file(char* path, char* mode);

void writeBit(FileStream fs, bool bit);

void writeChar(FileStream fs, char c);

void writeInt(FileStream fs, int i);

int readChar(FileStream fs);

int readInt(FileStream fs);

bool readBit(FileStream fs);

void close_file(FileStream fs, char* mode);

#endif // FILE_H_INCLUDED
