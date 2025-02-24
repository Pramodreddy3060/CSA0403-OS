#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3  // Number of threads

pthread_mutex_t lock;  // Mutex lock
int shared_resource = 0;  // Shared variable

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    printf("Thread %d: Waiting to access shared resource...\n", thread_id);
    
    pthread_mutex_lock(&lock);  // Lock mutex (enter critical section)
    printf("Thread %d: Accessing shared resource.\n", thread_id);
    
    shared_resource++;  // Modify shared resource
    printf("Thread %d: Updated shared_resource = %d\n", thread_id, shared_resource);

    sleep(1);  // Simulate some processing time
    printf("Thread %d: Releasing lock.\n", thread_id);
    
    pthread_mutex_unlock(&lock);  // Unlock mutex (exit critical section)

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the mutex lock
    pthread_mutex_init(&lock, NULL);

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex lock
    pthread_mutex_destroy(&lock);

    printf("Final shared_resource value: %d\n", shared_resource);

    return 0;
}
