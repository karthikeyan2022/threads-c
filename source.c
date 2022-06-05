/*
An example of multithreaded, synchronized program in C.

Mutual exclusion

Command to build:
gcc -g -O2 -o source source.c -lpthread

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_CHILDREN 2
#define DEFAULT_COUNT_SIZE 10000  // 10^4

void perror_exit(char* s)
{
    perror(s); exit(-1);
}

void *check_malloc(int size)
{
    void* p = malloc(size);
    if(p == NULL) perror_exit("malloc failed");
    return p;
}

typedef sem_t Semaphore;

Semaphore* make_semaphore(int n)
{
    Semaphore* sem = check_malloc(sizeof(Semaphore));
    int ret = sem_init(sem, 0, n);
    if(ret == -1) perror_exit("sem init failed");
    return sem;
}

int sem_signal(Semaphore* sem)
{
    return sem_post(sem);
}

typedef struct {
    int counter;
    int end;
    int *array;
} Shared;

Shared* make_shared(int end)
{
    int i;
    // create a shared object; This is shared by two children threads
    Shared* shared = check_malloc(sizeof(Shared));

    shared->counter = 0;
    shared->end = end;

    shared->array = check_malloc(shared->end * sizeof(int));

    for(i = 0; i < shared->end; i++)
    {
        shared->array[i] = 0;
    }

    return shared;
}

pthread_t make_thread(void* (*entry)(void *), Shared* shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create(&thread, NULL, entry, (void*) shared);

    if(ret != 0) perror_exit ("pthread creation failed");

    return thread;
}

void join_thread(pthread_t thread)
{
    int ret = pthread_join(thread, NULL);
    if(ret == -1) perror_exit ("pthread join failed");
}

void child_code(Shared* shared)
{
    printf("starting child at counter %d\n", shared->counter);

    while(1)
    {
        if(shared->counter >= shared->end)
            return;

        // in proper synchronization, the value in array idx will exactly be 1
        shared->array[shared->counter]++;
        shared->counter++;

        if(shared->counter % 10000 == 0)
            printf("%d\n", shared->counter);
    }
}

void* entry (void* arg)
{
    Shared* shared = (Shared*)arg;
    child_code(shared);
    printf("child done.\n");
    pthread_exit (NULL);
}

void check_array(Shared* shared)
{
    int i, errors = 0;

    printf ("Checking... ");

    for (i=0; i<shared->end; i++) {
        if (shared->array[i] != 1) errors++;
    }

    printf ("%d Errors found!\n", errors);
}

int main(int argc, char* argv[])
{
    int i;
    int num_count = DEFAULT_COUNT_SIZE;
    pthread_t child[NUM_CHILDREN];

    if(argc >=2)
        num_count = (int)strtol(argv[1], NULL, 10);

    printf("The threads counts up to %d value.\n", num_count);
   
    Shared* shared = make_shared(num_count);

    for(i = 0; i < NUM_CHILDREN; i++)
    {
        child[i] = make_thread(entry, shared);
    }

    printf("Join thread started... \n");

    for(i = 0; i < NUM_CHILDREN; i++)
    {
        join_thread(child[i]);
    }

    check_array(shared);

    return 0;
}