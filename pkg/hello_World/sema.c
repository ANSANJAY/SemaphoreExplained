// Include the necessary header files
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>
#include "sema.h"   // Custom header for semaphore definitions

// Function to allocate and return a new semaphore object
sema_t *
sema_get_new_semaphore() {

    // Allocate memory for the semaphore and return the pointer
    sema_t *sema = calloc(1, sizeof(sema_t));
    return sema;
}

// Initialize the semaphore with given permits
void
sema_init(sema_t *sema, int permit_counter) {

    // Set the initial value of permit counter
    sema->permit_counter = permit_counter;

    // Initialize the condition variable associated with the semaphore
    pthread_cond_init(&sema->cv, NULL);

    // Initialize the mutex lock associated with the semaphore
    pthread_mutex_init(&sema->mutex, NULL);
}

// Function for a thread to wait/acquire a semaphore
void
sema_wait(sema_t *sema) {

    // Lock the mutex to ensure atomic operation on semaphore value
    pthread_mutex_lock(&sema->mutex);

    // Decrement the semaphore value
    sema->permit_counter--;

    // If the value goes below 0, the thread should wait on the condition variable
    if (sema->permit_counter < 0) {
        pthread_cond_wait(&sema->cv, &sema->mutex);
    }

    // Release the mutex lock
    pthread_mutex_unlock(&sema->mutex);
}

// Function to signal/post to a semaphore, possibly waking up a waiting thread
void
sema_post(sema_t *sema) {

    // This variable checks if any thread is currently waiting on the semaphore
    bool any_thread_waiting;

    // Lock the mutex for atomic operation on semaphore value
    pthread_mutex_lock(&sema->mutex);

    // Determine if any thread is waiting (i.e., semaphore value is negative)
    any_thread_waiting = sema->permit_counter < 0 ? true : false;

    // Increment the semaphore value
    sema->permit_counter++;

    // If there's a thread waiting, signal the condition variable to wake one up
    if (any_thread_waiting) {
        pthread_cond_signal(&sema->cv);
    }

    // Release the mutex lock
    pthread_mutex_unlock(&sema->mutex);
}

// Destroy the semaphore and associated resources
void
sema_destroy(sema_t *sema) {

    // Reset the permit counter
    sema->permit_counter = 0;

    // Release any held mutex lock (this step is generally not recommended 
    // as destroying a locked mutex results in undefined behavior, but it's
    // included here as part of the given code)
    pthread_mutex_unlock(&sema->mutex);

    // Destroy the condition variable
    pthread_cond_destroy(&sema->cv);  

    // Destroy the mutex lock
    pthread_mutex_destroy(&sema->mutex);
}

// Function to get the current value of the semaphore
int
sema_getvalue(sema_t *sema) {
	return sema->permit_counter;
}
