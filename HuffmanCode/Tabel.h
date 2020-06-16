#ifndef TABEL_H_INCLUDED
#define TABEL_H_INCLUDED

typedef struct tabel* Tabel;

Tabel newTabel(char c, char* content);

char getKeyTabel(Tabel t);

char* getContentTabel(Tabel t);

#endif // TABEL_H_INCLUDED
