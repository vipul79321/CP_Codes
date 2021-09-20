## How to efficiently implement K-Queues in a single array
[Link](https://www.geeksforgeeks.org/efficiently-implement-k-queues-single-array/)

**Solution Approach** - 
* Create following arrays - 
  * front[k] - To store index of front element of ith queue
  * rear[k] - To store index of last element of ith queue
  * next[n] - To store index of next free element if arr[i] is unoccupied, else to store index of next element in the queue if arr[i] is occupied

```c++
class kQueues
{
    int n,k;
    vector<int>arr,next,front,rear;
    int free_index;
    
    public:
        kQueues(int n1, int k1)
        {
            n = n1, k = k1;
            arr.clear();arr.resize(n);
            next.clear();next.resize(n);
            
            front.clear();front.resize(k);
            rear.clear();rear.resize(k);
            
            for(int i=0;i<n-1;i++)next[i] = i+1;
            next[n-1] = -1;
            
            for(int i=0;i<k;i++)
            {
                rear[i] = front[i] = -1;
            }
            
            free_index = 0;
        }
        
        void push(int item, int qn)
        {
            if(free_index == -1)return; // overflow condition
            
            int pushed_index = free_index;
            free_index = next[free_index];  //updating next free_index;
            
            if(front[qn] == -1)
            {
                front[qn] = pushed_index;
            }
            else
            {
                next[rear[qn]] = pushed_index;
            }
            
            rear[qn] = pushed_index;
            next[pushed_index] = -1; // to mark the end of the  queue;
            arr[pushed_index] = item;
        }
        
        int pop(int qn)
        {
            if(front[qn] == -1)return INT_MIN; // underflow condition
            
            int popped_index = front[qn];
            front[qn] = next[popped_index];
            if(front[qn] == -1) // if queue got empty
            {
                rear[qn] = -1;
            }
            
            next[popped_index] = free_index;
            free_index = popped_index;
            return arr[popped_index];
        }
};
```

----

## LRU Cache


