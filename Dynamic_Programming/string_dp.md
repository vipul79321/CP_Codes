## Longest Common Subsequence

```c++
// Finding LCS
for(i=1;i<=n;i++)
  for(j=0;j<=m;j++)
  {
     if(s[i-1] == t[j-1])lcs[i][j] = lcs[i-1][j-1] + 1;
     else
     lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]);
  }
```

```c++
// Print LCS
x = n, y = m;
ans = ""
while(x>0 && y>0)
{
    if(s[x-1] == t[y-1])
    {
       ans += s[x-1];
       x--,y--;
    }
    else if(lcs[x-1][y] > lcs[x][y-1])
          x--;
    else
          y--;
 }
 
 reverse(ans.begin(),ans.end())
 ```
 
 ## Longest Repeated Subsequence
 
 ```c++
 // Similar to finding LCS(s,s) such that i!=j
 for(i=1;i<=n;i++)
  for(j=0;j<=m;j++)
  {
     if(s[i-1] == t[j-1] && i!=j)lcs[i][j] = lcs[i-1][j-1] + 1;
     else
     lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]);
  }
 ```
 
 
