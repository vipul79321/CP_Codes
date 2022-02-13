## Heap Implementation
[Link](https://www.geeksforgeeks.org/binary-heap/)

**minHeap class description** 
* `minHeap()` - Initializes an empty minHeap.
* `minHeap(vector<int> &v)` - Intializes a minHeap based on input vector.
* `buildHeap()` - Simply calls heapify for all nodes from last to first.
* `heapify(int i)` - Checks if given index and its child satisfy min-heap property, if not then it swap parent's value with smallest child's value and call heapify for that child
* `getMin()` - Simply returns heap[0];
* `extractMin()` - Returns heap[0], assign heap[0] = heap.back(); then heap.pop_back(); calls heapify(0);
* `parent(int i)` - Returns (i-1)/2;
* `left(int i)` - Returns 2 * i + 1;
* `right(int i)` - Returns 2 * i +2;
* `insert(int val)` - push_back val to heap. Now it checks whether it satisifies min-heap property with its parent, if not then swap parent and node value and keep on checking till parent exist.
* `decreaseKey(int i, int val)` - assign heap[i] = val; Now it checks whether it satisifies min-heap property with its parent, if not then swap parent and node value and keep on checking till parent exist.
* `increaseKey(int i, int val)` - we can simply call deleteKey(i) and then insert(val)
* `deleteKey(int i)` - calls decreaseKey(i, INT_MIN); then extractMin();

```c++
class minHeap
{
    private:
        vector<int>heap;
    public:
        minHeap() // Intializes an empty heap
        {
            heap.clear();
        }
        
        minHeap(vector<int>&v)  // Makes a heap from input vector
        {
            heap.clear();
            heap = v;
            buildHeap();
        }
        
        void buildHeap()
        {
            for(int i = heap.size()-1;i>=0;i--)
                heapify(i);
        }
        
        void heapify(int i)
        {
            if(i >= heap.size())return;
            
            int l = left(i), r = right(i);
            
            int smallest = i;
            
            if(l < heap.size() && heap[l] < heap[smallest])
            smallest = l;
            
            if(r < heap.size() && heap[r] < heap[smallest])
            smallest = r;
            
            if(smallest != i)
            {
                swap(heap[smallest],heap[i]);
                heapify(smallest);
            }
        }
        
        
        int getMin(){ return heap.size() ? heap[0] : INT_MIN; }
        
        int parent(int i){return (i-1)/2;}
        
        int left(int i){return 2*i+1;}
        
        int right(int i){return 2*i+2;}
        
        void insert(int key)
        {
            heap.push_back(key);
            int i = heap.size()-1;
            while(parent(i) >= 0 && heap[parent(i)] > heap[i])
            {
                swap(heap[i], heap[parent(i)]);
                i = parent(i);
            }
        }
        
        int extractMin()
        {
            if(heap.size() == 0)return INT_MIN;
            
            int val = heap[0];
            swap(heap[0],heap[heap.size()-1]);
            heap.pop_back();
            
            heapify(0);
            
            return val;
        }
        
        void decreaseKey(int i, int val)
        {
            heap[i] = val;
            while(parent(i) >= 0 && heap[parent(i)] > heap[i])
            {
                swap(heap[i], heap[parent(i)]);
                i = parent(i);
            }
        }
        
        void increaseKey(int i, int val)
        {
            deleteKey(i);
            insertKey(val);
        }
        
        void deleteKey(int i)
        {
            decreaseKey(i, INT_MIN);
            extractMin();
        }
};
```

---

## Time Complexity of Building Heap
[Link](https://www.geeksforgeeks.org/time-complexity-of-building-a-heap/)

* **Time Complexity of Building Heap from given vector is O(n)**
  * Proof - 
    * Since we call heapify for each index and heapify function takes O(height) time
    * And also we know that, there are `n/pow(2,h+1)` nodes at height h, lets call it f(h)
    * So total time complexity will be - `Summation( f(h) * O(h)` for all h = 0 to h = logn)
    * We can write above summation as - `n * Summation(h / pow(2,h) )` for all h = 0, to h = Infinity
    * Now the summation as become a sum of infinite Airthmetic GP and this summation evaluates to `2 * n`
    * Hence `O(n)`
* `O(logn)` for **Insert, delete, decreaseKey, increaseKey, extractMin**
* `O(1)` for **getMin**

---

## Tournament Tree - Minimum Comparisons Required to get Second Best element
[Link](https://www.geeksforgeeks.org/tournament-tree-and-binary-heap/)

* Think of given array elements as n player each having power arr[n]
* Now Imagine a tournament tree, i.e first we pair - up n players and make them compete, then in next round we will have n/2 player, we will keep doing this till there is only 1 player left
* Now this tournament tree represents a complete binary tree with n leaf nodes and hence it will have n-1 internal nodes and internal nodes represents a match
* So we need **n-1 matches** to find out the **best element**
* To find the second best element, we need to find best player from all the player which competed with our best element. It is equivalent to traversing along the height of tournament tree.
* Height of tournament tree will log2(n), but since at last level there are only leaf nodes, so we only need **log2(n) - 1** extra comparison to find second-best element
* In total we need **n-1 + log2(n)- 1** comparisons to find second best element

---

## Why is Binary Heap Preferred over BST for Priority Queue?
[Link](https://www.geeksforgeeks.org/why-is-binary-heap-preferred-over-bst-for-priority-queue/)

* Since Binary Heap is implemented using arrays, there is always better locality of reference and operations are more cache friendly.
* Although operations are of same time complexity, constants in Binary Search Tree are higher.
* We can build a Binary Heap in O(n) time. Self Balancing BSTs require O(nLogn) time to construct.
* Binary Heap doesn’t require extra space for pointers.
* Binary Heap is easier to implement.
* There are variations of Binary Heap like Fibonacci Heap that can support insert and decrease-key in Θ(1) time

**So when is BST used over Binary Heap** - 
* In BST searching O(logn) operation. In BST sorting can be done in O(n) by doing simple inorder traversal
* In BST, we can find `kth largest element in log(n) time`[Link](https://www.geeksforgeeks.org/find-k-th-smallest-element-in-bst-order-statistics-in-bst/). We need to BST node by maintaining count of nodes in left subtree of that node and right subtree of that node. And by depending on the value of k we can choose either to move in left subtree or right subtree.


---

## Kth smallest element in given array
[Heap based solution](https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/) | [Randomized Quickselect(similar to quicksort) solution](https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-2-expected-linear-time/) | [Median of Median QuickSelect solution](https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-3-worst-case-linear-time/)

**Heap Based Solution - O(nlogk)** - 
* Create a max - heap and insert first k elements into it.
* Now for any new element check if heap.top() > new_element then pop heap and push new_element into heap. Otherwise do nothing
* Finally after going through all the elements  - Return heap.top(); 

**Randomized QuickSelect Based solution - Worst case - O(n * n), Average Case - O(n)** - 
* See code below for details - 

```c++
int findKthSmallestElement(vector<int>&v, int l, int r, int k)
{
    if(k < 0 || r-l+1 < k || r < l)return INT_MAX;
    
    int len = (r-l+1);
    int pivot_index = rand()%len;
    int pivot = arr[pivot_index];
    swap(arr[pivot_index], arr[r]);
    
    int less_equal = l;
    
    for(int i=l;i<r;i++)
    {
        if(arr[i] <= pivot)
        {
            swap(arr[less_equal],arr[i]);
            less_equal++;
        }
    }
    swap(arr[less_equal],arr[r]); // since arr[r] is the pivot element
    
    int cnt_less_equal = less_equal - l + 1;
    
    if(cnt_less_equal == k)
      return arr[less_equal];
    else if(cnt_less_equal < k)
      return findKthSmallestElement(arr,less_equal+1,r,k-cnt_less_equal);
    else
      return findKthSmallestElement(arr,l,less_equal-1,k);
}
```


**Median of Median QuickSelect Based solution - O(n)** -
* Instead of randomly selecting pivot element as above, we divide our array into arrays of size 5 and from each partition of size 5 we obtain its median
* Now, we have median-of-median array, obtain its `size/2th` smallest element
* Now use the median of median-of-median array as pivot element
* Follow above steps till the desired partition is not reached

---

## Largest Derangement of a Sequence
[Link](https://www.geeksforgeeks.org/largest-derangement-sequence/)

**Solution Approach** - 
* Put all element in max - priority queue
* Now for each i from 0 to n - 1:
  * `val = pq.top(); pq.pop();`
  * if `val == arr[i] && i != n-1` then `ans[i] = pq.top(); pq.pop(); pq.push(val);`
  * else `ans[i] = val;`
* Finally check `if arr[n-1] == ans[n-1]` then `swap(ans[n-2],ans[n-1]);`
* Using similar logic we can find smallest derangement of a sequence

---

## Median of stream of running integers using STL 
[Link](https://www.geeksforgeeks.org/median-of-stream-of-running-integers-using-stl/) | [Link](https://www.geeksforgeeks.org/median-of-stream-of-integers-running-integers/) | [Atcoder submission link](https://atcoder.jp/contests/abc218/submissions/25792413)

**Solution Approach** - 
* Use Two multiset S & T, and maintain them such that `S.size() == T.size() || S.size() == T.size() + 1 and *S.rbegin() < *T.begin()`
* While inserting, insert element in `S` and call `balance()` function
* `findMedian()` - 
```c++
int findMedian()
{
    if(S.size() != T.size()+1)
    {
        auto itr = S.end();itr--;
        return (*itr + *T.begin())/2;
    }
    else
    {
        return *S.rbegin();
    }
}
```
* `balance()` - 
```c++
void balance()
{
    if(S.size())
    {
        auto itr = S.end();
        itr--;
 
        T.insert(*itr);
        S.erase(itr);
    }
 
    while(S.size() < T.size())
    {
        S.insert(*T.begin());
        T.erase(T.begin());
    }
}
```
* Utility function to support deletion - `erased(x)`
```c++
void erased(int x)
{
    if(S.size())
    {
        auto itr = S.end();itr--;
        if(*itr >= x)
            S.erase(S.lower_bound(x));
        else
            T.erase(T.lower_bound(x));
        
        balance();
    }
}
```









