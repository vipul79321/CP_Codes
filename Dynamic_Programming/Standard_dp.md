## Coin Change problem - 

```c++
n = target;
m = coins.size();
dp[n+1][m+1] = {0};
for(j=0;j<m;j++)dp[0][j] = 1;

for(i=1;i<=n;i++)
{
   for(j=1;j<=m;j++)
   {
      dp[i][j] = dp[i][j-1];
      if(coin[j-1] <= i)dp[i][j] += dp[i-coin[j-1]][j];
    }
 }
 ```
 
 ```c++
 // Memory efficient implementation
 n = target;
 m = coins.size();
 
 dp[n+1] = 0;
 dp[0] = 1;
 
 for(j=1;j<=m;j++)
 {
   for(i=coins[j-1];j<=n;j++)
   {
      dp[i] += dp[i-coins[j-1]];
   }
 }
  ```
---

## Subset Sum problem - 

```c++
dp[n+1][sum+1] = {0};

for(i=0;i<=n;i++)dp[i][0] = 1;

for(i=1;i<=n;i++)
{
   for(j=1;j<=sum;j++)
   {
      dp[i][j] = dp[i-1][j];
      if(j>=arr[i-1])dp[i][j] = dp[i][j] || dp[i-1][j-arr[i-1]];
   }
}

// Since we only need last row for dp transition we can reduce space complexity by making dp[2][sum+1] array and using curr and prev variables.
```
---

## Domino Tiling - Fill 3xN profile with 2x1 tile
[Link](https://www.geeksforgeeks.org/tiling-with-dominoes/)

---

## Maximum Games Played by winner - Good one. Have to think inversely.
[P.s Link](https://www.geeksforgeeks.org/maximum-games-played-winner/) - Given N players, output maximum number of games played by winner, with condition that two players are allowed to compete against one another if and only if difference between number of games played by them is <=1.

Hint - Think of minimum number of players required so that winner plays i games. dp[i] = dp[i] + dp[i-1]
```c++

dp[0] = 1;
dp[1] = 2;
i = 2;
while(1) {
   dp[i] = dp[i-1] + dp[i-2];
   if(dp[i] > n)return i-1;
}
```
---
## Maxium sum increasing subsequence from a prefix and a given element after prefix is must - [link](https://www.geeksforgeeks.org/maximum-sum-increasing-subsequence-from-a-prefix-and-a-given-element-after-prefix-is-must/)

## Maximum sum contiguous subarray - Kadane's algo 

```c++
   int start = 0,s,e;
   int max_so_far = INT_MIN;
   int curr = 0;
   
   for(i=0;i<n;i++)
   {
       curr += a[i];
       if(curr >= max_so_far)
       {
           s = start;
           e = i;
           max_so_far = curr;
       }
       if(curr < 0)
       {
           start = i+1;
           curr = 0;
       }
   }
   
   return e-s+1;
   ```
---
