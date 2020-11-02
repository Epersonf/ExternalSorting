#include <time.h>
#include "file_stack.h"
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



void merge_sorted_partitions(char* fileName, int start, int end) {
    FILE* file = fopen(fileName, "wb");

    int filesAmount = end - start;
    TFileStack** files = (TFileStack**) malloc(sizeof(TFileStack) * filesAmount);

    for (int i = 0; i < filesAmount; i++) {
        files[i] = create_file_stack(generate_file_name(fileName, start + i));
    }

    int isAllEof = 0;
    while (1) {
        int index = 0;
        int record = 0;
        isAllEof = 1;
        int first = 1;
        for (int i = 0; i < filesAmount; i++) {
            int num = read_file_stack(files[i]);

            if (is_eof(files[i]))
                continue;

            isAllEof = 0;
            if (first || num < record) {
                record = num;
                index = i;
                first = 0;
            }
        }

        if (isAllEof)
            break;

        next_file_stack(files[index]);
        printf("Selected %d\n", record);
        fwrite(&record, sizeof(int), 1, file);
    }

    for (int i = 0; i < filesAmount; i++) {
        free_file_stack(files[i]);
    }

    fclose(file);
}
