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
 ---
 
 ## Longest Common Substring
 ```c++
 LCSuff[i][j] : Max length common suffix for S[0..i-1] & T[0..j-1]
 
 LCSuff[i][j] = LCSuff[i-1][j-1] + 1 if S[i-1] == T[j-1]
 LCSuff[i][j] = 0 otherwise
 
 Length of longest common substring between S & T == max(LCS[i][j])
 ```
 
 ---

## Longest Palindrome Subsequence
[Link](https://www.geeksforgeeks.org/longest-palindrome-subsequence-space/)
* Longest Palindrome subsequence can be thought as `Longest Common Subsequence between S and reverse(S)`
* Calculations
```c++
lps[n][n] = 0;
for(i=0;i<n;i++)lps[i][i] = 1;
for(i=0;i<n-1;i++)
{
    if(s[i] == s[i+1])lps[i][i+1] = 2;
}

for(int len=3;len<=n;len++)
{
    for(int i=0;i<=n-len;i++)
    {
        int j = i+len-1;
        if(s[i] == s[j])lps[i][j] = lps[i+1][j-1] + 1;
        
        lps[i][j] = max(lps[i][j],max(lps[i-1][j],lps[i][j-1]));
    }
}
return lps[0][n-1];
```
* Printing - Similar to LCS printing

* Counting
```c++
countLPS[n][n] = 0;
for(i=0;i<n;i++)countLPS[i][i] = 1;
for(i=0;i<n-1;i++)
{
    if(s[i] == s[i+1])countLPS[i][i+1] = 3;
}

for(int len=3;len<=n;len++)
{
    for(int i=0;i<=n-len;i++)
    {
        int j = i+len-1;
        if(s[i] == s[j])
        {
            countLPS[i][j] = countLPS[i][j-1] + countLPS[i+1][j] + 1;
        }
        else
        {
            countLPS[i][j] = countLPS[i][j-1] + countLPS[i+1][j] - countLPS[i+1][j-1];
        }
    }
}
```

---

## Longest Palindromic Substring
[Link](https://www.geeksforgeeks.org/longest-palindrome-substring-set-1/)
* Let dp[i][j] is 1 if substring (i,j) is palindrome else false
* Transitions - 
    * dp[i][j] = (s[i]==s[j]) & dp[i+1][j-1]

* Checking and Counting
```c++
isPalindromeSubstring[n][n] = 0;
countPalindromeSubstring[n][n] = 0;
for(i=0;i<n;i++)countPalindromeSubstring[i][i] = 1,isPalindromeSubstring[i][i] = 1;
for(i=0;i<n-1;i++)
{
    if(s[i] == s[i+1])countPalindromeSubstring[i][i+1] = 3,isPalindromeSubstring[i][i+1]=1;
}

for(int len=3;len<=n;len++)
{
    for(int i=0;i<=n-len;i++)
    {
        int j = i+len-1;
        if(s[i] == s[j] && isPalindromeSubstring[i+1][j-1] == 1)
        {
            isPalindromeSubstring[i][j] = 1;
            countPalindromeSubstring[i][j] = countPalindromeSubstring[i][j-1] + countPalindromeSubstring[i+1][j] + 1 - countPalindromeSubstring[i+1][j-1];
        }
        else
        {
            isPalindromeSubstring[i][j] = 0;
            countPalindromeSubstring[i][j] = countPalindromeSubstring[i][j-1] + countPalindromeSubstring[i+1][j] - countPalindromeSubstring[i+1][j-1];
        }
    }
}
```
