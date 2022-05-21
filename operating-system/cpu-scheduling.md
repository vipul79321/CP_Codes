[Link](https://www2.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/6_CPU_Scheduling.html)

### Some definitions
* **Non-preemptive** - Once a process starts running it keeps running, until it either voluntarily blocks or until it finishes.
* **Preemptive** - Process preemption possible. Reasons could be time quantum expired, higher priority process arriving.
* **Dispatcher** - The dispatcher is the module that gives control of the CPU to the process selected by the scheduler. This function involves:
  * Switching context.
  * Switching to user mode.
  * Jumping to the proper location in the newly loaded program.
* **Dispatch Latency** - Time taken by dispatcher.
* **Arrival Time** - The time at which process enters the ready state
* **Burst Time** - Time required by process to get executed on CPU
* **Turnaround Time** - Time taken by process to get completed since its arrival.
* **Waiting Time** - Turnaround Time - Burst Time
* **Response Time** - Time taken by process to get the CPU first time since its arrival

---

### Scheduling Algorithms
* Non - Preemptive - 
  * **FCFS(First Come First Serve)** - Faces convoy effect
  * **Shortest Job First Scheduling** - Problems with SJF are - 
    * We cannot know job duration in advance.
    * One approximation is that we predict, job duration by computing exponential average of duration of recent processes
* Preemptive - 
  * **Shortest Remaining Time First** - Also known as preemptive version of SJF 
  * **Priority Scheduling** - May face the problem of **starvation of low priority processes**. To solve that use concept of **aging** -  increasing priority with wait time.
  * **Round Robin Scheduling** - 
    * If the process finishes its burst before the time quantum timer expires, then it is swapped out of the CPU just like the normal FCFS algorithm.
    * If the timer goes off first, then the process is swapped out of the CPU and moved to the back end of the ready queue. 
  * **Multilevel Queue Scheduling** - 
    * When processes can be readily categorized, then multiple separate queues can be established, each implementing whatever scheduling algorithm is most appropriate for that type of job, and/or with different parametric adjustments. 
    * Scheduling must also be done between queues
  * **Multilevel Feedback Queue** -  
    * Similar to Multilevel Queue, but here jobs can switch queues( one reason could be due to aging)

---

> **Note** - The process scheduler schedules only the kernel threads.

---

### Thread Scheduling
* **Contention scope** refers to the scope in which threads compete for the use of physical CPUs.
* **Process Contention Scope, PCS**, occurs, when competition occurs between threads that are part of the same process. 
  * It happens on system implementing Many-to-One and Many-to-Many model.
* **System Contention Scope, SCS**, involves the system scheduler scheduling kernel threads to run on one or more CPUs. 
  * System implementing one-to-one mapping only uses SCS
* PCS scheduling is done by programmer by assigning priority to threads with help of thread libraries 

---

### Multiple Processor Scheduling
* Approaches to MultiProcessor Scheduling
  * **Asymmetric Multiprocessing** - one processor is the master, controlling all activities and running all kernel code, while the other runs only user code.
  * **Symmetric Multiprocessing** - each processor schedules its own jobs, either from a common ready queue or from separate ready queues for each processor.
* **Processor Affinity** - 
  * Processors contain cache memory, which speeds up repeated accesses to the same memory locations.
  * If a process were to switch from one processor to another each time it got a time slice, the data in the cache ( for that process ) would have to be invalidated and re-loaded from main memory, thereby obviating the benefit of the cache.
  * **Soft Affinity** - when the system attempts to keep processes on the same processor but makes no guarantees.
  * **Hard Affinity** - in which a process specifies that it is not to be moved between processors.  
* **Load Balancing** - Balancing can be achieved through one of the below methods - 
  * **Push migration** involves a separate process that runs periodically, ( e.g. every 200 milliseconds ), and moves processes from heavily loaded processors onto less loaded ones.
  * **Pull migration** involves idle processors taking processes from the ready queues of other processors. 


> **NOTE** -  One needs to be careful, while balancing load, as time saved in balancing load, may be lost in building cache for that process in the new processor

---

### Real-Time CPU Scheduling
* **Soft real-time** systems have degraded performance if their timing needs cannot be met. Example: streaming video.
* **Hard real-time** systems have total failure if their timing needs cannot be met. Examples: Assembly line robotics, automobile air-bag deployment.
* Various Scheduling Algorithm | See in yellow pages for more details - 
  * **Priority Based Scheduling**
  * **Rate-Monotonic Scheduling**
  * **Earliest Deadline First Scheduling**
