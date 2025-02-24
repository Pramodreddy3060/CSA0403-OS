#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "shared_memory.txt"  // Simulated shared memory

void writer() {
    FILE *file = fopen(FILE_NAME, "w");  // Open file for writing
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char data[100];
    printf("Writer: Enter data to write into shared memory: ");
    fgets(data, sizeof(data), stdin);  // Get user input

    fprintf(file, "%s", data);  // Write to file
    fclose(file);
    printf("Writer: Data written successfully!\n");
}

void reader() {
    FILE *file = fopen(FILE_NAME, "r");  // Open file for reading
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char data[100];
    fgets(data, sizeof(data), file);  // Read from file
    fclose(file);

    printf("Reader: Data read from shared memory: %s\n", data);
}

int main() {
    int choice;
    
    printf("Choose Mode: \n1. Writer\n2. Reader\nEnter choice: ");
    scanf("%d", &choice);
    getchar();  // Clear input buffer

    if (choice == 1) {
        writer();  // Call writer function
    } else if (choice == 2) {
        reader();  // Call reader function
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
