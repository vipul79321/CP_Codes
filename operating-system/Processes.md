[Link](https://www2.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/3_Processes.html)

### Define Process in Operating System
* Process is basically instance of program in execution. It contains all the required information about that program such as code, data etc.

### Difference between Process and Program | [Link](https://www.geeksforgeeks.org/difference-between-program-and-process/)
* Program contains a set of instructions designed to complete a specific task, whereas Process is an instance of an executing program.
* Program is an **static** entity while Process is a **dynamic** entity
* Program is a **passive entity** as it resides in the **secondary memory**, whereas Process is an **active entity** as it is created during execution and loaded into the **main memory**.

### Describe Various sections in which Process memmory is divided 
* **Text Section** - contains **compiled program code**, read in from non-volatile storage when the program is launched.
* **Data Section** - contains **global and static variables**, allocated and initialized prior to executing main.
* **Heap** - Used to handle dynamic memory allocation via new, malloc, delete etc
* **Stack** - Used for local variables 

**Note** - stack and the heap start at opposite ends of the process's free space and grow towards each other. If they should ever meet, then either a stack overflow error will occur, or else a call to new or malloc will fail due to insufficient memory available.

### Various Process states
* **New** - The process is in the stage of being created.
* **Ready** - The process has all the resources available that it needs to run, but the CPU is not currently working on this process's instructions.
* **Running** - The CPU is working on this process's instructions.
* **Waiting** - The process cannot run at the moment, because it is waiting for some resource to become available or for some event to occur. For e.g waiting for I/O.
* **Terminated** - The process has completed.

### Contents of Process Control Block 
* **Process State** - Running, waiting, etc., as discussed above.
* **Process ID**, and parent process ID.
* **CPU registers and Program Counter** - These need to be saved and restored when swapping processes in and out of the CPU.
* **CPU-Scheduling information** - Such as priority information and pointers to scheduling queues.
* **Memory-Management information** - E.g. page tables or segment tables.
* **Accounting information** - user and kernel CPU time consumed, account numbers, limits, etc.
* **I/O Status information** - Devices allocated, open file tables, etc.

### Process Scheduling
* The two main objectives of the process scheduling system are to
  * keep the CPU busy at all times and 
  * to deliver "acceptable" response times for all programs, particularly for interactive ones.
* The process scheduler must meet these objectives by implementing suitable policies for swapping processes in and out of the CPU.

**Note** - these objectives can be conflicting. In particular, every time the system steps in to swap processes it takes up time on the CPU to do so, which is thereby "lost" from doing any useful productive work.

### Schedulers
* **Long-Term Scheduler** - It is a typical of batch system or a very heavily loaded system. It runs infrequently. E.g - When a process is terminated, then selecting one or more process to load into ready queue in its place
* **Short-term scheduler(or CPU Scheduler)** - runs very frequently, and must very quickly swap one process out of the CPU and swap in another one.
* **Medium-term scheduler** - When system loads get high, this scheduler will swap one or more processes out of the ready queue system for a few seconds, in order to allow smaller faster jobs to finish up quickly and clear the system.


### Context - Switching
* Interrupt Handling - Whenever an interrupt arrives, the CPU must do a **state-save** of the currently running process, then switch into kernel mode to handle the interrupt, and then do a **state-restore** of the interrupted process.
* Context Switching - when the time slice for one process has expired and a new process is to be loaded from the ready queue. This will be instigated by a **timer interrupt**, which will then cause the current process's state to be saved and the new process's state to be restored.
* Therefore, context switching is achieved by interrupt handling
* Saving and restoring states involves saving and restoring all of the **Registers, Program counter, PCBs**.

**Note** - Context switching should be very fast, as it happens frequently. Some systems use hardware solutions to achieve speed for example using a single machine instruction for saving or restoring all registers at once.

**Note** - A **program counter (PC)** is a CPU register in the computer processor which has the address of the next instruction to be executed from memory.


### Fork System call
* fork() returns - 
  * 0 - to created child process
  * pid(>0) - to parent process
  * -1 - to parent in case child creation was unsuccessful
* Some differences between the child and parent process are:
  * Different PIDs
  * Separate copies of all data, including variables with their current values and the stack
  * Separate program counter (PC) indicating where to execute next; originally both have the same value but they are thereafter separate
  * after fork, the two processes do not share variables

**NOTE** - If a child process exits or is interrupted, then a **SIGCHLD** signal is sent to the parent process to inform about the termination or exit of the child process.


### Exec system call
* The exec() family of functions replaces the current process image with a new process image.
* **It loads the program into the current process space and runs it from the entry point.**

### How do you send a signal from parent to child process? | [Link](https://www.mvorganizing.org/what-is-parent-process-and-child-process/)
* The communication between child and parent processes can be done using **kill()** and **signal()**.
* The parent can then send messages to child using the pid and kill().
* The child picks up these signals with signal() and calls appropriate functions.
* For information about communication from child to parent see `wait()` system call
* There are standard ways of process communications too (such as pipes, sockets, message queues, shared memories) which can be used for communication between parent & child

### Wait system call | [Link](http://www2.cs.uregina.ca/~hamilton/courses/330/notes/unix/fork/fork.html)
* A system call that causes the process to wait for a signal (waits until any type of signal is received from any process).
* Most commonly used in a parent process to wait for the signal that the OS sends to a parent when its child is terminated
* Returns the pid of the process sending the signal

### Orphan Processes | [Link](https://www.gmarik.info/blog/2012/orphan-vs-zombie-vs-daemon-processes/)
* An **Orphan process** is a running process whose parent process has finished or terminated.
* A **Daemon process** is an intentionally orphaned process in order to have a background process.


### Zombie Processes | [Link](https://www.tutorialspoint.com/what-is-zombie-process-in-linux)
* A zombie process is a process whose execution is completed but it still has an entry in the process table. 
* Zombie processes usually occur for child processes, as the parent process still needs to read its child’s exit status. 
* Once this is done using the wait system call, the zombie process is eliminated from the process table. This is known as reaping the zombie process.

![Zombie Process](https://www.tutorialspoint.com/assets/questions/media/12233/Zombie%20Process%20in%20LInux.png)

Some key points - 
* All the memory and resources allocated to a process are deallocated when the process terminates using the exit() system call. But the process’s entry in the process table is still available. This process is now a zombie process.
* The exit status of the zombie process zombie process can be read by the parent process using the wait() system call. After that, the zombie process is removed from the system. Then the process ID and the process table entry of the zombie process can be reused.
* If the parent process does not use the wait() system call, the zombie process is left in the process table. This creates a resource leak.


### InterProcess Communication
* Cooperating processes are need for - 
  * Computation Speedup
  * Modularity
  * Information sharing
  * Convenience
* Cooperating processes require a way to communicate among themselves
* Some of the common methods of InterProcess Communications are - 
  * **Shared Memory Systems** - E.g Producer - Consumer Problem
  * **Message Passing System**
  * **Sockets** - In client - server systems
  * **Remote Procedure Calls** - In client - server systems


### Shared Memory Systems
* Generally faster than message passing system, but implementation is quite complicated.
* Works well when amount of data to be transferred is large among the same computer

### Message Passing Systems
* Generally slower than shared memory systems, but easy to implement
* Works well when amount of data to be transferred is less but among multiple computers
* Following things needs to be addressed in such systems - 
  * Direct Communication (sender-receiver directly communicate) or Indirect Communication (sender-receiver communicate via shared mailboxes)
  * Buffer size - 0, bounded or unbounded
  * Message sending and recieving should be in sync


### Sockets
* A socket is one endpoint of a two-way communication link between two programs running on the network.
* It is a combination of an IP address and a port number.
* Connection via sockets may be of one of the two forms - 
  * **Connection-Oriented (TCP, Transmission Control Protocol)**
  * **Connectionless(UDP, User Datagram Protocol)**

### Connection-Oriented (TCP, Tranmission Control Protocol)
* Connection-oriented ( TCP, Transmission Control Protocol ) connections emulate a telephone connection. 
* All packets sent down the connection are guaranteed to arrive in good condition at the other end
* They will be delivered to the receiving process in the order in which they were sent. 
* The TCP layer of the network protocol takes steps to verify all packets sent, re-send packets if necessary, and arrange the received packets in the proper order before delivering them to the receiving process. 
* There is a certain amount of overhead involved in this procedure, and if one packet is missing or delayed, then any packets which follow will have to wait until the errant packet is delivered before they can continue their journey.

### Connectionless(UDP, User Datagram Protocol)
* Connectionless ( UDP, User Datagram Protocol ) emulate individual telegrams. 
* There is no guarantee that any particular packet will get through undamaged ( or at all ), and no guarantee that the packets will get delivered in any particular order.
* There may even be duplicate packets delivered, depending on how the intermediary connections are configured. 
* UDP transmissions are much faster than TCP, but applications must implement their own error checking and recovery procedures.

### Remote Procedure calls
* Remote Procedure Call (RPC) is a powerful technique for constructing distributed, client-server based applications. 
* It is based on extending the conventional local procedure calling so that the called procedure need not exist in the same address space as the calling procedure. 
* The two processes may be on the same system, or they may be on different systems with a network connecting them.

![RPC Working](https://media.geeksforgeeks.org/wp-content/uploads/operating-system-remote-procedure-call-1.png)
![RPC Structure](https://media.geeksforgeeks.org/wp-content/uploads/operating-system-remote-call-procedure-working.png)


