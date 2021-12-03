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
  * A free frame is located or obtained using page-replacement algorithm
  * The process is put on an I/O wait and a disk operation is scheduled to bring that page into main memory
  * After the page has been brought to memory, I/O wait is removed and the process page table is updated by marking that page as `valid`
  * **The instruction that caused page fault trap has to be restarted from the begining**

**NOTE**
* Hardware support required for Virtual Memory is - **Page Table** and **Swap Space**
* **Swap Space** -  It is used as virtual memory which contains process memory images. Whenever our computer runs short of physical memory it uses its virtual memory and stores information in memory on disk. Swap space helps the computer’s operating system in pretending that it has more RAM than it actually has. | [Link](https://www.geeksforgeeks.org/swap-space-in-operating-system/)
* **Backing Store** - Backing store is typically part of a hard disk that is used by a paging or swapping system to store information not currently in main memory. Backing store is slower and cheaper than main memory. It is generally used as synonym for Swap Space | [Link](https://www.memorymanagement.org/glossary/b.html)


**NOTE**
* One crucial part while handling page fault trap is that instruction has to be restarted again, for most architecture this is not as issue as a single instruction wont modify a large block of data, but for some architecture this may be an issue
* To overcome above issue, system can access both ends of the block before executing the instruction, guaranteeing that the necessary pages get paged in before the instruction begins.

**NOTE** - `Pure Demand Paging` - When No pages are swapped into memory until they are requested by page faults

**NOTE** - Effective access time of demand paging - `EMAT = (1-p)*m + p*f`, where p is page fault rate, m is memory access time, f is page fault service time

---



  


