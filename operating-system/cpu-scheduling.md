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

**NOTE** - The process scheduler schedules only the kernel threads.

---


 
