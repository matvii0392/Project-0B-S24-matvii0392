//
// Created by Illia Matviienko on 2/5/24.
//

#include "tucp.h"
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#define EMPTY NULL


//function to check whether file already exists
bool fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

//function to copy contents of one file to another
void copyFile(const char *sourceFilename, const char *destinationFilename) {
    FILE *sourceFile, *destinationFile;
    char buffer[1024];
    size_t bytesRead;

    // Open the source file in binary read mode
    sourceFile = fopen(sourceFilename, "rb");
    if (sourceFile == NULL) {
        printf("Unable to open source file %s\n", sourceFilename);
        return;
    }

    // Open the destination file in binary write mode
    destinationFile = fopen(destinationFilename, "wb");
    if (destinationFile == NULL) {
        printf("Unable to create destination file %s\n", destinationFilename);
        fclose(sourceFile);
        return;
    }

    // Copy contents from source to destination
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);
    //printf("File copied successfully from %s to %s\n", sourceFilename, destinationFilename);
}

//function to copy a file to a user-defined directory
void copyFileToDirectory(const char *sourceFilename, const char *destinationDirectory) {
    FILE *sourceFile, *destinationFile;
    char buffer[1024];
    size_t bytesRead;

    // Open the source file in binary read mode
    sourceFile = fopen(sourceFilename, "rb");
    if (sourceFile == NULL) {
        printf("Unable to open source file %s\n", sourceFilename);
        return;
    }

    // Create the destination path
    char destinationPath[256];
    snprintf(destinationPath, sizeof(destinationPath), "%s/%s", destinationDirectory, sourceFilename);

    // Open the destination file in binary write mode
    destinationFile = fopen(destinationPath, "wb");
    if (destinationFile == NULL) {
        printf("Unable to create destination file %s\n", destinationPath);
        fclose(sourceFile);
        return;
    }

    // Copy contents from source to destination
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    //printf("File copied successfully from %s to %s\n", sourceFilename, destinationPath);
}

//function to check if entry is a Directory
int isDirectory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

//function to check if entry is a File
int isFile(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}


int main(int argc, char *argv[]) {
    char *positions[100];
    FILE *filePointer;
    DIR *dir;
    struct dirent *entry;
    char cwd[1024];
    int filledPositions = 0;

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        //printf("***Current directory: %s\n", cwd);
    } else {
        perror("getcwd() ERROR");
        return 1;
    }

    for (size_t i = 0; i < argc; i++) {
        positions[i] = argv[i];
        //printf("Position %zu : %s\n", i, positions[i]);
        filledPositions++;
    }

    //printf("Filled positions: %d\n", filledPositions);
    if (filledPositions == 3) {
        const char *source = positions[1];
        const char *destination = positions[filledPositions - 1];
        char str1[1024] = "/";
        strcat(str1, positions[filledPositions - 1]);
        if (isFile(strcat(cwd, str1))) {
            if (fileExists(destination)) {
                //printf("File %s exists\n", destination);
                copyFile(source, destination);
            } else {
                //printf("File %s does not exist\n", destination);
                //printf("Creating new file %s\n", destination);
                filePointer = fopen(destination, "w");
                if (filePointer == NULL) {
                    //printf("Failed to create a file.\n");
                } else {
                    //printf("File created.\n");
                    fclose(filePointer);
                    copyFile(source, destination);
                }
            }
        }
        if (isDirectory(strcat(cwd, str1))) {
            copyFileToDirectory(source, destination);
        }
    } else if (filledPositions > 3){
        for (size_t q = 1; q < filledPositions; q++){
            const char *source = positions[q];
            const char *destination = positions[filledPositions - 1];
            char str1[1024] = "/";
            strcat(str1, positions[filledPositions - 1]);
            if (isDirectory(strcat(cwd, str1))) {
                copyFileToDirectory(source, destination);
            }
        }
    }
    return 0;
}
