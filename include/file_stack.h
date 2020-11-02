typedef struct file_stack {
    char* name;
    FILE* file;
    int position;
} TFileStack;

TFileStack* create_file_stack(char* fileName) {
    TFileStack* toReturn = (TFileStack*) malloc(sizeof(TFileStack));
    toReturn->name = fileName;
    toReturn->file = fopen(fileName, "rb");
    toReturn->position = 0;
    return toReturn;
}

int read_file_stack(TFileStack* target) {
    fseek(target->file, target->position * sizeof(int), SEEK_SET);
    if (feof(target->file)) return 0;
    int a;
    fread(&a, sizeof(int), 1, target->file);
    return a;
}

void next_file_stack(TFileStack* target) {
    target->position++;
}

int is_eof(TFileStack* target) {
    return feof(target->file);
}

void free_file_stack(TFileStack* target) {
    fclose(target->file);
    free(target);
}
