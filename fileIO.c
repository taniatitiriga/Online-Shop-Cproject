#include "fileIO.h"

void readFromCSV(const char* filePath) {
    FILE* file = openFile(filePath, "r");

    if (file == NULL)
        return;

    char header[200];
    char data[200];

    char* col_data;
    char* next_col;

    fgets(header, 200, file);

    while (!feof(file)) {
        fgets(data, 200, file);
        col_data = strtok(data, ",");

        while (col_data != NULL) {
            printf("I have read %s\n", col_data);
            col_data = strtok(NULL, ",");
        }
    }

    fclose(file);
}

void writeToFile(const char* filePath, const char* message) {
    if (message == NULL || strlen(message) == 0)
        return;

    FILE* file = openFile(filePath, "a");

    if (file == NULL)
        return;

    fprintf(file, "%s\n", message);

    fclose(file);
}

FILE* openFile(const char* filePath, const char* mode) {
    if (filePath == NULL || strlen(filePath) == 0 ||
        mode == NULL || strlen(mode) == 0)
        return NULL;

    FILE* file = fopen(filePath, mode);

    return file;
}

