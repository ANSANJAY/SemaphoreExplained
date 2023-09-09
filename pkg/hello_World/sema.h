// Standard file inclusion guards to prevent double inclusion
#ifndef __SEMA__
#define __SEMA__

// Forward declaration of semaphore type
typedef struct sema_ sema_t;

// Definition of the semaphore structure
struct sema_ {
    int permit_counter;          // Counter for available permits in the semaphore
    pthread_cond_t cv;           // Condition variable used for blocking/waking up threads
    pthread_mutex_t mutex;       // Mutex to protect access to the permit_counter
};

// Prototype for function to allocate and return a new semaphore object
sema_t *
sema_get_new_semaphore();

// Prototype for function to initialize a semaphore with a given count
void
sema_init(sema_t *sema, int count);

// Prototype for function allowing a thread to wait/acquire a semaphore
void
sema_wait(sema_t *sema);

// Prototype for function to signal/post to a semaphore, possibly waking up a waiting thread
void
sema_post(sema_t *sema);

// Prototype for function to destroy a semaphore and free its resources
void
sema_destroy(sema_t *sema);

// Prototype for function to retrieve the current value of a semaphore's permit counter
int
sema_getvalue(sema_t *sema);

// Define macros for alternate names for semaphore wait and post operations
// P & V notation is a classical representation for wait and signal operations on semaphores
#define P(sema) sema_wait(sema)
#define V(sema)	sema_post(sema)

// Define macros for another set of alternate names for semaphore wait and post operations
// Some literature might use 'UP' and 'DOWN' to denote wait and signal respectively
#define UP(sema)	sema_wait(sema)
#define DOWN(sema)	sema_post(sema)

#endif /* __SEMA__ */
