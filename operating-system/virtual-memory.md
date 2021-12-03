[Link](https://www2.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/9_VirtualMemory.html)

### Virtual Memory - Motivation

* In practice, most real processes do not need all their pages, or at least not all at once.
* Therefore, instead of bringing all pages to main-memory, we can bring pages only when needed.
* The ability to load only the portions of processes that were actually needed ( and only when they were needed ) has several benefits:
  * Now, program could be written for much larger logical address space than that physically exist on computer
  * Because each process is only using a fraction of their total address space, there is more memory left for other programs, improving **CPU utilization and system throughput**.
  * Virtual memory also allows the sharing of files and memory by multiple processes, with several benefits:
    * System libraries can be shared by mapping them into the virtual address space of more than one process.
    * Process pages can be shared during a fork( ) system call, eliminating the need to copy all of the pages of the original ( parent ) process.

---

### Demand Paging
* The idea behind **demand paging** is that when a process is swapped in, its pages are not swapped in all at once. 
* Rather they are swapped in only when the process needs them. ( on demand. ) 
* This is termed a **lazy swapper**, although a **pager** is a more accurate term.

#### Working of Demand Paging
* When a process is swaped in, **pager** only loads pages that it expects the process would need right away.
* Pages that are not loaded into memory are marked **invalid** in process page-table.
* Whenever process tries to access a page that is not present in main-memory a **page fault trap** is generated
* Handling of page fault trap
  * Find the location of the desired page on the disk, either in swap space or in the file system 
  * Locate a free frame
    * If there is a free frame, use it
    * If there is no free frame, use a page-replacement algorithm to select an existing frame to be replaced, known as the **victim frame.**
    * Write Victim Frame to disk and update all related page-tables to indicating that page has been removed from the memory
    * Generally all page-replacement algorithm tries to select victim frame, whose dirty bit is not set(i.e, their content has not been modified). But using non-dirty frame as victim we can skip writing victim frame to disk as done in above step.
  * The process is put on an I/O wait and a disk operation is scheduled to bring that page into main memory
  * After the page has been brought to memory, I/O wait is removed and the process page table is updated by marking that page as `valid`
  * **The instruction that caused page fault trap has to be restarted from the begining**

**NOTE**It 
* Hardware support required for Virtual Memory is - **Page Table** and **Swap Space**
* **Swap Space** -  It is used as virtual memory which contains process memory images. Whenever our computer runs short of physical memory it uses its virtual memory and stores information in memory on disk. Swap space helps the computer’s operating system in pretending that it has more RAM than it actually has. | [Link](https://www.geeksforgeeks.org/swap-space-in-operating-system/)
* **Backing Store** - Backing store is typically part of a hard disk that is used by a paging or swapping system to store information not currently in main memory. Backing store is slower and cheaper than main memory. It is generally used as synonym for Swap Space | [Link](https://www.memorymanagement.org/glossary/b.html)


**NOTE**
* One crucial part while handling page fault trap is that instruction has to be restarted again, for most architecture this is not as issue as a single instruction wont modify a large block of data, but for some architecture this may be an issue
* To overcome above issue, system can access both ends of the block before executing the instruction, guaranteeing that the necessary pages get paged in before the instruction begins.

**NOTE** - `Pure Demand Paging` - When No pages are swapped into memory until they are requested by page faults

**NOTE** - Effective access time of demand paging - `EMAT = (1-p)*m + p*f`, where p is page fault rate, m is memory access time, f is page fault service time

---

**NOTE** - There are majorly two important task in Virtual Memory Management
* Page Replacement Strategy - It deals with how to select a page for replacement when there are no free frames available.
* Frame Allocation Strategy - It deals with how many frames are allocated to each process ( and to other needs )

---

### Page Replacement Algorithms

* **All page replacement algorithms aim at minimize number of page faults**

#### FIFO Page Replacement Algorithm
* Whenever there is no empty frame, free the page that was first brought into the memory
* FIFO suffers from **Belady's Anomaly** - On increasing number of frames, number of page fault may increase for given reference string. E.g - `( 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 ) ` with frame count as 3 & 4.

#### Optimal Page Replacement Algorithms
* This algorithm will replace the page that will not be used for long-time in the future.
* It cannot be implemented in practice as it requires looking ahead in future, but this algorithm act as a benchmark for performance evaluation of other algorithms

#### Least Recently Used (LRU) Page Replacement Algorithm
* This algorithm will replace the page that has not been used in longest time.
* Common Implementation Approaches - 
  * **Counters** - 
    * Every memory access increments a counter(acting as timer), and the current value of this counter is stored in the page table entry for that page. 
    * Then finding the LRU page involves simple searching the table for the page with the smallest counter value.
  * **Stacks** - 
    * Another approach is to use a stack, and whenever a page is accessed, pull that page from the middle of the stack and place it on the top. 
    * The LRU page will always be at the bottom of the stack. 
    * Because this requires removing objects from the middle of the stack, a **doubly linked list** is the recommended data structure.

**NOTE** - 
* LRU and Optimal Page replacement algorithm gives same number of page faults for reference string S and its reverse
* LRU and Optimal Page replacement algorithm doesnt exhibit Belady's Anomaly
* LRU and Optimal Page replacement algorithm falls in the category of **Stack Algorithm**(A stack algorithm is one in which the pages kept in memory for a frame set of size N will always be a subset of the pages kept for a frame size of N + 1)

#### Least Frequently Used
* Maintain a counter for each page indicating how many times this page has been used
* When replacing, select the page with minimum counter value

#### Most Frequently Used
* Maintain a counter for each page indicating how many times this page has been used
* When replacing, select the page with maximum counter value


#### Page Buffering Algorithms
* They are used alongwith Page-replacement algorithms to achieve optimal performance.

**Idea 1** - 
* Maintain a certain minimum number of free frames at all times. 
* When a page-fault occurs, go ahead and allocate one of the free frames from the free list first, to get the requesting process up and running again as quickly as possible,
* and then select a victim page to write to disk and free up a frame as a second step.

**Idea 2** - 
* Keep a list of modified pages
* When the I/O system is otherwise idle, have it write these pages out to disk, and then clear the modify bits(or dirty bits)
* This increases the chance of finding a "clean" page for the next potential victim.

**Idea 3** - 
* Keep a pool of free frames, but remember what page was in it before it was made free. 
* Since the data in the page is not actually cleared out when the page is freed, it can be made an active page again without having to load in any new data from disk. 
* This is useful when an algorithm mistakenly replaces a page that in fact is needed again soon. 

---

### Some Approximation to LRU
* Since, implementing LRU requires hardware support here are some possible approximations

#### Using Reference Bits
* Maintain reference bits(say 8 bits) for each page, which are right-shifted periodically.
* Whenever a page is accessed Highest bit is set for that page
* Now when replacing, select page with minimum value( converting 8 bits to integer)

#### Second-Chance Algorithm
* Maintain single reference bit for each page, which are cleared out preiodically
* Now when replacing, If we first found a page whose reference bit is set then clear it out and continue searching cyclically till we found a page whose reference bit is not set

#### Enhanced Second-Chance Algorithm
* This algorithm looks for both reference bit and modify bit pair
* It searches for page with following characters in the order mentioned below - 
  *  `( 0, 0 )` - Neither recently used nor modified.
  *  `( 0, 1 )` - Not recently used, but modified.
  *  `( 1, 0 )` - Recently used, but clean.
  *  `( 1, 1 )` - Recently used and modified.

---

### Frame Allocation Strategies
[Link](https://www.geeksforgeeks.org/operating-system-allocation-frames/)

**Few Things to take into consideration while allocating frames** - 
* Total number of frames is limited
* At least a minimum number of frames should be allocated to each process. Reason for that are - 
  * Because if less number of frames are allocated, there is an increase in the page fault ratio, decreasing the performance of the execution of the process.
  * Also, there should be enough frames to hold all the different pages that any single instruction can reference.

**Frame Allocation Algorithms** - 
* **Equal Allocation** - Assigning equal number of frames to each process. If x frames and y processess then each process will get x/y frames
* **Proportional Allocation** - Assigning frames proportional to size of that process. If x frame and y process andeach process as size s_i and total sum of size is s then each process will get `s_i * x / s`

**Types of Allocation** - 
* Number of frames allocated to process can dynamically change depending on the allocation strategy followed - 
* **Local Replacement**
  * When a process needs a page which is not in the memory, it can bring in the new page and allocate it a frame from its own set of allocated frames only.
  * _Advantages_ - The pages in memory for a particular process and the page fault ratio is affected by the paging behavior of only that process.
  * _Disadvantages_ - A low priority process may hinder a high priority process by not making its frames available to the high priority process.
* **Global Replacement**
  * When a process needs a page which is not in the memory, it can bring in the new page and allocate it a frame from the set of all frames, even if that frame is currently allocated to some other process; that is, one process can take a frame from another.   
  * _Advantages_ - Does not hinder the performance of processes and hence results in greater system throughput.
  * _Disadvantages_ - The page fault ratio of a process can not be solely controlled by the process itself. The pages in memory for a process depends on the paging behavior of other processes as well. 

---

### Thrashing
[Link](https://www.geeksforgeeks.org/techniques-to-handle-thrashing/)

* Thrashing is a condition or a situation when the system is spending a major portion of its time in servicing the page faults, but the actual processing done is very negligible. 

#### Cause of Thrashing
* If a process is allocated too few frames, then there will be too many and too frequent page faults. 
* As a result, no useful work would be done by the CPU and the CPU utilisation would fall drastically. 
* The long-term scheduler would then try to improve the CPU utilisation by loading some more processes into the memory thereby increasing the degree of multiprogramming. 
* This would result in a further decrease in the CPU utilization triggering a chained reaction of higher page faults followed by an increase in the degree of multiprogramming, called Thrashing.

#### Locality Model
* The locality model notes that processes typically access memory references in a given locality, making lots of references to the same general area of memory before moving periodically to a new locality.


#### Techniques to handle Thrashing
* **Working Set Model** - 
  * This model is based on Locality Model.
  * It states that If we could just keep as many frames as are involved in the current locality, then page faulting would occur primarily on switches from one locality to another. ( E.g. when one function exits and another is called. ), Otherwise process is bound to thrash
  * This model is based on parameter `A`. A working set of process is set the set of A most recently used pages
  * Total demand of frames `D = Summation(Working Set Size of each process)`
  * If D > Total number of frames, then thrashing will occur otherwise no thrashing

* **Page Fault Frequency** - 
  * This is based on minimizing page-fault rate
  * If the page-fault rate exceeds a certain upper bound then that process needs more frames,
  * and if it is below a given lower bound, then it can afford to give up some of its frames to other processes.

---

### Memory-Mapped Files
[Link](https://www.youtube.com/watch?v=nPIhoJ6lKeQ)

* Rather than accessing data files directly via the file system with every file access, data files can be paged into memory the same as process files, resulting in much faster accesses ( except of course when page-faults occur. ) This is known as **memory-mapping a file.**

**NOTE** 
* File writes are made to the memory page frames, and are not immediately written out to disk. They are written to disk during flush system call or so
* Memory-mapped files can be easily shared among processes by simply adding entry for that in process's page table

---

### Allocating Kernel Memory
[Link](https://www.geeksforgeeks.org/operating-system-allocating-kernel-memory-buddy-system-slab-system/)

**Motivation | Need** - 
* Kernel Memory cannot easily be paged
* Some of it is used for I/O buffering and direct access by devices, example, and must therefore be contiguous and not affected by paging. 
* Other memory is used for internal kernel data structures of various sizes, and since kernel memory is often locked ( restricted from being ever swapped out ), management of this resource must be done carefully to avoid internal fragmentation or other waste.

**Different Allocation Strategies** - 
* [**Buddy System**](https://en.wikipedia.org/wiki/Buddy_memory_allocation)
* [**Slab Allocation**](https://en.wikipedia.org/wiki/Slab_allocation)

  


