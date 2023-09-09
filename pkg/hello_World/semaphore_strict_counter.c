

/*
 * Compile instructions:
 * gcc -g -c semaphore_strict_counter.c -o semaphore_strict_counter.o
 * gcc -g semaphore_strict_counter.o -o semaphore_strict_counter.exe -lpthread
 * Run : ./semaphore_strict_counter.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // For POSIX threads operations
#include <unistd.h>  // For pause() and sleep() functions
#include <errno.h>   // To retrieve error numbers
#include "sema.h"    // Custom semaphore implementation header

// Two semaphores to synchronize even and odd threads
sema_t sema0_1, sema0_2;

// Two threads: one for even numbers and one for odd numbers
pthread_t even_thread, odd_thread;

/*
 * The function for even numbers thread.
 * It waits for its turn, prints an even number, then signals the odd thread to proceed.
 */
static void *
thread_fn_callback_even(void *arg) {
    int i;
    for ( i = 2 ; i <= 15; i+=2) {
        sema_wait(&sema0_2);
        printf("%d\n", i);
        sema_post(&sema0_1);
    }
    return NULL;
}

/*
 * The function for odd numbers thread.
 * It prints an odd number, then signals the even thread to proceed and waits for its next turn.
 */
static void *
thread_fn_callback_odd(void *arg) {
    int i;
    for ( i = 1 ; i <= 15; i+=2) {
        printf("%d\n", i);
        sema_post(&sema0_2);
        sema_wait(&sema0_1);
    }
    return NULL;
}

/*
 * A utility function to create a thread.
 */
void
thread_create(pthread_t *thread_handle, void *(*thread_fn)(void *)) {
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int rc = pthread_create(thread_handle, 
            &attr, 
            thread_fn,
            NULL);
    
    if(rc != 0) {
        printf("Error occurred, thread could not be created, errno = %d\n", rc);
        exit(0);
    }
}

/*
 * Main function initializes the semaphores, creates the threads, and cleans up afterward.
 */
int
main(int argc, char **argv){
    // Initialize the semaphores
    sema_init(&sema0_1, 0);
    sema_init(&sema0_2, 0);

    // Create the even and odd threads
    thread_create(&even_thread, thread_fn_callback_odd);
    thread_create(&odd_thread, thread_fn_callback_even);

    // Wait for the threads to complete
    pthread_join(even_thread, NULL);
    pthread_join(odd_thread, NULL);

    // Clean up the semaphores
    sema_destroy(&sema0_1);
    sema_destroy(&sema0_2);

    return 0;
}
