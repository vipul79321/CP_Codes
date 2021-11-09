## Manacher's Algorithm - O(n)
**Problem Description** - Given a string s, find all sub-palindromes in O(n)

**Solution Description** - 
* For each index i, we will compute the count of odd and even palindromes containing ith element in center(by for even length by center we mean, latter of two centers)

**Algorithm Description for counting odd length palindromes** - 
* Intialize `l = 0, r = -1;`
* Intialize odd_pal_cnt[i] as follows - 
  * if `i <= r` then `odd_pal_cnt[i] = min(r-i+1, odd_pal_cnt[l + r-i]);`, as since index l + r - i will be mirror of index i in sub-palindrome [l,r]
  * else `odd_pal_cnt[i] = 1;`
* Now trivially try to increase odd_pal_cnt[i] as follows - 
  * `while(i-odd_pal_cnt[i] >= 0 && i + odd_pal_cnt < n && s[i-odd_pal_cnt[i]] == s[i + odd_pal_cnt[i]])`
    * odd_pal_cnt[i]++;
* Finally update l and r as follows - 
  * `if i + odd_pal_cnt[i] - 1 > r :`
    * `r = i + odd_pal_cnt[i] - 1, l = i - odd_pal_cnt[i] + 1;`

**Note** - If length of odd palindrome having center as i is `x` then `odd_pal_cnt[i] contains (x+1)/2`.

See code below - 
```c++
vector<int> get_odd_palindromes(string s)
{
    int n = s.length();
    vector<int>odd_pal_cnt(n,0);
    
    for(int i=0,l=0,r=-1; i<n; i++)
    {
        odd_pal_cnt[i] = i > r ? 1 : min(odd_pal_cnt[l + (r-i)], r-i+1);
        
        while(i-odd_pal_cnt[i] >= 0 && i + odd_pal_cnt[i] < n && s[i-odd_pal_cnt[i]] == s[i+odd_pal_cnt[i]])
            odd_pal_cnt[i]++;
            
        if(i + odd_pal_cnt[i] - 1 > r)
        {
            r = i + odd_pal_cnt[i] - 1;
            l = i - odd_pal_cnt[i] + 1;
        }
    }
    return odd_pal_cnt;
}
```

**Algorithm Description for counting even length palindromes** - 
* Intialize `l = 0, r = -1;`
* Intialize even_pal_cnt[i] as follows - 
  * if `i <= r` then `even_pal_cnt[i] = min(r-i+1, even_pal_cnt[l + r- i + 1]);`
  * else `even_pal_cnt[i] = 0;`
* Now trivially try to increase even_pal_cnt[i] as follows - 
  * `while(i-even_pal_cnt[i] - 1 >= 0 && i + even_pal_cnt[i] < n && s[i - even_pal_cnt[i] - 1]  == s[i + even_pal_cnt[i]])`
    * `even_pal_cnt[i]++;`
* Finally update l and r as follows - 
  * `if i + even_pal_cnt[i] -1 > r:`
    * `r = i + even_pal_cnt[i] - 1; l = i - even_pal_cnt[i];`

**Note** - If length of even palindrome having rightmost center as i is `x` then `even_pal_cnt[i] contains x/2`.

See code below - 
```c++
vector<int> get_even_palindromes(string s)
{
    int n = s.length();
    vector<int>even_pal_cnt(n,0);
    
    for(int i=0,l=0,r=-1; i<n; i++)
    {
        even_pal_cnt[i] = i > r ? 0 : min(even_pal_cnt[l + (r-i) + 1], r-i+1); // Imp ------Please note indexes
        
        while(i-even_pal_cnt[i]-1 >= 0 && i + even_pal_cnt[i] < n && s[i-even_pal_cnt[i]-1] == s[i+even_pal_cnt[i]])
            even_pal_cnt[i]++;
        
        if(i + even_pal_cnt[i] - 1 > r)
        {
            r = i + even_pal_cnt[i] - 1;
            l = i - even_pal_cnt[i];  // Imp ---- as i is later of two middle indexes in even length palindrome
        }
    }
}
```
