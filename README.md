## Approaching a problem 

### Algorithms

* **Backtracking**
* **Bitmasking**
  * Subset Sum 
  * DP on broken profile
* **DP**
  * Standard DP
  * String DP
  * Combinatorial DP
* **Graph - Algorithms**
  * DSU 
  * Unweighted graph
    * DFS/BFS
    * Topological Sorting 
    * Bridges
    * Articulation Point | Biconnected Components
    * Euler path
    * Strongly Connected components
    * 2-SAT
  * Weighted graph
    * Shortest Path
    * Minimum Spanning Tree
    * Negative Cycle
  * LCA
* **Binary Search**
  * Standard Binary Search
  * kth order statistics
  * Binary search on ans | reverse thinking
* **Sliding Window**
* **Two-pointers**
* **Reverse Engineering**
* **Sorting**
* **Sqrt Decomposition**


### String Algorithms
* Rabin-Karp Hashing
* KMP
* Z-algo
* Manacher Algorithm

### Queries Type problem
* Offline solve
* Segment Tree - Standard | Merge-Sort Segment Tree | Lazy Segment Tree
* Fenwick Tree
* Sparse Table
* Mo's Algorithm

### Data Structures
* Heap
* Hashing
* Stack
* Queue
* Linked List
* Binary Tree

---

## Steps to follow during Google-Interview

* Understand the Question
* Write down all the input and its form
* Write down one example and get ans of it, if not provided by interviewer
* Think Of Solution and its time complexity
* Discuss the solution with the recruiter at the same time dry run
* Discuss corner cases
* Write code
* Dry run on code and corner cases

---

## Code writing rules to be followed in Google Interview
1. Try to make code, as **modular** as possible.
2. Make self explanatory data structures. For e.g - In case of 2D point, make a struct point
```c++
struct Point
{
  int x,y;
}
```
3. Naming
    * **Variable** names should be self-explanatory with underscores in between. For e.g - `adjacency_list`
    * **Function** names should be self-explanatory with each first letter capitalised. For e.g. - `MyCustomSort`
    * **Constants** are prefixed by k. For e.g. - `const int kDaysInAWeek = 7;`
    * **Class data members** are named similarly as variable names with an extra trailing underscore. For e.g. - `my_class_data_member_`
