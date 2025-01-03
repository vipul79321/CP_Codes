[Link](https://www2.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/8_MainMemory.html)

---

**NOTE** - [Copy-on-write Forking](https://www.geeksforgeeks.org/copy-on-write/)
* The idea behind a copy-on-write is that when a parent process creates a child process then both of these processes initially will share the same pages in memory.
* These shared pages will be marked as copy-on-write.
* Now if any of these processes will try to modify the shared pages then only a copy of these pages will be created and the modifications will be done on the copy of pages by that process and thus not affecting the other process.
---

**NOTE** - In decreasing order of **access speed**
* Registers
* Cache
* Main Memory
* Secondary Memory(Hard-drive)
---

### Address Binding
[Link](https://www.geeksforgeeks.org/memory-allocation-techniques-mapping-virtual-addresses-to-physical-addresses/)
* Address binding is the process of mapping from **logical** address space to **physical** address space.
* There are three types of address binding - 
  * **Compile Time** 
    * If you know that during compile time, where process will reside in memory, then an absolute address is generated. i.e the physical address is embedded to the executable of the program during compilation.
    * Loading the executable as a process in memory is very fast.
    * But if program is relocated then it has to be **recompiled**
  * **Load Time**
    * If the location at which a program will be loaded is not known at compile time, then the compiler must generate relocatable code with reference relative to address of start of program
    * If that address changes then program must be **reloaded**
    * The loader translates the relocatable address to an absolute address
  * **Execution Time** 
    * If a program can be moved around in memory during the course of its execution, then binding must be delayed until execution time.
    * This requires special hardware, and is the method implemented by most modern OSes.
    * E.g - this technique is used in compaction

![Multi-step processing of user program](https://github.com/vipul79321/CP_Codes/blob/main/images/multistep-processing-of-user-program.jpg)

---

### Logical and Physical Address
[Link](https://www.geeksforgeeks.org/logical-and-physical-address-in-operating-system/)

* **Logical Address** - The address generated by the CPU is a logical address. It is also known as **virtual address**
* **Physical Address** - The address actually seen by the memory hardware is a physical address.
* **Logical Address Space** - The set of all logical addresses used by a program composes the logical address space
* **Physical Address Space** - The set of all corresponding physical addresses composes the physical address space.

**NOTE** - 
* Addresses bound at compile time or load time have **identical** logical and physical addresses.
* Addresses created at execution time, however, have different logical and physical addresses
* Mapping of logical address to corresponding physical address is done by **Memory Management Unit**
* **Relocation Register** - Used as reference for logical address to generate relocatable code 
* **Limit Register** - Used as limit to prevent illegal memory access. All access should be range `[Relocation Register, Relocation Register + Limit Register]`

---

### Dynamic Loading

* Rather than loading an entire program into memory at once, dynamic loading loads up each routine as it is called. 
* The advantage is that unused routines need never be loaded, reducing total memory usage and generating faster program startup times. 
* The downside is the added complexity and overhead of checking to see if a routine is loaded every time it is called and then then loading it up if it is not already loaded.

---

### Static Linking vs Dynamic Linking
[Link](https://www.geeksforgeeks.org/static-and-dynamic-linking-in-operating-systems/)

* **Static Linking**
  * With static linking library modules get fully included in executable modules.
  * _Disadvantages_ -
    * It wastes both disk space and main memory usage because every program that included a certain routine from the library would have to have their own copy of that routine linked into their executable code.
    * Whenever a library routine updates then the program must be re-built ( re-linked ) in order to incorporate the changes.

* **Dynamic Linking** - 
  * With dynamic linking, however, only a stub(a statically linked function) is linked into the executable module, containing references to the actual library module linked in at run time.
  * _Advantages_
    * Saves memory
    * Easy to share - If the code section of library routine is reentrant then we can only load one copy of dynamically linked routines into memory and sharing the code amongst all processes
    * Library routines are updated then we dont need to rebuild as long as stub remains the same. The program can be updated merely by loading new versions of the DLLs onto the system

---
**NOTE** - If compile-time or load-time address binding is used, then processes must be swapped back into the same memory location from which they were swapped out. If execution time binding is used, then the processes can be swapped back into any available location.

---
**NOTE** - **Reentrant** program means that it does not write to or change the code in any way ( it is non self-modifying ), and it is therefore safe to re-enter it.

---

### Contiguous Memory Allocation

* Contiguous memory allocation allocates consecutive blocks of memory to a file/process.
* Contiguous memory allocation can be categorized into two ways :
  * [Fixed partition scheme](https://www.geeksforgeeks.org/fixed-or-static-partitioning-in-operating-system/)
    * The number of partition of RAM is fixed, size of partition may or may not be same
    * _Advantages_
      * Easy to implement
    * _Disadvantages_
      * Internal Fragmentation
      * External Fragmentation
      * Restriction of maximum process size and degree of multiprogramming
  * [Variable partition scheme](https://www.geeksforgeeks.org/variable-or-dynamic-partitioning-in-operating-system/)
    * Intially RAM is empty and partition are made during runtime according to process's need
    * Therefore, Number of partitions in RAM is not fixed and depends on the number of incoming process and Main Memory’s size.
    * _Advantages_
      * No Internal Fragmentation - As partition are made depending on the process size itself at runtime
      * No restriction on maximum process size and degree of multiprogramming
    * _Disadvantages_ 
      * Difficult Implementation
      * External Fragmentation - As when a processes leaves they creates a hole equal to its size   

**Different Contiguous Memory Allocation Strategies** - 
* **First Fit** - Searches the first available hole from beginning, that is big enough to accomodate the process
* **Next Fit** - Searches the first available hole from where it last left-off, that is big enough to accomodate the process
* **Best Fit** - Searches smallest available hole that is big enough to accomodate the process
* **Worst Fit** - Assign largest available hole, if it can accomodate the process

**Few Important Points** - 
* Next fit and First fit are generally faster than other strategies while next fit being slightly more faster
* First fit tends to create more internal fragmentation in the begining, while next fit overcomes it by looking from the position is last left-off
* Simulations show that either first or best fit are better than worst fit in terms of both time and storage utilization.
* Best fit tends to create more internal fragmentation as leftover space is very small
* In worst fit, leftover space is large so it may be used by other smaller process


[Fragmentation](https://www.geeksforgeeks.org/difference-between-internal-and-external-fragmentation/)

**Internal Fragmentation**
* It happens when we allocate process to fixed size block. It may happen that block size is greater than what is required by process and this wasted space results in internal fragmentation
* Internal fragmentation can be avoided by dynamic allocation

**External Fragmentation**
* External fragmentation means that the available memory is broken up into lots of little pieces, none of which is big enough to satisfy the next memory requirement, although the sum total could.
* It can be overcome using paging or compaction

**Compaction** 
* External Fragmentation can be solved using compaction, given that all the programs  in memory are relocatable, then we can move all process down to one end of physical memory
* This only involves updating the relocation register for each process, as all internal work is done using logical addresses.


**Difference between Contiguous and Non-Contiguous Memory Allocation**

[Link](https://www.geeksforgeeks.org/difference-between-contiguous-and-noncontiguous-memory-allocation/)

| Contiguous Memory Allocation	| Non-Contiguous Memory Allocation |
| ----------------------------- | -------------------------------- |
| Contiguous memory allocation allocates consecutive blocks of memory to a file/process. |	Non-Contiguous memory allocation allocates separate blocks of memory to a file/process. |
| Faster and easier to implement.	| Slower and difficult to implement. |
| Overhead is minimum as not much address translations are there while executing a process.	| More Overheads are there as there are more address translations. |
| Wastage of memory is there. |	No memory wastage is there. |

---

### Segmentation
[Link](https://www.geeksforgeeks.org/segmentation-in-operating-system/)

* Operating Systems, Segmentation is a memory management technique in which the memory is divided into the variable size parts called as Segments
* Each Segment represents User's view of the process. For example, a C compiler might generate 5 segments for the user code, library code, global ( static ) variables, the stack, and the heap

**Types of Segmentation**
* **Virtual memory segmentation** – Each process is divided into a number of segments, not all of which are resident at any one point in time.
* **Simple segmentation** – Each process is divided into a number of segments, all of which are loaded into memory at run time, though not necessarily contiguously.

**Segment Table** - 
* It stores base address and limit of each segment. 
* Address generated by CPU contains segment number and offset. Segment table is then used to get base address of that segment and offset is checked against limit to make sure no illegal access takes place

**Advantages of Segmentation**
* **No Internal fragmentation**.
* Segment Table consumes less space in comparison to Page table in paging.

**Disadvantage of Segmentation**
* As processes are loaded and removed from the memory, the free memory space is broken into little pieces, causing **External fragmentation.**

---

### Paging
[Link](https://www.geeksforgeeks.org/paging-in-operating-system/) 

#### Paging
* Paging is a memory management scheme that allows processes physical memory to be discontinuous, and which eliminates problems with **external fragmentation** by allocating memory in equal sized blocks known as **pages**.
* The Physical Address Space is conceptually divided into a number of fixed-size blocks, called **frames**.
* The Logical address Space is also splitted into fixed-size blocks, called **pages**.
* **Page Size = Frame Size**

#### Page Table
* Logical address generated by CPU contains - `page no. | offset`
* Page table is used to get the `frame no.` where that page resides
* **Number of bits in page no. represents size of page table of that process**
* **Number of bits in frame no. represents number of frames in physical address space**

**NOTE** - 
* The operating system must keep track of each individual process's page table, updating it whenever the process's pages get moved in and out of memory. This all increases the overhead involved when swapping processes in and out of the CPU.
* There is no external fragmentation with paging, but internal fragmentation is possible


#### Hardware Support
* **Motivation** - Page lookups must be done for every memory reference, and whenever a process gets swapped in or out of the CPU, its page table must be swapped in and out too, along with the instruction registers, etc.
* Various Hardwares - 
  * **Register** can be used to store page-table. But they are small and expensive
  * **Page Table Base Register** - 
    * We store page table in main memory 
    * We can store where in the main memory our page table is stored in PTBR
    * But now memory access got half as fast, as now we need to access page-table from main memory and then corresponding frame in main-memory
  * **Translation Look-aside Buffer (TLB)** | [Link](https://www.geeksforgeeks.org/translation-lookaside-buffer-tlb-in-paging/)
    * TLB is a special cache that contains page table entries that have been most recently used.
    * _Steps in TLB Hit_
      * CPU generates logical address `page no.|offset` 
      * It is checked in TLB, TLB hit if present
      * Corresponding frame number is retrieved from TLB entry and physical address is generated
    * _Steps in TLB Miss_
      * CPU generates logical address `page no.|offset` 
      * It is checked in TLB, TLB miss if not present
      * Now it will check that page no. in page-table present in main-memory
      * TLB is updated with new PTE using various page-replacement techniques
    * _Effective Memory Access Time (EMAT)_
      * `EMAT = h*(c+m) + (1-h)*(c+2m)`
      * Here h = TLB hit ratio
      * c = TLB Access Time
      * m = Main Memory Access Time 

**NOTE** - 
[Link](https://cs.stackexchange.com/questions/94226/how-does-the-tlb-identify-a-particular-process) | [Link](https://gateoverflow.in/210774/Does-every-process-have-its-own-tlb) | [Link](https://gateoverflow.in/210774/Does-every-process-have-its-own-tlb?show=210994#c210994) | [Link](https://en.wikipedia.org/wiki/Translation_lookaside_buffer#Address-space_switch) 
* Every process doesnt have their own TLB, there is one TLB only
* There are two strategies to follow when there is a context switch.
  * Flush the TLB.
  * Mark the entries of TLB invalid those do not belong to the current process.
  * Saving Process id alongwith TLB entries

#### Protection
* Page table can also help to protect processes from accessing memory that they shouldn't, or their own memory in ways that they shouldn't.
* A bit or bits can be added to the page table to classify a page as read-write, read-only, read-write-execute etc
* We can also add valid-invalid bits in page-table entries to signify whether that page is present in main memory and call page fault if not present | [Link](https://cs.stackexchange.com/a/91693)

#### Shared Pages
* Paging systems can make it very easy to share blocks of memory, by simply duplicating frame numbers in multiple page tables. This may be done with either code or data.

---

### Multi-Level Paging | Hierarchical Paging
[Link](https://www.geeksforgeeks.org/multilevel-paging-in-operating-system/) | [Imp Question](https://www.geeksforgeeks.org/multilevel-paging-in-operating-system/)

* The entries of the level 1 page table are pointers to a level 2 page table and entries of the level 2 page tables are pointers to a level 3 page table and so on. 
* The entries of the last level page table are stores actual frame information.
* Level 1 contain single page table and address of that table is stored in **PTBR (Page Table Base Register)**
* **MultiLevel Paging solves the problem of storing a big page table at single contiguous memory location**

```
---
For numericals, if not mentioned size of each page table will be equal to page size
---
Number of entries in page table = (virtual address space size) / (page size) = Number of pages
---
Virtual address space size= 2^n B | Assuming n bits are used to represent logical address
---
Size of page table = (number of entries in page table)*(size of PTE)
---
```

**Disadvantages of multi-level paging** - With each memory access to page tabel on each level, it increases translation overhead

---

### Hashed Page Tables
[Link](https://www.geeksforgeeks.org/hashed-page-tables-in-operating-system/)

* Let logical address be `page-no | offset`
* `page-no` will be hashed and then entered in page-table at hashed location
* In hashed page table, each entry in page table is linked list(to handle hash-collision) of `pair<page-no, frame-no>`
* It is useful to avoid translation overhead in multi-level paging

---

### Inverted Paging
[Link](https://www.geeksforgeeks.org/inverted-page-table-in-operating-system/)

* Instead of having separate page table for each process, we create a single page table for each frame and hence called **Inverted Page Table**
* Inverted page table indexes will refer to frame no and entries will `pair<process id, page no.>`
* Access to an inverted page table can be slow, as it may be necessary to search the entire table in order to find the desired page. Hashing the table may help to speedup the process
* Normal page sharing is not possible in inverted page table as for each frame it contain `pair<process id, page no.>` as entry in inverted page table, although this can be overcome using **Chained pointer** ( where each entry will in inverted page table will be `vector<pair<process id, page no.>`

---

### Segmented Paging and Paged Segmentation
[Link](https://www.geeksforgeeks.org/paged-segmentation-and-segmented-paging/)
