## Implement Queue using Stacks
[Link](https://www.geeksforgeeks.org/queue-using-stacks/)

**By making Enqueue operation costly - Enqueue - O(n), Dequeue - O(1)**

Use two stacks s1 & s2
* Push(x) - 
    * Pop all the elements from s1 and push them into s2. 
    * Then push x into s1. 
    * Now pop all the elements from s2 and push them in s1.
* Pop - 
    * Simply pop element from s1.

**By making Dequeue operation costly - Enqueue - O(1), Dequeue - Worst case - O(n), Amortized - O(1)**  -- Better than previous solution.

Use two stacks s1 & s2
* Push(x) - 
    * Simply Push x into s1.
* Pop 
    * If s2 is empty pop all the elements of s1 and push them into s2. 
    * Lastly simply pop element from s2.

---

## Implement Stacks using Queues
[Link](https://www.geeksforgeeks.org/implement-stack-using-queue/)

**By making Push operation costly - Push - O(n), Pop - O(1)**

Use two queues q1 & q2
* Push(x) - 
    * Enqueue x into q2 
    * Enqueue all the elements of q1 into q2
    * swap q1 & q2
* Pop - 
    * Simply dequeue from q1

**By making Pop operation costly - Push - O(1), Pop - O(n)**

Use two queues q1 & q2
* Push(x) - 
    * Enqueue x in q1

* Pop - 
    * Dequeue all elements from q1 and enqueue them in q2, except the last one.
    * Dequeue last element from q1
    * swap q1 & q2

We can achieve this solution using single queue as follows, given we can know the size of queue - 
* Push(x) - Let s be size of q1 before enqueuing. Enqueue x in q1. Now, Dequeue and enqueue q1 s number of times.
* Pop - Simply dequeue q1.

---

## Design a stack that supports getMin() in O(1) time and O(1) extra space
[Link](https://www.geeksforgeeks.org/design-a-stack-that-supports-getmin-in-o1-time-and-o1-extra-space/) | [Link](https://www.geeksforgeeks.org/design-and-implement-special-stack-data-structure/)
/
**Solution Approach** - 
* Push(x) - 
   * If stack is empty, simply push x into stack and update `min_ele = x`
   * else if x >= min_ele, simply push x into stack
   * else if x < min_ele, push `2 * x - min_ele` into stack and update `min_ele = x`

* Pop() - 
  * If stack is empty return error
  * else if stack.top() >= min_ele, simply pop top element from the stack
  * else if stack.top() < min_ele, then pop `min_ele` and update `min_ele = 2 * min_ele - stack.top()`

* getMin() - simply return `min_ele`

---

## Always think about linked list implementation of stack too, for solving problem.
* [Design a stack with operations on middle element](https://www.geeksforgeeks.org/design-a-stack-with-find-middle-operation/)
* [How to create mergable stack?](https://www.geeksforgeeks.org/create-mergable-stack/)
* [Implement Stack and Queue using Deque](https://www.geeksforgeeks.org/implement-stack-queue-using-deque/)

---

## How to efficiently implement k stacks in a single array?
[Link](https://www.geeksforgeeks.org/efficiently-implement-k-stacks-single-array/)

```c++
class kStacks
{
    vector<int>arr,next,top;
    int n,k;
    int free_index;
    
    public:
        kStacks(int n1, int k1)
        {
            n = n1, k = k1;
            arr.clear(),arr.resize(n); // array to store stack entries.
            
            // when arr[i] is empty, next[i] will store next free element from ith index
            // otherwise it will store previous element to facilitate popping operation
            next.clear(),next.resize(n);
            
            top.clear(),top.resize(k,-1); // array to store index of top of each k stacks.
            
            free_index = 0;
            for(int i=0;i<n-1;i++)next[i] = i+1;
            next[n-1] = -1; // to mark the end of free space
        }
        
        void push(int x, int sn)
        {
            if(free_index == -1)return; // overflow condition
            
            int pushed_index = free_index;  // push at free index.
            free_index = next[free_index];   // update free index to next free index now.
        
            next[pushed_index] = top[sn];  // update next of pushed index as current top of sn to facilitate popping
            top[sn] = pushed_index;   // update top of sn as pushed_index
            
            arr[pushed_index] = x;
            return;
        }
        
        int pop(int sn)
        {
            if(top[sn] == -1)return INT_MIN; //underflow condition
            
            int popped_index = top[sn];
            int val = arr[popped_index];
            
            top[sn] = next[popped_index]; // go to previous element
            
            next[popped_index] = free_index;  
            free_index = popped_index; // make popped element free
            
            return val;
        }
    
};

```









