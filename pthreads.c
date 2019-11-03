/*
* Corso di Sistemi Operativi
* A.A. 2019/20
* Corso di Laurea in Scienze e Tecnologie Informatiche
* Universita' della Basilicata
* 
* docente: Ing. Domenico Daniele Bloisi, PhD
*
* domenico.bloisi@unibas.it
*
* pthreads.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int SHARED_DATA = 0;

void *f1(void *arg)
{
  SHARED_DATA = SHARED_DATA + 2;
  SHARED_DATA = SHARED_DATA * 2;
  pthread_exit(0);
} 

void *f2(void *arg)
{
  SHARED_DATA = SHARED_DATA + 3;
  SHARED_DATA = SHARED_DATA * 3;
  pthread_exit(0);
}

int main()
{
  pthread_t thread1, thread2;

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

