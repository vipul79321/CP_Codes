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

* Build function will be as follow - 
```c++
vertex* build(int l, int r)
{
    if(l==r)
    {
        return new vertex(arr[l]);
    }
    int mid = (l+r)/2;
    return new vertex(build(l,mid), build(mid+1,r));
}
```

* update function will be as follows - 
```c++
vertex* update(int index, int new_val, vertex *curr int l, int r)
{
    if(l==r)
    {
        arr[l] = new_val;
        return new vertex(new_val);
    }
    int mid = (l+r)/2;
    if(mid>=index)
    {
        return new vertex(update(index, new_val, l, mid), curr->right);
    }
    else
    {
        return new vertex(curr->left, update(index, new_val, mid+1,r));
    }
}
```

* get_sum function will look like this - 
```c++
int get_sum(int low, int high, vertex *curr, int l, int r)
{
    if(l>high || r<low)return 0;
    if(low<=l && r<=high)return curr->sum;
    
    int mid = (l+r)/2;
    return get_sum(low,high,curr->left,l,mid) + get_sum(low,high,curr->right,mid+1,r);
}
```

---

### Implicit Segment Tree
[Link](https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-13)

* Idea of implicit segment tree is we make segment tree on demand, i.e we dont make the whole segment tree we just make the node as they come in use 

```c++
struct Vertex {
    int left, right; // left boundary and right boundary
    int sum = 0;
    Vertex *left_child = nullptr, *right_child = nullptr;

    Vertex(int lb, int rb) {
        left = lb;
        right = rb;
    }

    void extend() {
        if (!left_child && left + 1 < right) {
            int t = (left + right) / 2;
            left_child = new Vertex(left, t);
            right_child = new Vertex(t, right);
        }
    }

    void add(int k, int x) {
        extend();
        sum += x;
        if (left_child) {
            if (k < left_child->right)
                left_child->add(k, x);
            else
                right_child->add(k, x);
        }
    }

    int get_sum(int lq, int rq) {
        if (lq <= left && right <= rq)
            return sum;
        if (max(left, lq) >= min(right, rq))
            return 0;
        extend();
        return left_child->get_sum(lq, rq) + right_child->get_sum(lq, rq);
    }
};
```

