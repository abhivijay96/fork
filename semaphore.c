// TO Demonstrate usage of semaphores in C

#include <stdio.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <stdlib.h>

// concepts used pthreads, semaphore
// global semaphore shared by all threads

sem_t semaphore;

void* child(void *id)
{
    int* temp = (int *) id;
    printf("Thread %d waiting for semaphore\n", *temp);
    sem_wait(&semaphore);
    // critical section here
    sleep(5);
    printf("Thread %d accessing the resource\n", *temp);
    //free(temp);
    sem_post(&semaphore);
}

void main()
{
     printf("Demonstrating usage of semaphores\n");
     printf("Let's assume we have a resource, enter the number of threads that can access it simultaneously\n");

     int res_size;
     scanf("%d", &res_size);

     int size;
     printf("Enter the number of threads that you want to spawn\n");
     scanf("%d", &size);

     sem_init(&semaphore, 0, res_size);
     int i;
     pthread_t threads[size];

     for(i = 0; i < size; i++)
     {
        int* k = (int *) malloc(sizeof(int));
        *k = i;
        pthread_create(&threads[i], NULL, child, (void *)k); 
     }

     for(i = 0; i < size; i++)
     {
         pthread_join(threads[i], NULL);
     }
}