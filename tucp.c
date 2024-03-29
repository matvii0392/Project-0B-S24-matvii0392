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
void copyFile(const char *source, const char *destination) {
    FILE *sourceFile, *destinationFile;
    size_t bytesRead;
    char temp[1024];

    // Open the source file in binary read mode
    sourceFile = fopen(source, "rb");
    if (sourceFile == NULL) {
        printf("Error: Unable to open source file %s, file in directory created instead.\n", source);
        char dest1[1024];
        snprintf(dest1, sizeof(dest1), "%s/%s", destination, source);
        // Open the destination file in binary write mode
        destinationFile = fopen(dest1, "wb");
        fclose(destinationFile);
        return;
    }
    // Open the destination file in binary write mode
    destinationFile = fopen(destination, "wb");
    if (destinationFile == NULL) {
        printf("Error: Unable to create destination file %s\n", destination);
        fclose(sourceFile);
        return;
    }
    // Copy contents from source to destination
    while ((bytesRead = fread(temp, 1, sizeof(temp), sourceFile)) > 0) {
        fwrite(temp, 1, bytesRead, destinationFile);
    }
    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);
    //printf("File copied successfully from %s to %s\n", sourceFilename, destinationFilename);
}

//function to copy a file to a user-defined directory
void cpFileToDirectory(const char *source, const char *destination) {
    FILE *sourceFile, *destinationFile;
    size_t bytesRead;
    char temp[1024];
    // Open the source file in binary read mode
    sourceFile = fopen(source, "rb");
    if (sourceFile == NULL) {
        printf("Error: Unable to open source file %s, file in directory created instead.\n", source);
        char dest1[1024];
        snprintf(dest1, sizeof(dest1), "%s/%s", destination, source);
        // Open the destination file in binary write mode
        destinationFile = fopen(dest1, "wb");
        fclose(destinationFile);
        return;
    }
    // Create the destination path
    char dest[1024];
    snprintf(dest, sizeof(dest), "%s/%s", destination, source);
    // Open the destination file in binary write mode
    destinationFile = fopen(dest, "wb");
    if (destinationFile == NULL) {
        printf("Error: Unable to create destination file %s\n", dest);
        fclose(sourceFile);
        return;
    }
    // Copy contents from source to destination
    while ((bytesRead = fread(temp, 1, sizeof(temp), sourceFile)) > 0) {
        fwrite(temp, 1, bytesRead, destinationFile);
    }
    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);
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
    //DIR *dir;
    //struct dirent *entry;
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
        filledPositions++;
    }

    if (filledPositions == 3) {
        const char *source = positions[1];
        const char *destination = positions[filledPositions - 1];
        char str1[1024] = "/";
        strcat(str1, positions[filledPositions - 1]);
        if (isFile(strcat(cwd, str1))) {
            if (fileExists(destination)) {
                //printf("Copying file %s\n", destination);
                copyFile(source, destination);
            }
        }
        if (isDirectory(strcat(cwd, str1))) {
            cpFileToDirectory(source, destination);
        } else {
            filePointer = fopen(destination, "w");
            if (filePointer == NULL) {
                printf("Error: Failed to create the file.\n");
            } else {
                copyFile(source, destination);
                // Close the file after creating it
                fclose(filePointer);
            }
        }
    } else if (filledPositions > 3) {
        for (size_t q = 1; q < filledPositions - 1; q++) {
            const char *source = positions[q];
            const char *destination = positions[filledPositions - 1];
            char str1[1024] = "/";
            strcat(str1, positions[filledPositions - 1]);
            if (1) {
                cpFileToDirectory(source, destination);
            }
        }
        return 0;
    }
}
