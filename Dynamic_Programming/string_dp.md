### Longest Common Subsequence - Calculation and Printing
[Link](https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/)

* **Calculation**
```c++
int lcs[n+1][m+1] = {0};
// Finding LCS
for(i=1;i<=n;i++)
  for(j=1;j<=m;j++)
  {
     if(s[i-1] == t[j-1])lcs[i][j] = lcs[i-1][j-1] + 1;
     else
     lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]);
  }
```
---

* **Printing**
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
 ---
 
 * **Print all LCS in lexographical order**
 [Link](https://www.geeksforgeeks.org/print-longest-common-sub-sequences-lexicographical-order/)
 
   * Make lcs matrix where `lcs[i][j]` is length of longest common subsequence in s[i..n-1] and t[j..m-1]. 
   * Loop for char from 'a' to 'z' 
     * Find occurence of that char in both strings and check if LCS is possible from there
     * See code below for more details
```c++
lcslen = lcs[0][0];

void printAll(string s, string t,
              char[] curr, int currlen,
              int index_s, int index_t)
{
    // if currlcs is equal to lcslen then print it
    if (currlen == lcs[0][0])
    {
        data[currlcs] = '\0';
        puts(data);
        return;
    }
 
    // if we are done with all the characters of both string
    if (index_s==s.length() || index_t==t.length())
        return;
 
    // here we have to print all sub-sequences lexicographically,
    // that's why we start from 'a'to'z' try to put this 
    // character at position currlen in data by checking if we can get LCS by doing that
    for (char ch='a'; ch<='z'; ch++)
    {
        // done is a flag to tell that we have printed all the
        // subsequences corresponding to current character
        bool done = false;
 
        for (int i=index_s; i<s.length(); i++)
        {
            // if character ch is present in s then check if it is present in t
            if (ch==s[i])
            {
              for (int j=index_t; j<t.length(); j++)
              {
                // if ch is present in both of them and
                // remaining length is equal to remaining
                // lcs length then add ch in sub-sequenece
                if (ch==t[j] && lcs[i][j] == lcslen-currlen)
                {
                  data[currlcs] = ch;
                  printAll(s, t, data, currlen+1, i+1, j+1,);
                  done = true;
                  break;
                }
              }
            }
 
            // If we found LCS beginning with current character.
            if (done)
                break;
        }
    }
}

```

---

 ### Longest Repeated Subsequence
 [Link](https://www.geeksforgeeks.org/longest-repeated-subsequence/)

* Find LCS(s,s) such that there should be no common index in lcs

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
 
 ### Longest Common Substring
 [Link](https://www.geeksforgeeks.org/longest-common-substring-dp-29/)
 
 ```c++
 LCSuff[i][j] : Max length common suffix for S[0..i-1] & T[0..j-1]
 
 LCSuff[i][j] = LCSuff[i-1][j-1] + 1 if S[i-1] == T[j-1]
 LCSuff[i][j] = 0 otherwise
 
 Length of longest common substring between S & T == max(LCS[i][j])
 ```
 
 ---

### Longest Palindrome Subsequence - Calculation & Printing and Counting
[Link](https://www.geeksforgeeks.org/longest-palindrome-subsequence-space/)

* Longest Palindrome subsequence can also be thought as `Longest Common Subsequence between S and reverse(S)`

**Calculations**
```c++
lps[n][n] = 0; // lps[i][j] represents length of longest common palindromic subsequence of s[i..j]
for(i=0;i<n;i++)lps[i][i] = 1;
for(i=0;i<n-1;i++) {
    if(s[i] == s[i+1])lps[i][i+1] = 2;
}

for(int len=3;len<=n;len++) {
    for(int i=0;i<=n-len;i++) {
        int j = i+len-1;
        if(s[i] == s[j])lps[i][j] = lps[i+1][j-1] + 1;
        
        lps[i][j] = max(lps[i][j],max(lps[i-1][j],lps[i][j-1]));
    }
}
return lps[0][n-1];
```
---

* **Printing** - 
  * Similar to LCS printing
  * Obtain LCS between S and reverse(S) and print it. 

---

* **Counting**
```c++
countLPS[n][n] = 0;
for(i=0;i<n;i++)countLPS[i][i] = 1;
for(i=0;i<n-1;i++) {
    if(s[i] == s[i+1])countLPS[i][i+1] = 3;
}

for(int len=3;len<=n;len++) {
    for(int i=0;i<=n-len;i++) {
        int j = i+len-1;
        if(s[i] == s[j]) {
            countLPS[i][j] = countLPS[i][j-1] + countLPS[i+1][j] + 1;
        }
        else {
            countLPS[i][j] = countLPS[i][j-1] + countLPS[i+1][j] - countLPS[i+1][j-1];
        }
    }
}
```

---

### Longest Palindromic Substring - Calculation & Counting
[Link](https://www.geeksforgeeks.org/longest-palindrome-substring-set-1/)

* Let `isPalindromeSubstring[i][j]` is 1 if substring (i,j) is palindrome else false
* Transitions - 
    * `isPalindromeSubstring[i][j] = (s[i]==s[j]) & isPalindromeSubstring[i+1][j-1]`

* **Checking and Counting**
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

---

### Shortest Common Supersequence
[Link](https://www.geeksforgeeks.org/shortest-common-supersequence/) | [Link](https://www.geeksforgeeks.org/shortest-possible-combination-two-strings/) | [Link](https://www.geeksforgeeks.org/print-shortest-common-supersequence/)

* `Length of Shortest Common Supersequence = str1.length() + str2.length() - LCSlen(str1,str2)`
* Another DP transition can be
    * Let `scs[i][j] = Length of SCS for str1[1...i] & str2[1..j]`
    * if `str1[i] == str2[j]` then `scs[i][j] = dp[i-1][j-1] + 1;`
    * else `scs[i][j] = min(1 + scs[i-1][j], 1 + scs[i][j-1]);`
* See code below for more details

**Finding SCS Length**
```c++
int scs[n+1][m+1];

for(int i=1;i<=n;i++)scs[0][i] = i;
for(int i=1;i<=m;i++)scs[i][0] = i;

scs[0][0] = 0;

for(int i=0;i<=n;i++)
{
    for(int j=0;j<=m;j++)
    {
        if(i==0) {
            scs[i][j] = j;
        }
        else if(j==0) {
            scs[i][j] = i;
        }
        else if(s1[i-1] == s2[j-1]) {
            scs[i][j] = 1 + scs[i-1][j-1];
        }
        else {
            scs[i][j] = min(1 + scs[i-1][j], 1 + scs[i][j-1]);
        }
    }
}

```

**Printing SCS**
```c++
i = n, j = m;
while(i > 0 && j > 0)
{
    if(str1[i-1] == str2[j-1]) {
        ans.push_back(str1[i-1]);
        i--,j--;
    }
    else if(scs[i][j-1] > scs[i-1][j]) {
        ans.push_back(str1[i-1]);
        i--;
    }
    else {
        ans.push_back(str2[j-1]);
        j--;
    }
}

while(i > 0) {
    ans.push_back(str1[i-1]);
    i--;
}

while(j > 0) {
    ans.push_back(str2[j-1]);
    j--;
}

reverse(ans.begin(),ans.end());
return ans;
```

---

### Shortest Uncommon subsequence 
[Link](https://www.geeksforgeeks.org/shortest-uncommon-subsequence/)

**Problem Description** - Given two string S and T find length of shortest subsequence of S which is not a subsequence of T

**Solution Approach** - 
* create a matrix `sus[n+1][m+1]`, where `sus[i][j]` represents length of sus between `S[0..i-1] and T[0..j-1]`
* Intialize all the entries of sus as Infinity
* Transitions - 
  * `sus[i][0] = 1;` for i = [0,n]
  * For sus[i][j] 
    * let k **rightmost index** such that `0<=k<=j-1` and `T[k-1] == S[i-1]`
    * if `k == -1` then `sus[i][j] = 1` as `S[i-1]` is not present in `T[0..j-1]`
    * else `sus[i][j] = min(sus[i-1][j], 1 + sus[i-1][(k-1) + 1])`


```c++
// Intialize as inf
int sus[n+1][m+1] = {inf};

// if T is empty
for(i=1;i<=n;i++)sus[i][0] = 1;

for(int i=1;i<=n;i++) //considering s[0..i-1]
{
    for(int j=1;j<=m;j++) //considering t[0..j-1]
    {
        for(int k=j-1;k>=0;k--) // check for occurence of s[i-1] in t[0..j-1]
        {
            if(s[i-1] == t[k])
            break;
        }
        if(k==-1)sus[i][j] = 1;  // if s[i-1] not found then s[i-1] is the sus itself
        else
        // if found we can either ignore s[i-1]
        // or we can add it in our sus and check for s[0..i-1] & t[0..k-1]
        sus[i][j] = min(sus[i-1][j], 1 + sus[i-1][(k-1) + 1]); // since we founded it on index k
    }
}
return sus[n][m];
```

---

### Count Distinct Subsequences
[Link](https://www.geeksforgeeks.org/count-distinct-subsequences/)

```c++
int prev[26] = {-1};

int count[n+1] = {0};
count[0] = 1; // empty subsequence
for(int i=1;i<=n;i++)
{
    // simply add previous subsequences and subsequences ending at i-1
    count[i] = 2*count[i-1];
    if(prev[s[i-1]-'a'] != -1) {
        // remove duplicate subsequences which were ending at previous occurence of same character.
        count[i] -= count[prev[s[i-1]-'a' - 1];
    }
    prev[s[i-1]-'a'] = i;
}
```

---

### Count distinct occurences as subsequences
[Link](https://www.geeksforgeeks.org/count-distinct-occurrences-as-a-subsequence/)
* `dp[i][j]` = Number of occurences of t[0..j-1] in s[0..i-1]
* Transitions - 
    * `dp[i][j] = dp[i-1][j] if s[i-1] != t[j-1];`
    * `dp[i][j] = dp[i-1][j] + dp[i-1][j-1] if s[i-1] == t[j-1]`

---

### Minimum Insertions to form a palindrome
[Link](https://www.geeksforgeeks.org/minimum-insertions-to-form-a-palindrome-dp-28/)

```c++
if (s[i] == s[j])
dp[i][j] = dp[i+1][j-1]
else
dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
```

---

### Minimum steps to delete the string after repeated deletion of palindromic substrings
[Link](https://www.geeksforgeeks.org/minimum-steps-to-delete-a-string-after-repeated-deletion-of-palindrome-substrings/)

* Let `dp[i][j]` be the minimum steps required to delete the string s[i..j]
* Following dp transition will arise
    * Simple deletion - `dp[i][j] = min(dp[i][j], 1+dp[i+1][j])`
    * Deleting alongwith s[i+1..k-1] - `dp[i][j] = min(dp[i][j], dp[i+1][k-1] + dp[k+1][j])` where `i+1<k<j && s[i] == s[k]`
    * Deleting alongwith s[k+1..j-1] - `dp[i][j] = min(dp[i][j], dp[i][k-1] + dp[k+1][j-1])` where `i<k<j-1 && s[j] == s[k]`
    * `if s[i] == s[i+1]` then `dp[i][j] = min(dp[i][j], 1 + dp[i+2][j]);`
    * `if s[j-1] == s[j]` then `dp[i][j] = min(dp[i][j], 1 + dp[i][j-2]);`
    * Standard Transitions - `dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);`
    * if `s[i] == s[j]` then `dp[i][j] = min(dp[i][j], dp[i+1][j-1])`

---

### Longest repeating and non-overlapping substring
[Link](https://www.geeksforgeeks.org/longest-repeating-and-non-overlapping-substring/)

* Let `LCSRe[i][j]` stores length of the matching and non-overlapping substrings ending with i'th and j'th characters.
* Transitions - 
  *  Loop for i from 1 to n
    * Loop for j from i+1 to n 
      * `if (s[i-1] == s[j-1]) && (j-i) > LCSRe[i-1][j-1]` then `LCSRe[i][j] = 1 + LCSRe[i-1][j-1];`
      * else if `(s[i-1] == s[j-1] &&(j-i) > LCSRe[i-1][j-1])` then `LCSRe[i][j] = (j-i)`
      * else `LCSRe[i][j] = 0;`
* Ans will be `max(LCSRe[i][j]);`


