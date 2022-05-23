### What is OS and what are its functions | [Link](https://www.interviewbit.com/operating-system-interview-questions/)

* Operating System (OS) is basically a software program that manages and handles all resources of a computer such as hardware and software
* An OS is responsible for managing, handling, and coordinating overall activities and sharing of computer resources
* It acts as an intermediary among users of computer and computer hardware
* Functions of OS - 
  * Memory and Processor Management
  * File Management and Device Management
  * Scheduling of resources and jobs
  * Error Detection
  * Security

---

### What are different types of OS | [Link](https://www.interviewbit.com/operating-system-interview-questions/#understanding-os)

* **Batched OS** (Example: Payroll System, Transactions Process, etc.)
  * OS batches similar types of jobs and run them automatically 
* **Multi-Programmed OS** (Example: Windows O/S, UNIX O/S, etc.)
* **Timesharing OS** (Example: Multics, etc.)
  * A time shared operating system uses CPU scheduling and multi-programming to provide each user with a small portion of a shared computer at once.
* **Distributed OS** (LOCUS, etc.) 
* **Real-Time OS** (PSOS, VRTX, etc.)
  * A real-time operating system (RTOS) is a special-purpose operating system used in computers that has strict time constraints for any job to be performed. 

---

### What is Bootstrap Program in OS | [Link](https://www.interviewbit.com/operating-system-interview-questions/#bootstrap-program-os)

* It is the first code that is executed when the system startups and is located at fix place in disk called boot blocks
* It is responsible for reading and loading OS.
* It also locates kernel and loads into main-memory after which programs start execution

---

### What is kernel in OS | [Link](https://www.interviewbit.com/operating-system-interview-questions/#kernel-and-its-functions-os)

* The kernel is basically a computer program usually considered as a central component or module of OS. 
* It is responsible for handling, managing, and controlling all operations of computer systems and hardware. 
* Whenever the system starts, the kernel is loaded first and remains in the main memory. 
* It also acts as an interface between user applications and hardware.

---

### What is difference between Kernel and OS | [Link](https://www.interviewbit.com/operating-system-interview-questions/#kernel-vs-os) | [Link](https://stackoverflow.com/questions/3315730/what-is-the-difference-between-the-operating-system-and-the-kernel)

* The kernel is part of the operating system and closer to the hardware it provides low level services like:
  * device driver
  * process management
  * memory management
  * system calls
* An operating system also includes applications like the user interface (shell, gui, tools, and services).

---

### What are different types of kernels | [Link](https://www.interviewbit.com/operating-system-interview-questions/#difference-between-microkernel-and-monolithic-kernel) | [Link](https://en.wikipedia.org/wiki/Kernel_(operating_system))

* **Monolithic Kernels** - 
  * In a monolithic kernel, all OS services run along with the main kernel thread, thus also residing in the same memory area. This approach provides rich and powerful hardware access.
  * It is fast
  * It uses signals and sockets for IPC
  * Disadvantages
    * If a service crashes, the whole system crashes in a monolithic kernel.
    * With increase in size, large kernels are difficult to maintain   
* **Micro Kernels** - 
  * It is a minimal OS that executes only important functions of OS. Other services are moved out into severs.
  * It uses message queues to achieve IPC
  * Used in all modern OSes
  * Advantages
    * If a service crashes, it may not affect on working of the microkernel.
    * It is easy to maintain and extendible   

---

### What is Spooling in OS | [Link](https://www.geeksforgeeks.org/what-exactly-spooling-is-all-about/)

* SPOOL is an acronym for **simultaneous peripheral operations on-line**
* It is a kind of buffering mechanism or a process in which data is temporarily held to be used and executed by a device, program or the system.
* E.g - 
  * The most common can be found in I/O devices like keyboard printers and mouse. 
  * For example, In printer, the documents/files that are sent to the printer are first stored in the memory or the printer spooler. 
  * Once the printer is ready, it fetches the data from the spool and prints it.

---

### What is Race Condition | [Q32](https://www.techgeekbuzz.com/os-interview-questions/)

* It is a situation that occurs when different operations are performed on the same data simultaneously, and the outcome of the execution depends on the order of the operations performed on the data. Evidently, the race condition can provide an undesirable outcome.

---

### What do you know about cascading termination? | [Q70](https://www.techgeekbuzz.com/os-interview-questions/)

* When a process finishes execution, then the operating system terminates the process via the exit system call. 
* Only the parent process can cause the termination of its child processes, so when the parent process completes execution and is terminated, then its child process also gets terminated automatically.
* This phenomenon of a process triggering the termination of another process is known as cascading termination.
