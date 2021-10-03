**Problem Description** - Given an array with following range queries - 
* query(l,r) - Returns xor of all the elements occuring even number of times in that range.

**Solution Description** - 
* Basic idea is to get xor of all even occuring elements, we will obtain xor of all the distinct elements in that and xor it with xor of all elements in that range.
* We will start by treating queries in **offline manner** and hence **sort them on the basis of R value then L value**.
* For answering queries, we will update curr_R to match with our current query's R - 
  * While updating R, `if last[arr[R]] != -1` then we will update value at `index = last[arr[R]] with arr[R]` - To cancel out the xor
  * Then we will udpate value at `index = R with arr[R]` - To maintain the latest occurence of arr[R] in our fenwick tree. And also do last[arr[R]] = R;
  * R++;
* Now to get XOR of all the distinct elements in our range [L,R], we will call following queries - 
  * `getXOR(query.R) ^ getXOR(query.L-1)`
* We will also maintain a prefix-xor array to get XOR of all the elements in range [L,R]
  * `prefix[query.R] ^ prefix[query.L-1]`
* Now our ans to this query will be -  `getXOR(query.R) ^ getXOR(query.L-1) ^ prefix[query.R] ^ prefix[query.L-1]`


**See code below for more details** - 

```c++
struct Query
{
    int L,R;
}

bool compare(Query &a, Query &b)
{
    if(a.R == b.R)
    {
        return a.L < b.L;
    }
    return a.R < b.R;
}

vector<int>bit;
int n;

void update(int id, int val)
{
    id++;
    while(id <= n)
    {
        bit[id] = bit[id] ^ val;
        id += id&(-id);
    }
}

void getXOR(int id)
{
    id++;
    int XOR = 0;
    while(id > 0)
    {
        XOR = XOR ^ bit[id];
        id -= id&(-id);
    }
    return XOR;
}


void solveQueries(vector<int>&arr, vector<Query>&queries)
{
    n = arr.size();
    bit.clear();bit.resize(n+1,-1);
    
    sort(queries.begin(),queries.end(),compare); // Note that queries are 0-indexed
    
    int curr_R = -1;
    map<int,int>last;
    
    vector<int>prefix_xor(n+1,0);
    for(int i=0;i<n;i++)
    {
        prefix_xor[i+1] = prefix_xor[i] ^ arr[i];
    }
    
    for(auto q:queries)
    {
        while(curr_R < q.R)
        {
            curr_R++;
            if(last[arr[curr_R]] != -1)
            {
                update(last[arr[curr_R]], arr[curr_R]);
            }
            update(curr_R, arr[curr_R]);
            last[arr[curr_R]] = curr_R;
        }
        
        int ans = 0;
        ans = ans ^ getXOR(q.R) ^ getXOR(q.L-1) ^ prefix_xor[q.R+1] ^ prefix_xor[q.L];
        cout<<ans<<" ";
    }
}
```
