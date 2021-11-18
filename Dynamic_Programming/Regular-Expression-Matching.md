## Regular Expression Matching
[Link](https://leetcode.com/problems/regular-expression-matching/) | [Youtube Tutorial Link](https://www.youtube.com/watch?v=HAA8mgxlov8)

**Problem Description** - Given an input string txt and a pattern pat, implement regular expression matching with support for '.' and ' * ' where - 
* `' . '` -  Matches any single character.
* `' * '` -  Matches zero or more of the preceding element. i.e if a character is followed by * then it means it can appear any number of times(zero too).
* **NOTE** - `.*` means that `.` can be repeated zero or any number of times. Also there wont be two consecutive `*`

**Solution** - 
* We will implement a top-down memoization based dp solution. 
* `dp[i][j]` will represent if we can completely match str[i..n-1] & pat[j..m-1]
* See code below for dp transitions

```c++
bool dfs(int i,int j)
{
    if(i >= txt.length() && j >= pat.length())return 1;
    
    if(j >= pat.length())return 0;
    
    if(dp[i][j] != -1)return dp[i][j]; // already visited.
    
    
    bool match = 0; // A variable to store whether current corresponding characters match in pattern and text.
    if(i < txt.length() && (pat[j] == txt[i] || pat[j] == '.'))
        match = 1;
    
    if(j+1 < pat.length() && pat[j+1] == '*')
    {
        dp[i][j] = dfs(i,j+2); // By repeating current character 0 number of times and moving on to next character by skipping *
        if(match)
        // By repeating current character, and moving on to next character in text while staying on same character in pattern
            dp[i][j] = dp[i][j] | dfs(i+1,j); 
    }
    else if(match)
    {
        dp[i][j] = dfs(i+1,j+1); // Standard case.
    }
    else
    {
        dp[i][j] = 0; // No match then assign false value
    }
    
    return dp[i][j];
}
```


