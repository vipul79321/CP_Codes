## Knuth Morris Prat String Matching Algorithm
[Link](https://cp-algorithms.com/string/prefix-function.html)

### Prefix Function
* Prefix function of a string is an array of `size == s.length()`, say prefix, where **prefix[i] is the length of longest proper prefix of substring s[0...i] which is also an suffix.**
* Proper prefix of string is any prefix which is not equal to that string.

```c++
vector<int> prefix_function(string s)
{
    int n = s.length();
    vector<int>prefix(n,0);
    int len = 0;
    
    for(int i=1;i<n;)
    {
        if(s[i] == s[len])
        {
            len++;
            prefix[i] = len;
            i++;
        }
        else if(len > 0)
        {
            len = prefix[len-1];
        }
        else
        {
            prefix[i] = 0;
            i++;
        }
    }
    
    return prefix;
}
```

### Use case - 1 - Pattern Matching | Count of occurences of pattern in the text
**Problem description** - Given a text and pattern, we need to find the number of times given pattern occurs in the text.

**Solution Description** - 
* Create a string `pattern + "#" + text`, and calculate its prefix function.
* Now loop for all index greater than pattern.length() and check if `prefix[i] == pattern.length()`, if equality holds then there is an occurence at `index = curr_index - (n + 1) - n + 1 in text`


### Use case - 2 - Number of occurences of each prefix of a string in that same string or in a given string
**Problem Description** - Given a string s, we need to count the occurences of each prefix s[0..i] in that string.

**Solution Approach** - 
* Compute prefix function for the given string. 
* Now, see this code - 
```c++
vector<int> prefix_count(string s)
{
    int n = s.length();
    vector<int>prefix = prefix_function(s);
    vector<int>ans(n+1,0);   // ans[i] represents number of occurences of prefix of length i.
    
    for(int i=0;i<n;i++)
      ans[prefix[i]]++;  // number of time prefix[i] occurs in prefix array.   ------ Step - 1
    
    for(int n-1;i>=0;i--) // since we know the occurence of prefix of length i, then we need to add this value to prefix[i-1]; ----- Step - 2
      ans[prefix[i-1]] = ans[prefix[i-1]] + ans[i];
     
    for(int i=0;i<=n;i++)
      ans[i]++; // include original prefixes in ans too. ----- Step - 3
    
    return ans;
}
```

**Another Variation** - 
* Given a string s and a string t, for each prefix s[0..i], we need to count its occurence in string t.

**Solution Approach** - 
* Create a string `s + "#" + t` and compute its prefix function. Now for updating ans in step-1(see code above) we will only consider indexes which belong to string t in our modified string.
* Step-2 will be same. Step-3 will be discarded.


### Use case - 3 - Number of distinct substring in a given string - O(n * n)

**Solution Approach** - 
* Let **cnt be the count of number of distinct substring in string s**.
* Now, lets append character `c` in string s. Now some new substrings will be formed, so we need to update count with number of new substrings formed which were not present earlier.
* For this we will create a string **t = s + c and reverse it** and will compute prefix function for string t.
* Let **max_pre** be the maximum value in the prefix array calculated above then updated cnt will be **cnt = cnt + |s| + 1 - max_pre**


### Use case - 4 - Check if string is made of repeated chunks and find smallest such chunk

**Solution Approach** - 
* Calculate prefix function for the given string. Let **`k = n - prefix[n-1]`. Now `if n%k == 0`, then prefix of length k is the smallest chunk which can be repeated to obtain the given string**


### Use case - 5 - Automaton - See blog itself.
