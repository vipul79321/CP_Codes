### Segment Tree
[Link](https://cp-algorithms.com/data_structures/segment_tree.html)

**Few Important Points** - 
* For using segment tree, we should be able to properly define merge function for two nodes
* **Build Time** - `O(n)`
* **Query Time** - `O(logn)` (assuming merging is O(1))
* **Space Complexity** - `O(4*n)`, `1 + 2 + 4 + .... 2^(logN) <= 2^(logN + 1) < 4*n`

**NOTE** - Memory efficient implementation of Segment Tree is based on the idea of Euler tour, 
* if parent index is id and represents range[l,r] 
* then left child will have `index = id+1` and represents range [l,mid]
* and right child will have `index = id + 2*(mid - l + 1)`
* So total space comes to `O(2*n)`

---

### Some standard queries
* Range-sum queries
* Range-max | Range-min queries
* Range-GCD | Range-LCM queries

---

### Range-Max queries and number of times it appears in that range
  * `st[node]` will have two attribute - `max` and `cnt`
  * merge will be like this
    * `if st[left].max  > st[right].max return st[left]`
    * `if st[right].max > st[left].max return st[right]`
    * `return new_node(st[left].max, st[left].cnt + st[right].cnt)`

---

### Searching for first array prefix with given sum | Finding smallest index of given cumulative frequency (assuming non-negative elements)
* Make range-sum segment tree
* call get_first(st_index = 0, l=0, r=n-1, target)
```c++
int get_first(int st_index, int l, int r, int target)
{
    if(st[st_index] < target) return -1;
    
    if(l == r)
    {
        if(st[st_index] == target) return l;
        else
        return -1;
    }
    
    int mid = (l+r)/2;
    
    if(st[2*st_index + 1] >= target)
      return get_first(2*st_index+1, l, mid, target);
    else
      return get_first(2*st_index+2, mid+1, r, target);
}
```
---

### Searching for first array element greater than given value in given range [low,high]

* Similar idea as above can be used here, but here range is given from low to high but above we were using full array
* call `get_first(low, high, st_index=0, l=0, r=n-1)`

```c++
int get_first(int low, int high, int st_index, int l, int r, int target)
{
    if(l>high || r < low)return -1;
    if(low<=l && r<=high)
    {
        if(st[st_index] <= target)return -1;
        
        while(l != r)
        {
            int mid = (l+r)/2;
            if(st[2*st_index+1] > x)
            {
                st_index = 2*st_index + 1;
                r = mid;
            }
            else
            {
                st_index = 2*st_index + 2;
                l = mid+1;
            }
        }
        return l;
    }
    int mid = (l+r)/2;
    int ans = get_first(low, high, 2*st_index+1, l, mid, target);
    if(ans != -1)return ans;
    return get_first(low, high, 2*st_index+2, mid+1, r, target);
}
``` 

---

### Finding subsegment with maximum sum in given range [l,r]

**Problem Description** - Given an array and range queries(l,r) we need to return maximum-sum subsegment (L,R) such that l<=L and R<=r

**Solution Description** - 
* Make a segment tree, whose node will have 4 attributes
  *  st_node.ans = ans for range represented by st_node
  *  st_node.pref = largest prefix sum of the range represented by st_node
  *  st_node.suff = largest suffix sum of the range represented by st_node
  *  st_node.sum = Total sum of range represented by st_node
* Using proper combine node function we can answer each query in O(logn)
* See code below for more details - 

```c++
struct data {
    int sum, pref, suff, ans;
};

data combine(data l, data r) {
    data res;
    res.sum = l.sum + r.sum;
    res.ans = res.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(res.ans,max(max(l.ans, r.ans), l.suff + r.pref));
    return res;
}

data make_data(int val) {
    data res;
    res.sum = val;
    res.pref = res.suff = res.ans = max(0, val);
    return res;
}

void build(int id, int l, int r)
{
    if(l==r)
    {
        st[id] = make_data(arr[l]);
        return;
    }
    int mid = (l+r)/2;
    build(2*id+1,l,mid);
    build(2*id+2,mid+1,r);
    st[id] = combine(st[2*id+1], st[2*id+2]);
}

void update(int index, int id, int l, int r, int new_val)
{
    if(l==r)
    {
        st[id] = make_data(new_val);
        arr[l] = new_val;
        return;
    }
    
    int mid = (l+r)/2;
    if(index<=mid)
        update(index,2*id+1,l,mid,new_val);
    else
        update(index,2*id+2,mid+1,r,new_val);

    st[id] = combine(st[2*id+1],st[2*id+2]);
}

data query(int low, int high, int id, int l, int r)
{
    if(l>high || r < low)return make_data(0);
    
    if(low<=l && r<=high)return st[id];
    
    int mid = (l+r)/2;
    data left = query(low,high,2*id+1,l,mid);
    data right = query(low,high,2*id+2,mid+1,r);
    return combine(left,right);
}
```

---

**NOTE** - 
* See this [link](https://github.com/vipul79321/CP_Codes/blob/main/Segment%20Tree/merge-sort-tree.md) for merge-sort segment tree
* Following queries can be answered using merge-sort segment tree
  * Find smallest number in range [l,r] which is greater than x
  * Find kth smallest element in range[l,r] 

---
