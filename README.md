
# 🚦 Custom Semaphore Implementation in C

Semaphores are synchronization primitives used to control access to shared resources in concurrent programming. They can be visualized as a counter representing the number of times a resource (or a set of resources) can be accessed. This counter can be increased (signaled) or decreased (waited on). When the counter is zero, threads attempting to "wait" on the semaphore will block until the semaphore is signaled by another thread.

This repository provides a custom implementation of semaphores using POSIX threads, mutex locks, and condition variables. Dive in to explore the exciting world of concurrency in C!

```

   +------------------------------------+
   |        Custom Semaphore             |
   +------------------------------------+
   |                                    |
   |  +----------------------+          |
   |  |      Permit Counter |----+      |
   |  +----------------------+    |      |
   |  +----------------------+    | Decrement/Increment |
   |  |        Mutex        |<---+      |
   |  +----------------------+          |
   |  +----------------------+          |
   |  |    Condition Var    |<---+      |
   |  +----------------------+    | Signal/Wait |
   |                                    |
   +------------------------------------+
               ^     ^
               |     | Interaction
               |     |
+-------------+ +-----------+ +-----------+
|   Thread A  | | Thread B | | Thread C  |
+-------------+ +-----------+ +-----------+


```

# Semaphore Implementation and Demonstration 🚦

 In computer science, semaphores are a powerful synchronization primitive used for controlling access to shared resources in concurrent systems.

This repository provides an implementation of semaphores and also showcases their use in two distinct scenarios: a basic hello-world context and a strict counter demonstration.

## Contents 📖
1. [sema.h and sema.c](#sema)
2. [semaphore_hello_world.c](#hello-world)
3. [semaphore_strict_counter.c](#strict-counter)

<a name="sema"></a>

### sema.h and sema.c
These files provide a custom implementation of semaphores using POSIX threads. The semaphores are defined using a structure that maintains a counter and employs condition variables and mutexes for synchronization.

- **sema_get_new_semaphore()**: Allocates memory for a new semaphore.
- **sema_init(sema_t *sema, int count)**: Initializes the semaphore with the given count.
- **sema_wait(sema_t *sema)**: Decrements the semaphore, and if the value becomes negative, the calling thread blocks.
- **sema_post(sema_t *sema)**: Increments the semaphore, and if the value is 0 or negative, it unblocks a waiting thread.
- **sema_destroy(sema_t *sema)**: Destroys the semaphore, freeing associated resources.
- **sema_getvalue(sema_t *sema)**: Returns the current value of the semaphore.

<a name="hello-world"></a>

### semaphore_hello_world.c
A demonstration of how threads can coordinate using semaphores to access a critical section.

The program uses POSIX threads and semaphores to print which thread is entering, executing in, and exiting from the critical section.

<a name="strict-counter"></a>

### semaphore_strict_counter.c
A demonstration of how semaphores can be used to enforce a strict order of execution between threads. 

In this program, there are two threads: one for printing odd numbers and the other for printing even numbers. Using the semaphores, these threads are synchronized in such a way that they print numbers in a strict increasing order from 1 to 15.

**Key Functions**:
- **thread_fn_callback_even()**: The function assigned to the even number thread. It waits for its turn, prints an even number, and then signals the odd thread to proceed.
- **thread_fn_callback_odd()**: The function assigned to the odd number thread. It prints an odd number, signals the even thread to proceed, and then waits for its next turn.

## Getting Started 🚀

## 🔧 Compilation

To compile the semaphore library:

```bash
gcc -g -c sema.c -o sema.o
```

To compile the sample application:

```bash
gcc -g -c semaphore_hello_world.c -o semaphore_hello_world.o
gcc -g semaphore_hello_world.o sema.o -o semaphore_hello_world.exe -lpthread
```

To run the demo application:

```bash
./semaphore_hello_world.exe
```

To compile the semaphore_strict_counter.c

```bash
gcc -g -c semaphore_strict_counter.c -o semaphore_strict_counter.o
gcc -g semaphore_strict_counter.o -o semaphore_strict_counter.exe -lpthread
./semaphore_strict_counter.exe
```

## ✨ Features

- A simplified semaphore structure using the pthread library.
- Clear APIs for semaphore initialization, wait (acquire), post (release), destroy, and fetching the current value.
- Alternate notations for semaphore operations like `P` & `V`, `UP` & `DOWN`.
- A demo application to showcase the use of the custom semaphore.



