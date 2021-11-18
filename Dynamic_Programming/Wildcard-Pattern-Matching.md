## WildCard Pattern Matching - I
[Link](https://www.geeksforgeeks.org/wildcard-pattern-matching/) | [Link](https://leetcode.com/problems/wildcard-matching/) | [Youtube Tutorial Link](https://www.youtube.com/watch?v=NbgUZAoIz3g)

**Problem Description** - Given a string text and a string pattern, tell if it is possible to obtain given text from given pattern. Pattern may contain some special characters apart from alphabets - 
* `' ? '` - It can be replaced by any one alphabet
* `' * '` - Matches any sequence of characters (including the empty sequence).

**Solution** - 

* __Standard O(n^2) dp solution__ - 
    * Let `dp[i][j]` represents if txt[0..i-1] can be matched completely with pat[0..j-1]
    * See code below for transitions.

```c++
int n = txt.length();
int m = pat.length();

int dp[n+1][m+1];
memset(dp,0,sizeof(dp));
dp[0][0] = 1;
for(int j=1;j<=m;j++)
{
    if(pat[j-1] == '*')dp[0][j] = dp[0][j-1]; // '*' may match with an empty text, as it can be an empty sequence too.
}

for(int i=1;i<=n;i++)
{
    for(int j=1;j<=m;j++)
    {
        if(txt[i-1] == pat[j-1] || pat[j-1] == '?') // check if character matches or pat has '?'
        {
            dp[i][j] = dp[i-1][j-1];
        }
        else if(pat[j-1] == '*') // if pat[j-1] =='*' then two options arises either we ignore '*' or we use it to make txt[i-1]
        {
            dp[i][j] = dp[i][j-1] | dp[i-1][j];
        }
        else
            dp[i][j] = false;
    }
}
return dp[n][m];
```

* __Greedy Optimized almost O(n) solution with no extra space__ [Link](https://www.geeksforgeeks.org/dynamic-programming-wildcard-pattern-matching-linear-time-constant-space/)( see code)

```c++
int n = txt.length();
int m = pat.length();

if(m==0)
    return (n==0);

int index_txt = -1, index_pat = -1;
int i=0,j=0;

while(i < n)
{
    if(j<m && (txt[i] == pat[j] || pat[j] == '?')) // standard case
    {
        i++;
        j++;
    }
    /*
    * if pat[j] == '*' store the corresponding index in text and pat in index_txt & index_pat respectively.
    * and increment j(signaling we are trying by ignoring '*')
    */
    else if(pat[j] == '*')
    {
        index_txt = i;
        index_pat = j;
        j++;
    }
    /*
    * If index_pat != -1 then we know that we need to revert back to index_txt & index_pat.
    * Also this time we know that we cant ignore '*' and have to use it with index_txt.
    * We will still keep index_pat as same.
    */
    else if(index_pat != -1)
    {
        i = index_txt + 1;
        j = index_pat + 1;
        index_txt++;
    }
    else
    {
        return false;
    }
}

while(j<m && pat[j] == '*')j++;

return (j==m);
```

---

## WildCard Patter Matching - II
[Link](https://www.geeksforgeeks.org/wildcard-pattern-matching-three-symbols/)

**Problem Description** - Completely similar to above problem, but pattern contains one extra type of special character '+'
* `" + "` - Matches previous single character of pattern, i.e value used by previous character during matching.

**Solution**
* To deal with **`+`**, we will create a dp table which alongwith boolean value also store the character used during that matching. See code for more details - 

```c++

if (m == 0)
    return (n == 0);

// If first character of pattern is '+'
if (pattern[0] == '+')
    return false;

// lookup table for storing results of
// subproblems
struct DP lookup[m + 1][n + 1];

// initialize lookup table to false
for (int i = 0; i <= m; i++)
    for (int j = 0; j <= n; j++) {
        lookup[i][j].value = false; 
        lookup[i][j].ch = ' '; 
    }  
       
// empty pattern can match with
// empty string
lookup[0][0].value = true;

// Only '*' can match with empty string
for (int j = 1; j <= n; j++)
    if (pattern[j - 1] == '*')
        lookup[j][0].value = 
               lookup[j - 1][0].value;

// fill the table in bottom-up fashion
for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {

        // Two cases if we see a '*'
        // a) We ignore ‘*’ character and move
        // to next character in the pattern,
        // i.e., ‘*’ indicates an empty sequence.
        // b) '*' character matches with ith
        // character in input
        if (pattern[i - 1] == '*') {
            lookup[i][j].value = lookup[i][j - 1].value || lookup[i - 1][j].value;
            lookup[i][j].ch = str[j - 1];
        }

        // Current characters are considered as
        // matching in two cases
        // (a) current character of pattern is '?'
        else if (pattern[i - 1] == '?') {
            lookup[i][j].value = lookup[i - 1][j - 1].value;
            lookup[i][j].ch = str[j - 1];
        }

        // (b) characters actually match
        else if (str[j - 1] == pattern[i - 1]) {
            lookup[i][j].value = lookup[i - 1][j - 1].value;
            if(lookup[i][j].value)
                lookup[i][j].ch = str[j-1];
        }
            
        // Current character match
        else if (pattern[i - 1] == '+')

            // case 1: if previous character is not symbol
            if (pattern[i - 2] != '+' && pattern[i - 2] != '*' && pattern[i - 2] != '?')
                if (pattern[i - 2] == str[j - 1]) {
                    lookup[i][j].value = lookup[i - 1][j - 1].value;
                    lookup[i][j].ch = str[j - 1];
                }

                // case 2 : if previous character 
                // is symbol (+, *, ? ) then we 
                // compare current text character 
                // with the character that is used by
                // the symbol  at that point. we 
                // access it by lookup[i-1][j-1]
                else if (str[j-1] == lookup[i-1][j-1].ch) {
                    lookup[i][j].value = lookup[i - 1][j - 1].value;
                    lookup[i][j].ch = lookup[i - 1][j - 1].ch;
                }

                // If characters don't match
                else
                    lookup[i][j].value = false;
    }
}

return lookup[m][n].value;
```


