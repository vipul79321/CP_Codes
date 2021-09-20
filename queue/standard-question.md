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
[Link](https://www.geeksforgeeks.org/lru-cache-implementation/) | [Link](https://leetcode.com/problems/lru-cache/)

**Solution Approach**
* Maintain an LRU list containing most recent used page in front and least recent use page in back.
* Maintain an map of `<key,list::iterator>`, to get the position of that key in LRU, deletion, insertion in list are done in O(1), if we know its position.

```c++
class LRUCache {
public:
    list<int>lru;
    unordered_map<int,list<int>::iterator>position;
    unordered_map<int,int>key_to_value;
    int capacity,sz;
    
    LRUCache(int capacity)
    {
        this->capacity = capacity;
        lru.clear(); position.clear();
    }
    
    int get(int key)
    {
        if(key_to_value.find(key) != key_to_value.end())
        {
            lru.erase(position[key]);
            lru.push_front(key);
            position[key] = lru.begin();
            return key_to_value[key];
        }
        else
        {
            return -1;
        }
    }
    
    void put(int key, int value)
    {
        if(key_to_value.find(key) != key_to_value.end())
        {
            lru.erase(position[key]);
        }
        
        lru.push_front(key);
        position[key] = lru.begin();
        key_to_value[key] = value;
        
        if(lru.size() > capacity)
        {
            key_to_value.erase(lru.back());
            position.erase(lru.back());
            lru.pop_back();
        }
    }
};
```

---

## Find maximum of all subarrays of size k in O(n) time | Sliding Window Maximum
[Link](https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/)

**Solution Approach**
* Maintain a deque containing elements in **non-increasing order** for finding window maximum

```c++
vector<int>kMax(vector<int>&arr, int k)
{
    int n = arr.size();
    deque<int>dq;
  
    for(int i=0;i<k;i++)
    {
        while(!dq.empty() && arr[dq.back()] < arr[i])
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    
    vector<int>ans;
    ans.push_back(arr[dq.front()]);
    
    for(int i=k;i<n;i++)
    {
        int start = i-k+1;
        while(!dq.empty() && dq.front() < start)dq.pop_front();
        while(!dq.empty() && arr[dq.back()] < arr[i])
        {
            dq.pop_back();
        }
        dq.push_back(i);
        
        ans.push_back(arr[dq.front()]);
    }
    
    return ans;
}
```
---


