#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "message_queue.txt"

void sender() {
    FILE *file = fopen(FILE_NAME, "w");  // Open file for writing (simulate queue)
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char message[100];
    printf("Sender: Enter message to send: ");
    fgets(message, sizeof(message), stdin);  // Get user input

    fprintf(file, "%s", message);  // Write message to file
    fclose(file);

    printf("Sender: Message sent!\n");
}

void receiver() {
    FILE *file = fopen(FILE_NAME, "r");  // Open file for reading (simulate queue)
    if (file == NULL) {
        perror("Error opening file (maybe no message yet)");
        exit(1);
    }

    char message[100];
    fgets(message, sizeof(message), file);  // Read message from file
    fclose(file);

    printf("Receiver: Message received: %s\n", message);
}

int main() {
    int choice;

    printf("Choose Mode: \n1. Sender\n2. Receiver\nEnter choice: ");
    scanf("%d", &choice);
    getchar();  // Clear input buffer

    if (choice == 1) {
        sender();  // Call sender function
    } else if (choice == 2) {
        receiver();  // Call receiver function
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
