#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE_PARTITION 100
#define size(a) sizeof(a)/sizeof(a[0])

void generate_file(char* fileName, int nmbrsAmt) {
    srand(time(NULL));
    FILE* file = fopen(fileName, "wb");
    for (int i = 0; i < nmbrsAmt; i++) {
        int random = rand() % 100;
        fwrite(&random, sizeof(int), 1, file);
    }
    fclose(file);
}

char* generate_file_name(char* fileName, int count) {
    char* buffer = (char*) malloc(sizeof(char) * 10);
    sprintf(buffer, "%s%d", fileName, count);
    return buffer;
}

void generate_partitions(char* fileName, int amtPerFile) {
    if (amtPerFile > MAX_SIZE_PARTITION) return;
    FILE* file = fopen(fileName, "rb");

    int count = 0;
    while (!feof(file)) {
        char* destinationFileName = generate_file_name(fileName, count);
        FILE* destinationFile = fopen(destinationFileName, "wb");
        free(destinationFileName);

        for (int i = 0; i < amtPerFile; i++) {
            if (feof(file)) break;
            int out;
            fread(&out, sizeof(int), 1, file);
            fwrite(&out, sizeof(int), 1, destinationFile);
        }

        fclose(destinationFile);
        count++;
    }

    fclose(file);
}

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

int main()
{
    int numbersAmt = 35;
    int numberPerFile = 5;
    int partitionsAmount = (numbersAmt/numberPerFile) + ((numbersAmt % numberPerFile != 0) ? 1 : 0);

    //gera arquivo com numbersAmt numeros aleatorios
    generate_file("file", numbersAmt);

    //gera partições com numberPerFile numeros
    generate_partitions("file", numbersPerFile);

    //ordena todos os arquivos
    for (int i = 0; i < partitionsAmount; i++)
        sort_file(generate_file_name("file", i), 5);
    return 0;
}
