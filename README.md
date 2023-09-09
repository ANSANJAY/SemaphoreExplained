# SemaphoreExplained



# 🚦 Custom Semaphore Implementation in C

Semaphores are synchronization primitives used to control access to shared resources in concurrent programming. They can be visualized as a counter representing the number of times a resource (or a set of resources) can be accessed. This counter can be increased (signaled) or decreased (waited on). When the counter is zero, threads attempting to "wait" on the semaphore will block until the semaphore is signaled by another thread.

This repository provides a custom implementation of semaphores using POSIX threads, mutex locks, and condition variables. Dive in to explore the exciting world of concurrency in C!

## 📂 Overview

The project consists of three main files:

1. `sema.h` - A header file that contains the declarations of the custom semaphore structure and its associated functions.
2. `sema.c` - This source file provides the implementation for the custom semaphore functions declared in `sema.h`.
3. `semaphore_hello_world.c` - A sample application that demonstrates the use of POSIX threads and the custom semaphore implementation. It provides a basic "hello world" setup to understand the functionality of the semaphore.

## ✨ Features

- A simplified semaphore structure using the pthread library.
- Clear APIs for semaphore initialization, wait (acquire), post (release), destroy, and fetching the current value.
- Alternate notations for semaphore operations like `P` & `V`, `UP` & `DOWN`.
- A demo application to showcase the use of the custom semaphore.

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



