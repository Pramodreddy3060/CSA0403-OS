#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_mutex_t mutex;          // Mutex for synchronizing output
sem_t forks[N];                 // Semaphores for forks

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Pick up left and right forks
        sem_wait(&forks[id]);                 // Pick up left fork
        sem_wait(&forks[(id + 1) % N]);       // Pick up right fork

        pthread_mutex_lock(&mutex);
        printf("Philosopher %d is eating...\n", id);
        pthread_mutex_unlock(&mutex);

        sleep(2); // Simulating eating time

        // Put down the forks
        sem_post(&forks[id]);                 // Release left fork
        sem_post(&forks[(id + 1) % N]);       // Release right fork

        printf("Philosopher %d finished eating and is thinking again...\n", id);
        sleep(1);
    }
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for threads to finish (will not happen in infinite loop)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores and mutex
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
