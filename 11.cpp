#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>  // Required for Sleep()

void *print_numbers(void *arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Thread 1 - Number: %d\n", i);
        Sleep(500);  // Pause for 500ms
    }
    return NULL;
}

void *print_characters(void *arg) {
    for (char c = 'A'; c <= 'E'; c++) {
        printf("Thread 2 - Character: %c\n", c);
        Sleep(500);  // Pause for 500ms
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create two threads
    pthread_create(&t1, NULL, print_numbers, NULL);
    pthread_create(&t2, NULL, print_characters, NULL);

    // Wait for threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main Thread: Execution Completed!\n");
    return 0;
}
