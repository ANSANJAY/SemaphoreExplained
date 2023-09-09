// Including necessary libraries for the program
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>     // Library for POSIX threads
#include <unistd.h>      // For sleep() function
#include <errno.h>       // For error handling
#include <semaphore.h>   // For semaphores

// Declaration of semaphore
sem_t sem;

// Declaration of thread array
pthread_t threads[5];

// Define the number of semaphore permits
#define PERMIT_COUNT 2

// Thread callback function
// This function is executed by each thread
static void *
thread_fn_callback(void *arg) {

    // Retrieve the thread's name from the argument
    char *thread_name = (char *)arg;

    // Notify entering into critical section
    printf("%s entering into C.S\n", thread_name);

    // Begin of critical section
    // The thread tries to acquire the semaphore
    sem_wait(&sem);

    // Notify that thread has entered critical section
    printf("%s entered into C.S\n", thread_name);
    
    // Simulating some processing in critical section using a loop
    int i;
    for ( i = 0 ; i < 5; i++) {
        printf("%s executing in C.S\n", thread_name);
        sleep(1);  // Sleep for a second
    }

    // Notify exiting from critical section
    printf("%s exiting from C.S\n", thread_name);

    // Release the semaphore
    sem_post(&sem);

    // End of critical section
    // Notify that thread has completely exited from critical section
    printf("%s exit from C.S\n", thread_name);
}

// Function to create a new thread
void
thread_create(pthread_t *thread_handle, void *arg) {

    // Create a new thread and assign the thread_fn_callback function to it
    int rc = pthread_create(thread_handle, 
                            NULL, 
                            thread_fn_callback,
                            arg);
    // Check if thread creation was successful
    if(rc != 0) {
        printf("Error occurred, thread could not be created, errno = %d\n", rc);
        exit(0);
    }
}

int
main(int argc, char **argv){

    // Initialize semaphore with defined permit count
    sem_init(&sem, 0, PERMIT_COUNT);

    // Create 5 threads
    thread_create(&threads[0], "thread0");
    thread_create(&threads[1], "thread1");
    thread_create(&threads[2], "thread2");
    thread_create(&threads[3], "thread3");
    thread_create(&threads[4], "thread4");

    // Join threads to main, ensuring all threads complete
    int i;
    for ( i = 0; i < 5; i++ ) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore once done
    sem_destroy(&sem);

    return 0;   // End of main function
}
