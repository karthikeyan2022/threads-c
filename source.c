#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_CHILDREN 2

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

    printf ("Checking...\n");

    for (i=0; i<shared->end; i++) {
        if (shared->array[i] != 1) errors++;
    }

    printf ("%d errors.\n", errors);
}

int main()
{
    printf("hello world \n");

    int i;
    pthread_t child[NUM_CHILDREN];

    Shared* shared = make_shared(100);

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