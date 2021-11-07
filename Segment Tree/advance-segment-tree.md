### Persistent Segment Tree
[Link](https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-12)

* A persistent data structure is a data structure that remembers it previous state for each modification
* Persistent segment tree is based on the idea that maximum logn nodes will be changed during a single update operation
* Instead of using array representation of segment tree, now we will have to use pointer representation of segment tree
```c++
struct vertex{
  vertex *l, *r;
  int sum;
  
  vertex(int val)
  {
      l = nullptr;
      r = nullptr;
      sum = val;
  }
  
  vertex(vertex *left, vertex *right)
  {
      l = left;
      r = right;
      sum = 0;
      if(l != nullptr)
        sum += left->sum;
      if(r != nullptr)
        sum += right->sum;
  }
  
};
```
