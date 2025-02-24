#include <stdio.h>
#include <string.h>

#define MAX_FILES 100  // Maximum number of files allowed

char files[MAX_FILES][50];  // Array to store file names
int fileCount = 0;  // Counter for number of files

// Function to create a new file
void createFile() {
    if (fileCount >= MAX_FILES) {
        printf("Error: Directory is full!\n");
        return;
    }

    char fileName[50];
    printf("Enter file name to create: ");
    scanf("%s", fileName);

    // Check if the file already exists
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i], fileName) == 0) {
            printf("Error: File already exists!\n");
            return;
        }
    }

    strcpy(files[fileCount], fileName);
    fileCount++;
    printf("File '%s' created successfully.\n", fileName);
}

// Function to delete a file
void deleteFile() {
    char fileName[50];
    printf("Enter file name to delete: ");
    scanf("%s", fileName);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i], fileName) == 0) {
            // Shift remaining files left to fill the gap
            for (int j = i; j < fileCount - 1; j++) {
                strcpy(files[j], files[j + 1]);
            }
            fileCount--;
            printf("File '%s' deleted successfully.\n", fileName);
            return;
        }
    }

    printf("Error: File not found!\n");
}

// Function to search for a file
void searchFile() {
    char fileName[50];
    printf("Enter file name to search: ");
    scanf("%s", fileName);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(files[i], fileName) == 0) {
            printf("File '%s' found at position %d.\n", fileName, i + 1);
            return;
        }
    }

    printf("Error: File not found!\n");
}

// Function to display all files
void displayFiles() {
    if (fileCount == 0) {
        printf("Directory is empty!\n");
        return;
    }

    printf("Files in the directory:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%d. %s\n", i + 1, files[i]);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nSingle-Level Directory System\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display All Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: searchFile(); break;
            case 4: displayFiles(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}
