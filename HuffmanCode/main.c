#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include "code_huffman.h"

int main(){
    clock_t t;
    DIR *dir;
    struct dirent *ent;
    char dir_name[] = "C:/Users/natandemorais/Desktop/files/";
    char path_files[10][100];
    char path_files_encode[10][100];

    if ((dir = opendir (dir_name)) != NULL) {
        ent = readdir(dir);
        ent = readdir(dir);

        int i = 0;
        while ((ent = readdir (dir)) != NULL) {
            strcpy(path_files[i], dir_name);
            strcat(path_files[i], ent->d_name);

            strcpy(path_files_encode[i], dir_name);
            strcat(path_files_encode[i], ent->d_name);
            strcat(path_files_encode[i], ".dat");

            t = clock();
            huffman_compress(path_files[i], path_files_encode[i]);
            t = clock() - t;

            double time = ((double)t)/(CLOCKS_PER_SEC);
            printf("%s\nTime: %f\n\n", path_files[i], time);

            i++;
        }
        closedir (dir);
    }

    return 0;
}
