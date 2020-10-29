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
* mutex-pthreads-sleep.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

int SHARED_DATA = 0;

void *f1(void *arg)
{
  sleep(5);
  pthread_mutex_lock(&mutex); 
  SHARED_DATA = SHARED_DATA + 2;
  SHARED_DATA = SHARED_DATA * 2;
  pthread_mutex_unlock(&mutex);
  pthread_exit(0);
} 

void *f2(void *arg)
{
  pthread_mutex_lock(&mutex); 
  SHARED_DATA = SHARED_DATA + 3;
  SHARED_DATA = SHARED_DATA * 3;
  pthread_mutex_unlock(&mutex);
  pthread_exit(0);
}

int main()
{
  pthread_t thread1, thread2;

  pthread_mutex_init(&mutex, NULL);

  if(pthread_create(&thread1, NULL, f1, NULL) < 0)
  {
      printf("errore creazione thread 1\n");
      exit(1);
  }
  
  if(pthread_create(&thread2, NULL, f2, NULL) < 0)
  {
      printf("errore creazione thread 2\n");
      exit(1);
  }  
  
  pthread_join (thread1, NULL);
  pthread_join (thread2, NULL);
  printf("SHARED_DATA: %d\n", SHARED_DATA);
}

