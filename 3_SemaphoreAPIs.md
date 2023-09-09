# SemaphoreExplained

##  Notes on Semaphores 📝

### Introduction to Semaphore APIs 🚦
- To work with semaphores, you must include the appropriate header file.
- There are five key APIs to use semaphores:
  1. `sam_t` - to declare a semaphore variable.
  2. Initialization function.
  3. `sam_wait` - blocks the thread if semaphore is 0.
  4. `sam_post` - increases the semaphore count.
  5. Destruction function.

### Understanding Semaphore Initialization 🚧
- Before performing operations on a semaphore, it must be initialized.
  - 1st argument: Address of the semaphore variable.
  - 2nd argument:
    - 0: For synchronization of threads.
    - Non-zero: For synchronization of processes.
  - 3rd argument: Initial count/permit number for semaphore. (Positive value).

### How Semaphores Work ⚙️
- Semaphores can be visualized as controlling access to a "critical section" of code.
  - A critical section is the part of the code where you want to control access.
  - The semaphore is initialized with a value, `N`. 
    - Example: If `N = 3`, at most 3 threads can concurrently execute the critical section.
- Execution sequence:
  1. Threads approach the critical section.
  2. They encounter `sam_wait`.
  3. If they can decrease the counter without it going negative, they can proceed.
  4. Once inside the critical section, when they finish, they call `sam_post` which increases the count.
  5. If the count was negative (meaning threads were waiting), one thread is unblocked.

### Difference between Semaphores and Mutexes 🔐
- For `N = 1`, semaphores act like a mutex.
  - Mutex: Allows only one thread to execute the critical section.
- Key distinction:
  - Mutex: Must be unlocked by the same thread that locked it.
  - Semaphore: Any thread can invoke `sam_post` (unblock).

### Program Using Semaphores 💻
- Details to be covered.

---

## Interview Questions on Semaphores 🤔

### Q1: What is a Semaphore?
**Answer:** A semaphore is a synchronization primitive used to control access to a shared resource by multiple threads or processes. It operates based on a counter which dictates how many threads can access the resource.

### Q2: How do you initialize a semaphore?
**Answer:** You initialize a semaphore by providing three arguments: the address of the semaphore variable, a second argument that is 0 for thread synchronization (or non-zero for process synchronization), and a third positive value indicating the initial count or permit number.

### Q3: How do `sam_wait` and `sam_post` APIs work in semaphores?
**Answer:** `sam_wait` tries to decrease the semaphore's counter. If after decreasing, the counter is not negative, the thread proceeds. If it becomes negative, the thread is blocked. `sam_post` increases the counter and if any threads were waiting (counter was negative), one thread is unblocked.

### Q4: What is the difference between a mutex and a semaphore?
**Answer:** While both are synchronization primitives, a mutex allows only one thread to execute the critical section and must be unlocked by the same thread that locked it. A binary semaphore, on the other hand, can have its post operation invoked by any thread, not just the one that called the wait operation.

### Q5: Can you explain the significance of the initial count or permit number in a semaphore?
**Answer:** The initial count or permit number in a semaphore dictates how many threads can concurrently access the controlled critical section without having to wait. If initialized with `N = 3`, at most 3 threads can execute the critical section concurrently.

--- 

I hope these notes and questions help with your revision for interviews! Best of luck! 🍀👍
