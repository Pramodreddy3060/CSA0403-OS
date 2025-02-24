#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Buffer capacity
#define NUM_ITEMS 10   // Total items to produce/consume

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0, out = 0;  // Buffer index for producer/consumer

sem_t empty, full;    // Semaphores
pthread_mutex_t mutex; // Mutex for mutual exclusion

// Producer function
void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100;  // Produce a random item

        sem_wait(&empty); // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Lock critical section

        buffer[in] = item; // Place item in buffer
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock
        sem_post(&full); // Signal consumer
        sleep(1);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full); // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Lock critical section

        int item = buffer[out]; // Consume item from buffer
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock
        sem_post(&empty); // Signal producer
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prodThread, consThread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Start with all slots empty
    sem_init(&full, 0, 0); // No filled slots initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
