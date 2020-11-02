#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE_PARTITION 100
#define size(a) sizeof(a)/sizeof(a[0])

int* read_file(char* fileName) {
    FILE* file = fopen(fileName, "rb");

    int* toReturn = (int*) calloc(MAX_SIZE_PARTITION, sizeof(int));

    int count = 0;
    while (!feof(file)) {
        int value;
        fread(&value, sizeof(int), 1, file);
        toReturn[count] = value;
        count++;
    }

    fclose(file);
    return toReturn;
}

void sort(int* vec, int size) {
    for (int i = 1; i < size; i++) {
        if (&vec[i] == NULL) break;
        if (vec[i - 1] <= vec[i]) continue;
        int buffer = vec[i - 1];
        vec[i - 1] = vec[i];
        vec[i] = buffer;
        i -= 2;
        if (i < 0) i = 0;
    }
}

void store_into_file(char* fileName, int* vec, int len) {
    FILE* file = fopen(fileName, "wb");
    for (int i = 0; i < len; i++) {
        fwrite(&vec[i], sizeof(int), 1, file);
    }
    fclose(file);
}

void sort_file(char* fileName, int amtPerFile) {
    int* vec = read_file(fileName);
    sort(vec, amtPerFile);
    store_into_file(fileName, vec, amtPerFile);
    free(vec);
}
