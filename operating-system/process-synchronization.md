[Link](https://www2.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/5_Synchronization.html)

### Process Synchronization | [Link](https://www.interviewbit.com/operating-system-interview-questions/#process-synchronization)
* Process synchronization is basically a way to coordinate processes that use shared resources or data.
* It aims at maintaining data consistency with the help of mutual exclusion in critical section

### Critical Section | [Link](https://www.careerride.com/Operating-System-Interview-Questions.aspx)
* It is a section of code which can be executed only by one process at a time to maintain data consistency.

### Critical Section Problem 
In Cooperative Processes - 
* Only one process in the group can be allowed to execute in their critical section at any one time. 
* If one process is already executing their critical section and another process wishes to do so, then the second process must be made to wait until the first process has completed their critical section work.

### Features of Solution to Critical Section Problem 
* **Mutual Exclusion** - Only one process at a time can be executing in their critical section.
* **Bounded Waiting** - There exists a limit as to how many other processes can get into their critical sections after a process requests entry into their critical section and before that request is granted
* **Progress** - If no process is currently executing in their critical section, and one or more processes want to execute their critical section, then only the processes not in their remainder sections can participate in the decision, and the decision cannot be postponed indefinitely. ( I.e. processes cannot be blocked forever waiting to get into their critical sections. )

**Solution Structure** - 
```
Entry Code 

Critical Section

Exit Code

Remainder Section
```

> **Note** - In all the solutions for critical section, it is assumed that entry code and exit code will be **Atomic**.

### Peterson's Solution | Turn Variable | Software Based Solution
* **turn** - Whose turn is it to go into critical section
* **flag[i]** - Whether process i wants to go into critical section or not. 1 if yes

```c++
do{
    // Entry code below three lines
    flag[i] = true;
    turn = j;
    while(flag[j] && turn == j);
    
    /*
    Critical Section
    */
    
    flag[i] = false;   //exit code
    
    /*
    Remainder Section
    */

}while(true);
```

### Hardware Synchronization | Test & Set solution

* Below code lacks condition of bounded waiting.
* To achieve bounded waiting, while exiting we can check in a circular manner, if there is process which is waiting then enter it in critical section otherwise simply open the lock to all process

```c++
// Supposed to be an atomic operation provided by hardware
bool TestAndSet(boolean *target) // sets target and returns its previous value
{
    bool res = *target;
    *target = true;
    return res;
}

do{
    while(TestAndSet(&lock));  //entry code
    
    /*
    critical section
    */
    
    lock = false;  // exit code
    
    /*
    Remainder section
    */
    
}while(true);
```

### Mutex
* Its functions are based upon a **locking mechanism**. It is used give access to a resource to only one process at a time.

---
>**Note** - [Difference between Mutex & Semaphore](https://afteracademy.com/blog/difference-between-mutex-and-semaphore-in-operating-system)
---

### Semaphores | [Link](https://www.interviewbit.com/operating-system-interview-questions/#semaphore-and-its-types)
* Semaphore is a **signaling mechanism**. It only holds one positive integer value. It is simply used to solve the problem or issue of critical sections in the synchronization process by using two atomic operations i.e., `wait()` and `signal()`. 

**Implementation Consisting of Spin-Lock and also the problem of starvation** - 
```c++
void wait(S)
{
    while(S <= 0) ;
    S--;
}

void signal(S)
{
    S++;
}

do{
    wait(S)  //entry code
    
    /*
    critical section
    */
    
    signal(S)  // exit code
    
    /*
    Remainder section
    */
    
}while(true);
```

> **Note**
> * One problem with the implementation shown here, ( and in the hardware solutions presented earlier ), is the busy loop used to block processes in the acquire phase. These types of locks are referred to as **spinlocks**, because the CPU just sits and spins while blocking the process.
> * Spinlocks are wasteful of cpu cycles, and are a really bad idea on **single-cpu single-threaded machines**, because the spinlock blocks the entire computer, and doesn't allow any other process to release the lock. ( Until the scheduler kicks the spinning process off of the cpu. )
> * On the other hand, spinlocks do not incur the overhead of a context switch, so they are effectively used on **multi-threaded machines** when it is expected that the lock will be released after a short time.

**Implementation resolving spin-lock and also the problem of starvation** - 

```c++
void wait(S)
{
    S->value--;
    if(S->value < 0) {
        //add process to suspended process lis
        block();
    }
}

void signal(S)
{
    S->value++;
    if(S->value <= 0)
    {
        // remove a process P  from suspended process list. 
        // Algorithm for selecting process must ensure bounded waiting
        wakeUp(P);
    }
}

do{
    wait(S)  //entry code
    
    /*
    critical section
    */
    
    signal(S)  // exit code
    
    /*
    Remainder section
    */
    
}while(true);
```

---

### Priority Inversion
* A challenging scheduling problem arises when a high-priority process gets blocked waiting for a resource that is currently held by a low-priority process.
* If the low-priority process gets pre-empted by one or more medium-priority processes, then the high-priority process is essentially made to wait for the medium priority processes to finish before the low-priority process can release the needed resource, causing a **priority inversion**.
* One solution is a priority-inheritance protocol, in which a low-priority process holding a resource for which a high-priority process is waiting will temporarily inherit the high priority from the waiting process. This prevents the medium-priority processes from preempting the low-priority process until it releases the resource, blocking the priority inversion problem.


