//
// Created by Illia Matviienko on 2/5/24.
//

#include "tucp.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

void copyFile(const char *sourceFilename, const char *destinationFilename) {
    FILE *sourceFile, *destinationFile;
    char ch;

    // Open the source file in read mode
    sourceFile = fopen(sourceFilename, "r");
    if (sourceFile == NULL) {
        printf("Unable to open source file %s\n", sourceFilename);
        return;
    }

    // Open the destination file in write mode
    destinationFile = fopen(destinationFilename, "w");
    if (destinationFile == NULL) {
        printf("Unable to create destination file %s\n", destinationFilename);
        fclose(sourceFile);
        return;
    }

    // Copy contents from source to destination
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destinationFile);
    }

    // Close files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully from %s to %s\n", sourceFilename, destinationFilename);
}

int main(int argc, char *argv[]) {
    char *positions[100];
    for (size_t i = 0; i < argc; i++) {
        positions[i] = argv[i];
    }


    if (positions[0] != NULL && positions[1] != NULL && positions[2]) {
        printf("1st file: %s and 2nd file: %s\n", positions[1], positions[2]);
    }
    const char *sourceFilename = positions[1];
    const char *destinationFilename = positions[2];

    copyFile(sourceFilename, destinationFilename);

    return 0;
}
