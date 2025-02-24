#include <stdio.h>
#include <string.h>

#define MAX_USERS 5        // Maximum number of users (directories)
#define MAX_FILES 10       // Maximum files per user

typedef struct {
    char name[50];         // User name (directory name)
    char files[MAX_FILES][50]; // Files within the user directory
    int fileCount;         // Number of files in this user's directory
} UserDirectory;

UserDirectory users[MAX_USERS]; // Array of user directories
int userCount = 0; // Total users created

// Function to create a new user (directory)
void createUser() {
    if (userCount >= MAX_USERS) {
        printf("Error: Maximum user directories reached!\n");
        return;
    }

    printf("Enter new user (directory) name: ");
    scanf("%s", users[userCount].name);
    users[userCount].fileCount = 0; // Initialize with no files
    userCount++;

    printf("User directory '%s' created successfully.\n", users[userCount - 1].name);
}

// Function to create a file under a user directory
void createFile() {
    char userName[50], fileName[50];
    printf("Enter user name (directory) to create a file in: ");
    scanf("%s", userName);

    // Find the user directory
    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, userName) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Error: User directory not found!\n");
        return;
    }

    if (users[userIndex].fileCount >= MAX_FILES) {
        printf("Error: Maximum files limit reached for this directory!\n");
        return;
    }

    printf("Enter file name to create: ");
    scanf("%s", fileName);

    // Check if file already exists
    for (int i = 0; i < users[userIndex].fileCount; i++) {
        if (strcmp(users[userIndex].files[i], fileName) == 0) {
            printf("Error: File already exists!\n");
            return;
        }
    }

    strcpy(users[userIndex].files[users[userIndex].fileCount], fileName);
    users[userIndex].fileCount++;
    printf("File '%s' created successfully in user directory '%s'.\n", fileName, userName);
}

// Function to delete a file from a user directory
void deleteFile() {
    char userName[50], fileName[50];
    printf("Enter user name (directory) to delete file from: ");
    scanf("%s", userName);

    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, userName) == 0) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Error: User directory not found!\n");
        return;
    }

    printf("Enter file name to delete: ");
    scanf("%s", fileName);

    for (int i = 0; i < users[userIndex].fileCount; i++) {
        if (strcmp(users[userIndex].files[i], fileName) == 0) {
            // Shift remaining files left
            for (int j = i; j < users[userIndex].fileCount - 1; j++) {
                strcpy(users[userIndex].files[j], users[userIndex].files[j + 1]);
            }
            users[userIndex].fileCount--;
            printf("File '%s' deleted from user directory '%s'.\n", fileName, userName);
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

    for (int i = 0; i < userCount; i++) {
        for (int j = 0; j < users[i].fileCount; j++) {
            if (strcmp(users[i].files[j], fileName) == 0) {
                printf("File '%s' found in user directory '%s'.\n", fileName, users[i].name);
                return;
            }
        }
    }

    printf("Error: File not found in any directory!\n");
}

// Function to display all users and their files
void displayDirectories() {
    if (userCount == 0) {
        printf("No user directories found!\n");
        return;
    }

    printf("\nUser Directories and Files:\n");
    for (int i = 0; i < userCount; i++) {
        printf("User Directory: %s\n", users[i].name);
        if (users[i].fileCount == 0) {
            printf("  No files\n");
        } else {
            for (int j = 0; j < users[i].fileCount; j++) {
                printf("  - %s\n", users[i].files[j]);
            }
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nTwo-Level Directory System\n");
        printf("1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display All Directories\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createUser(); break;
            case 2: createFile(); break;
            case 3: deleteFile(); break;
            case 4: searchFile(); break;
            case 5: displayDirectories(); break;
            case 6: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}
