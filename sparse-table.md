## Sparse Table
[Link](https://cp-algorithms.com/data_structures/sparse-table.html)

**Introduction** - 
* Sparse Table is a data structure, that allows answering range queries. 
* It can answer most range queries in **O(logn)**.
* Its true power is answering **range minimum queries (or any idempotent queries e.g. range gcd)**. For those queries it can compute the answer in **O(1)** time.
* Precomputation time is **O(NlogN)**
* The only drawback of this data structure is, that it can only be used on **immutable arrays**.


**Building Sparse Table Code**

```c++
int st[MAXN][K+1]; // MAXN is max possible N and K is log2(n);

for(int i=0;i<N;i++)st[i][0] = f(array[i]);

for(int j=1;j<=k;j++)
{
    for(int i=0; i+(1<<j) <= N;i++)
    {
        st[i][j] = f(st[i][j-1] , st[i + (1<<(j-1))][j-1]);
    }
}
```

**Range Minimum Queries using Sparse Table** 
* Build Sparse table as above by replacing `f as an minimum function`. For this we need pre-compute value of `log2[i]` for every element in range [0,MAXN];
```c++
log2[1] = 0;
for(int i=2;i<=MAXN;i++)
  log2[i] = log2[i/2] + 1;
```
* For calculating range-minimum for [l,r] - 
```c++
int j = log2[r-l+1];
ans = min(st[l][j], st[r - (1<<j) + 1][j];
return ans;
```

**Range Sum Queries using Sparse Table** 
* Build Sparse table as above by replacing `f as addition function`.
* For calculating range-sum for [l,r]

```c++
int len = r-l+1;
int curr_start = l;
int sum = 0;
for(int i=K;i>=0 && len>0;i--)
{
    int curr_pow = 1<<i;
    
    if(curr_pow <= len)
    {
        sum += st[curr_start][curr_pow];
        curr_start = curr_start + curr_pow;
        len = len - curr_pow;
    }
}

return sum;
```
