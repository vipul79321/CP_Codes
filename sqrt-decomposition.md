## Square Root Decomposition
[Link](https://www.geeksforgeeks.org/sqrt-square-root-decomposition-technique-set-1-introduction/)

**Algorithm Description** - 
* The key concept of this technique is to decompose given array into small chunks specifically of size sqrt(n). And precompute answer for each chunk.
* Now while answering for query [L,R], we can directly ans for all the blocks completely inside the range and for partial overlapping case we can compute them brutely
* Hence the total time complexity will O(sqrt(n) + sqrt(n) + sqrt(n)) == O(sqrt(n)) for each query

**See code below for point and range-sum queries with updates using sqrt decomposition** - 

```c++
int block_sz;
vector<int>block_arr;

struct Query
{
    int L,R;
}

int getBlockIndex(int i)
{
    return i/block_sz;
}

void update(int index, int val)
{
    block_arr[getBlockIndex(index)] += val - arr[index];
    arr[index] = val;
}

int query(int L, int R)
{
    int sum = 0;
    
    while(l < r && l%block_sz != 0)
    {
        sum += arr[l];
        l++;
    }
    
    while(l + block_sz - 1 <= r)
    {
        sum += block_arr[getBlockIndex(l)];
        l += block_sz;
    }
    
    while(l <= r)
    {
        sum += arr[l];
        l++;
    }
    
    return sum;
}


void sqrtDecomposition(vector<int>&arr, vector<Query>&queries)
{
    int n = arr.size();
    int block_sz = sqrt(n);
    block_arr.clear();block_arr.resize(n/block_sz + 1, 0);
    
    
    for(int i=0;i<n;i++)
    {
        block_arr[getBlockIndex(i)] += arr[i];
    }
    
    for(auto q:Queries)
    {
        cout<<query(q.L,q.R)<<" "<<endl;
    }
    
}
```

---

**NOTE** - Heavy & Light Nodes
* Let G be a graph of N nodes and M edges
* Let S = sqrt(M)
* We can claim that at max. S number of nodes can have degree greater S, i.e S number of nodes can be heavy nodes
* Tutorial on this concept - 
  * [Errichto YT Link](https://www.youtube.com/watch?v=BJhzd_VG61k) | [Erricho CF Blog Link](https://codeforces.com/blog/entry/96713)
* Problems on this concept - 
  * Count number of Triangle in a graph in `O(Msqrt(M))` - [Link](https://youtu.be/BJhzd_VG61k?t=3832) 
  * [ABC G - Propogation](https://atcoder.jp/contests/abc219/tasks/abc219_g)

---

**NOTE** - If the sum of N numbers is S then there are at most `sqrt(S)` distinct values. This observation is majorly used in string-algorithms

---
