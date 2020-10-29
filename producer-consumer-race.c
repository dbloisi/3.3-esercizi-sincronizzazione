/*
* Corso di Sistemi Operativi
* Corso di Laurea in Scienze e Tecnologie Informatiche
* Universita' della Basilicata
* 
* docente: Domenico D. Bloisi
* domenico.bloisi@unibas.it
*
* **This code is provided without any warranty about its
* usability. It is for educational purposes and should
* be regarded as such.**
*
* producer-consumer-race.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

char buffer;
int quit_program = 0;

void* produce(void *arg) {
    int i;
    for(i=0; i < 5; i++) {
        buffer = 'a' + i;
        printf("producing '%c'\n", buffer);
        sleep(3);
    }
    quit_program = 1;
    return NULL;
}

void* consume(void *arg) {
    char current_char = '\x0'; //NUL character
    while (quit_program == 0) {
        sleep(1);
        current_char = buffer;
        printf("consuming '%c'\n", current_char);
    }
    return NULL;
}

int main() {
    pthread_t th1, th2;
    pthread_create(&th1, NULL, &produce, NULL);
    pthread_create(&th2, NULL, &consume, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}

