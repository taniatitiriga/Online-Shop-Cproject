#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <string.h>

void readFromCSV(const char* filePath);
void writeToFile(const char* filePath, const char* message);
FILE* openFile(const char* filePath, const char* mode);

#endif