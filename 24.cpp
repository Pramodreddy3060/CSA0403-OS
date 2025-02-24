#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "example.txt"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // 1?? Create/Open the file
    fd = open(FILENAME, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating/opening file");
        return 1;
    }
    printf("File '%s' created/opened successfully.\n", FILENAME);

    // 2?? Write data to the file
    const char *text = "Hello, this is a file management demo!";
    bytes_written = write(fd, text, sizeof(text));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    printf("Data written to file successfully.\n");

    // Close the file after writing
    close(fd);

    // 3?? Reopen the file for reading
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }

    // 4?? Read data from the file
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }
    buffer[bytes_read] = '\0';  // Null-terminate string
    printf("Data read from file: %s\n", buffer);

    // Close file after reading
    close(fd);

    // 5?? Rename the file
    if (rename(FILENAME, "renamed_example.txt") == 0) {
        printf("File renamed successfully to 'renamed_example.txt'.\n");
    } else {
        perror("Error renaming file");
    }

    // 6?? Delete the file
    if (remove("renamed_example.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("Error deleting file");
    }

    return 0;
}
