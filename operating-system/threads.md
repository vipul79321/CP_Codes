[Link](https://www2.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/4_Threads.html)

### Threads | [Link](https://www.geeksforgeeks.org/thread-in-operating-system/)
* Thread is the segment of a process means a process can have multiple threads and these multiple threads are contained within a process.
* A thread have 3 states:
  * running, ready, and blocked.
* **Threads of the same process share - code, data, files, global variables and heap space.**
* **Each thread has its own register, thread counter(analog to program counters) and stack, even if they are of same process**

E.g use case of multi-threading - 
For example in a word processor, a background thread may check spelling and grammar while a foreground thread processes user input ( keystrokes ), while yet a third thread loads images from the hard drive, and a fourth does periodic automatic backups of the file being edited.

---

### Benefits of Multithreading
* **Responsiveness** - One thread may provide rapid response while other threads are blocked or slowed down doing intensive calculations.
* **Economic** -  Creating and managing threads ( and context switches between them ) is much faster than performing the same tasks for processes.
* **Resource Sharing** - By default nature of threads.
* **Scalability** - With multiple threads we can utilize mutliple-cores.

---

### Process vs Threads | [Link](https://www.javatpoint.com/process-vs-thread)

| Process | Threads |
| ------- | ------- |
| A process is an instance of a program that is being executed or processed. | Thread is a segment of a process or a lightweight process that is managed by the scheduler independently.|
| Processes are independent of each other and hence don't share a memory or other resources. | Threads are interdependent and share memory. |
| Each process is treated as a new process by the operating system. | The operating system takes all the user-level threads as a single process. |
| **If one process gets blocked by the operating system, then the other process can continue the execution.** | **If any user-level thread gets blocked, all of its peer threads also get blocked because OS takes all of them as a single process.**|
| Context switching between two processes takes much time as they are heavy compared to thread. | Context switching between the threads is fast because they are very lightweight. |
| **The data segment and code segment of each process are independent of the other.** | **Threads share data segment and code segment with their peer threads; hence are the same for other threads also.** | 
| The operating system takes more time to create or terminate a process. | Threads can be created and terminated in very little time. |
| Process has its own Process Control Block, Stack and Address Space. | Thread has Parents’ PCB, its own Thread Control Block and Stack and common Address space.|


> **NOTE** - **If any user-level thread gets blocked, all of its peer threads also get blocked because OS takes all of them as a single process**. It means all the threads which were mapped to same kernel thread as the blocked one will get blocked and they are being referred as peer here. | [StackoverFlow Explanation](https://stackoverflow.com/questions/68981493/confusion-regarding-the-blocking-of-peer-threads-when-a-user-level-thread-bloc)

---

### User Threads vs Kernel Threads | [Link](https://alldifferences.net/difference-between-user-level-and-kernel-level-thread/)

| User Level Threads | Kernel Level Threads |
| ------------------ | -------------------- |
| User-level threads are faster to create and manage. | Kernel level threads are slower to create and manage. |
| Implemented by a thread_library user level. | Operating system support directly to Kernel threads. |
|  Context switch time is less. | Context switch time is more.  |
|  Context switch requires no hardware support. |  Hardware support is needed.  |

---


### MultiThreading models | User-level threads to Kernel-level threads mapping | [Link](https://docs.oracle.com/cd/E19620-01/805-4031/6j3qv1oej/index.html)

* **Many-to-One Model** - One kernel thread per multiple user thread
  * Additionally, only one thread at a time can access the kernel, so only one schedulable entity is known to the operating system. 
  * As a result, this multithreading model provides limited concurrency and does not exploit multiprocessors.
* **One-to-One Model** - One kernel thread per user thread
  * In this implementation, each user-level thread created by the application is known to the kernel, and all threads can access the kernel at the same time. 
  * The main problem with this model is that it places a restriction on you to be careful and frugal with threads, as each additional thread adds more "weight" to the process. 
* **Many-to-Many Model** - Combination of both of the above types

---

### Thread Pools
* Creating new threads every time one is needed and then deleting it when it is done can be inefficient, and can also lead to a very large ( unlimited ) number of threads being created.
* An alternative solution is to create a number of threads when the process first starts, and put those threads into a **thread pool**.
  * Threads are allocated from the pool as needed, and returned to the pool when no longer needed.
  * When no threads are available in the pool, the process may have to wait until one becomes available.

---

### If one thread forks, is the entire process copied, or is the new process single-threaded?
* System dependant.
* If the new process execs right away, there is no need to copy all the other threads. If it doesn't, then the entire process should be copied.
* Many versions of UNIX provide multiple versions of the fork call for this purpose.

---


### When a multi-threaded process receives a signal, to what thread should that signal be delivered?
* Best choice depends on the type of signal recieved among the below four options - 
  * Deliver the signal to the thread to which the signal applies.
  * Deliver the signal to every thread in the process.
  * Deliver the signal to certain threads in the process.
  * Assign a specific thread to receive all signals in a process. 

---

### Thread Cancellation
* Threads that are no longer needed may be cancelled by another thread in one of two ways:
  * **Asynchronous Cancellation** cancels the thread immediately.
  * **Deferred Cancellation** sets a flag indicating the thread should cancel itself when it is convenient. It is then up to the cancelled thread to check this flag periodically and exit nicely when it sees the flag set.

---
