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






