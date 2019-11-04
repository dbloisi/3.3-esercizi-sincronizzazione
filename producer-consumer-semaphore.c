#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

char buffer;
int quit_program = 0;

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void* produce(void *arg) {
    int i;
    for(i=0; i < 5; i++) {
        sem_wait(&empty);
        buffer = 'a' + i;
        printf("producing '%c'\n", buffer);
        sem_post(&full);
    }
    sem_wait(&empty);
    quit_program = 1;
    sem_post(&full);
    return NULL;
}

void* consume(void *arg) {
    char current_char = '\x0'; //NUL character
    while(1) {
        sem_wait(&full);
        if(quit_program != 0) {
           return NULL;
        }
        current_char = buffer;
        printf("consuming '%c'\n", current_char);
        sem_post(&empty);
    }
}

int main() {
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 1);
    pthread_t th1, th2;
    pthread_create(&th1, NULL, &produce, NULL);
    pthread_create(&th2, NULL, &consume, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}

