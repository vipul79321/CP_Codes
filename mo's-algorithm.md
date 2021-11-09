## Use Mo's Algorithm to answer Range Sum Queries
[Link](https://www.geeksforgeeks.org/mos-algorithm-query-square-root-decomposition-set-1-introduction/)

**Mo's Algorithm Description** - 
* It is an offline algorithm, that is we need to have queries known before-hand
* And hence it doesnt support update operation
* The idea of MO’s algorithm is to pre-process all queries so that result of one query can be used in next query

**Time complexity Analysis with n elements and m queries** - 
* First, we need to sort the queries depending on the block number in which L belongs to and inside that block sort the queries in ascending value of R. See code for more details
* Sorting take O(mlogm) time
* Now, while answering each query
  * Movement of R - Last query of previous block may put R in rightmost position and first query of current block may bring R to leftmost possible position. So, for each query where previous block is not same as current block R will have to travel `n` distance and count of such blocks is `sqrt(n)` and hence R will contribute `O(n * sqrt(n))`
  * Movement of L - For each query L may travel sqrt(n) distance. And hence L will contribute O(m * sqrt(n)) to time complexity
* Hence, total time complexity will be  - `O(mlogm + n * sqrt(n) + m * sqrt(n) ) == O( (m + n) * sqrt(n))`

```c++
int block_sz;

struct Query
{
    int L,R;
}

bool compare(Query &x, Query &y)
{
    if(x.L/block_sz == y.L/block_sz)
    {
        return x.R < y.R;
    }
    else
    {
        return x.L/block_sz < y.L/block_sz;
    }
}


int MoAlgorithm(vector<int> &arr, vector<Query> &queries)
{
    int n = arr.size();
    int block_sz = sqrt(n), i,j;
    
    sort(queries.begin(),queries.end(),comp);
    
    int L = 0, R = -1;
    int curr_sum = 0;
    
    for(auto q:queries)
    {
        while(R < q.R)
        {
            curr_sum += arr[R]; R++;
        }
        
        while(R > q.R)
        {
            curr_sum -= arr[R]; R--;
        }
        
        while(L < q.L)
        {
            curr_sum += arr[L]; L++;
        }
        
        while(L > q.L)
        {
            curr_sum -= arr[L]; L--;
        }
        
        ans.push_back(curr_sum);
    }
    return ans;
}
```
