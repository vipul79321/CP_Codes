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
