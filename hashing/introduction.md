## Introduction
[Intro](https://www.geeksforgeeks.org/hashing-set-1-introduction/) | [Separate-Chaining](https://www.geeksforgeeks.org/hashing-set-2-separate-chaining/) | [Open-Addressing](https://www.geeksforgeeks.org/hashing-set-3-open-addressing/) | [Load-factor-and-Rehashing](https://www.geeksforgeeks.org/load-factor-and-rehashing/)

**Characteristic of a hash function** - 
* Easily computable
* Uniformly distributes keys

**Load Factor** - It is defined as number of entries in the hash table / size of hash table.

**Ways to handle collision** - 
* Separate Chaining
* Open Addressing


**Separate Chaining** - 
* The idea is to make each cell of hash table point to a linked list of records that have same hash function value

Advantages: 
1. Simple to implement. 
2. Hash table never fills up, we can always add more elements to the chain. 
3. Less sensitive to the hash function or load factors. 
4. It is mostly used when it is unknown how many and how frequently keys may be inserted or deleted. 

Disadvantages: 
1. Cache performance of chaining is not good as keys are stored using a linked list. Open addressing provides better cache performance as everything is stored in the same table.
2. Wastage of Space (Some Parts of hash table are never used) 
3. If the chain becomes long, then search time can become O(n) in the worst case. 
4. Uses extra space for links.

Performance Evaluation - 
* m = Number of slots in hash table
* n = Number of keys to be inserted in hash table
* Load factor α = n/m 
* Expected time to search = O(1 + α)
* Expected time to delete = O(1 + α)
* Time to insert = O(1)
* Time complexity of search insert and delete is O(1) if  α is O(1)


**Open Addressing** - 
In Open Addressing, all elements are stored in the hash table itself. So at any point, the size of the table must be greater than or equal to the total number of keys.
* Insert(k): Keep probing until an empty slot is found. Once an empty slot is found, insert k.
* Search(k): Keep probing until slot’s key doesn’t become equal to k or an empty slot is reached. 
* Delete(k): Delete operation is interesting. If we simply delete a key, then the search may fail. So slots of deleted keys are marked specially as “deleted”. 

Performance - 
* m = Number of slots in the hash table
* n = Number of keys to be inserted in the hash table
* Load factor α = n/m  ( < 1 )
* Expected time to search/insert/delete < 1/(1 - α) 
* So Search, Insert and Delete take (1/(1 - α)) time

**Probing** - 
* Linear Probing - In linear probing, we linearly probe for next slot. 
* Quadratic Probing - We look for next i^2 th slot for probing
* Double Hashing Probing - We use another hash function hash2(x) and look for `i*hash2(x)` slot in i’th rotation.


**Rehashing** - As the name suggests, rehashing means hashing again. Basically, when the load factor increases to more than its pre-defined value (default value of load factor is 0.75), the complexity increases. So we simply resize our hash table and rehash the previous entries
