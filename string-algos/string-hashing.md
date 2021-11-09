## String Hashing
[Link](https://cp-algorithms.com/string/string-hashing.html) | [Link](https://cp-algorithms.com/string/rabin-karp.html)
* Hashing is used to convert string into a number such that, `if s == t then hash(s) must be equal to hash(t)`. Please note, vice-versa may or may not be true.


**Polynomial Rolling Hash Function**
* A function of the following form is called Polynomial Rolling Hash Function

```math
hash(s) = s[0] + s[1] * p^2 + s[2] * p^3 ... s[n-1] * p^n-1 mod m
```

Where, p & m are both prime number. 

* Some standard choices for p & m in above function - 
  * p should be larger than number of alphabets in consideration, for e.g. - **31** if we are considering all lowercase only. If both lowercase and upper case then **53**. 
  * m should be a large prime number and at the same time, we should not encounter overflow while multiplication, so choices for m would be **m == 1e9+7**,  **m == 998244353**, **m == 1e8+7**

**Note** - 
* Its usually a good practice to compute two hash arrays with different set of p & m.
* **hash[j] - hash[i-1]**  is equal to **hash(s[i..j]) * pow_p[i]**.
* Now following scenarios arises when comparing hash for two different substrings - 
  * To get exact hash of s[i..j], we can do **(hash[j] - hash[i-1]) * modInverse(pow_p[i])**, and then compare them
  * We can also obtain **(hash[j] - hash[i-1] ) * pow_p[n-i-1]**, now all the hashed will be mutliplied by same power of p.


**Code Example** -
```c++
vector<long long>pow_p;

void fill_util(long long maxn, long long p, long long mod)
{
    pow_p.clear(); pow_p.resize(maxn);
    
    long long curr_pow = 1;
    for(int i=0;i<maxn;i++)
    {
        pow_p[i] = curr_pow%mod;
        curr_pow = (curr_pow*p)%mod;
    }
}

vector<long long> calculate_hash(string s, long long p, long long mod)
{
    int n = s.length();
    vector<long long>hash(n+1,0);
    
    for(int i=1;i<=n;i++)
    {
        long long x = s[i-1] - 'a';
        x = x+1;
        hash[i] = (hash[i] + (pow_p[i-1] * x)%mod )%mod;
        hash[i] = (hash[i] + hash[i-1])%mod;
    }
    
    return hash;
}

long long get_hash(int n, int l, int r, vector<long long>&hash) // l & r are 0-indexed. // Will return hash[s[l...r]] * pow_p[l];
{
    long long val =  (hash[r+1] - hash[l] + mod)%mod;
    return val;
}
```

## Use Cases

### Calculate number of unique substring - O(n^2 log(n))

**Solution Approach** - 
```c++
int ans = 0;
for(int len=1;len<=n;len++)
{
    set<long long>hs;
    for(int i=0;i<=n-len;i++)
    {
        hs.insert((get_hash(n,i,i+len-1,hash) * pow[n-i-1])%mod); // All the hash values are multiplied by same power of p which is pow_p[n-1];
    }
    ans = ans + hs.size();
}
return ans;
```

### String Matching
**Problem Description** 
* Given two string text and pat. We need to find the indexes of occurences of pat in text.

**Solution Approach** 
* Calculate hash array for text and obtain hash value for pattern.
* Now - 
```c++
int n = txt.size(), m = pat.size();
for(int i=0; i+m-1 < n;i++)
{
    if(get_hash(n, i, i+m-1, text_hash) == (hash_pat * pow_p[index])%mod) // Multiply hash_pat by pow_p[i], so that both hash value are multiplied by same power of p.
    {
        occurences.push_back(i);
    }
}
```
  
