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
