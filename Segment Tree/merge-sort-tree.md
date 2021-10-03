## Find kth smallest element in the given range [l,r]
[Link](https://www.geeksforgeeks.org/merge-sort-tree-for-range-order-statistics/)

**Solution Approach** - 
* First make an array with entries make_pair(arr[i],i) and sort it normally.
* Now we will make a merge-sort segment tree from above indexes( i.e. pair.second)
* How to ans queries
  * At each node of the segment tree, obtain count of indexes in range [L,R] in left-child. Let that count be m.
  * if m >= k then go to left child with same k
  * else go to right child with k = k - m


**See code below for more details** - 

```c++
struct Query
{
    int L,R,k;
}

vector<int>temp;
vector<vector<int> >st;

void build(int id, int l, int r)
{
    if(l==r)
    {
        st[id].push_back(temp[l].second);
        return;
    }
    
    int mid = (l+r)/2;
    
    build(2*id+1,l,mid); build(2*id+2,mid+1,r);
    
    merge(st[2*id+1].begin(),st[2*id+1].end(), 
          st[2*id+2].begin(),st[2*id+2].end(),
        back_inserter(st[id].begin()));
}

int get_cnt_in_range(int low, int high, int index)
{
    int end = upper_bound(st[index].begin(),st[index].end(),high) - st[index].begin();
    end--;
    int start = lower_bound(st[index].begin(),st[index].end(),low) - st[index].begin();
    
    return end - start + 1;
}

int getIndexofKthSmallest(int low, int high, int k, int id, int l, int r)
{
    if(l == r)return st[id][0];
    
    int mid = (l+r)/2
    int cnt_left_child = get_cnt_in_range(low,high,2*id+1);
    
    if(cnt_left_child >= k)
    {
        return getIndexofKthSmallest(low,high,k,2*id+1,l,mid);
    }
    else
    {
        return getIndexofKthSmallest(low,high,k-cnt_left_child,2*id+2,mid+1,r);
    }
}


void solveQueries(vector<int>&arr, vector<Query>&queries)
{
    int n = arr.size();
    st.clear(); st.resize(4*n);
    temp.clear();
    
    for(int i=0;i<n;i++)
    {
        temp.push_back(make_pair(arr[i],i));
    }
    
    sort(temp.begin(),temp.end());
    
    
    build(0,0,n-1);
    
    for(auto q:queries)
    {
        int ind = getIndexofKthSmallest(q.L,q.R,q.K,0,0,n-1);
        
        cout<<arr[ind]<<" ";
    }
}
```

---

## Find smallest number in range [l,r] which is greater than or equal to x
[Link](https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-9)

**Solution Description** - 
* Make a merge sort segment tree using the elements of the array.
* While querying for range [L,R] - 
  * simply, take minimum required value from all the st-nodes which lies completely in the range [L,R]
  * otherwise propagate further below
* See code below for more details.

**Note** - To allow point update in above problem use **multiset instead of vector**

```c++
struct Query
{
    int L,R,X;
}

vector<int>arr;
vector<vector<int> >st;

void build(int id, int l, int r)
{
    if(l==r)
    {
        st[id].push_back(arr[l]);
        return;
    }
    
    int mid = (l+r)/2;
    
    build(2*id+1,l,mid); build(2*id+2,mid+1,r);
    
    merge(st[2*id+1].begin(),st[2*id+1].end(), 
          st[2*id+2].begin(),st[2*id+2].end(),
        back_inserter(st[id].begin()));
}

int getSmallestDesiredElement(int low, int high, int x, int id, int l, int r)
{
    if(low > r || high < l)return INT_MAX;
    
    if(low <= l && r <= high)
    {
        int lb = lower_bound(st[id].begin(),st[id].end(),x) - st[id].begin();
        if(lb == st[id].size())return INT_MAX;
        else
        return st[id][lb];
    }
    
    int mid = (l+r)/2;
    return min(getSmallestDesiredElement(low,high,x,2*id+1,l,mid),
    getSmallestDesiredElement(low,high,x,2*id+2,mid+1,r));
}


void solveQueries(vector<Query>&queries)
{
    int n = arr.size();
    st.clear(); st.resize(4*n);
    
    build(0,0,n-1);
    
    for(auto q:queries)
    {
        int val = getSmallestDesiredElement(q.L,q.R,q.X,0,0,n-1);
        cout<<val<<" ";
    }
}
```
  
