## Z-algorithm - Introduction
[Link](https://cp-algorithms.com/string/z-function.html)
* The Z-function for a string is an array of length n where the i-th element is equal to the greatest number of characters starting from the position i that coincide with the first characters of s
* In other words, z[i] is the length of the longest common prefix between s and the suffix of s starting at i.
* Time and Space Complexity for Z-function = O(n)

### Use case - 1 - Pattern Matching
* Pattern matching - Given text and pattern string, find number of times pattern appear in text.
* Solution - compute z-function for pat + "$" + text, ans will be count of indexes such that z[i] == pat.length();
* Time & Space complexity - O(text.length() + pattern.length())

### Use case - 2 - String Compression
* String Compression - Given a string, find a string t of shortest length such that s can be represented as a concatenation of one or more copies of t.
* Solution -
  * Compute z-function of given string.
  * Iterate through all the indexes such that n%index == 0, ans will be first such index where, index + z[index] == n;
* Time & Space Complexity - O(n)

### Use case - 3 - Number of Distinct Substring in a given string
* Number of Distinct substring in a given string
* Solution -
  * Suppose we know, number of distinct substring till index i, say k.
  * Now for i+1 index, we want to know how many new substring ends at i+1 th index.
  * To solve above, make new string t = s(0..i+1) and reverse t. Compute z-function for t.
  * Now ans for above will be t.length() - zmax. zmax will represent, how many prefix of t occur somewhere in middle of t and hence not unique.
* Time Complexity = O(n^2) , Space complexity = O(n)


```c++
#include<bits/stdc++.h>
using namespace std;

vector<int> z_function(string s)
{
    int n = s.length();
    vector<int>z(n,0);

    int l=0,r=0;
    int i;
    for(i=1;i<n;i++)
    {
        if(i <= r)
          z[i] = min(r-i+1, z[i-l]);  // since we already know that s[0..r-l] == s[l..r], so we can say that z[i] == z[i-l] (if possible)

        while(i+z[i] < n && s[z[i]] == s[i+z[i]])  // Trivially checking further.
          z[i]++;

        if(i + z[i] - 1 > r)  // update l,r
        {
            l = i;
            r = i+z[i]-1;
        }
    }
    return z;
}


void solve(int test)
{
   string text,pat;
   cin>>text>>pat;

   string temp = pat + "+" + text;
   vector<int>z = z_function(temp);
  
   int cnt = 0;
   for(int i=pat.length()+1; i<temp.length();i++)
   {
       if(z[i] == pat.length())cnt++;
   }
   cout<<cnt<<endl;
}

int main()
{
  int t = 1;
  cin>>t;
  for(int x=1;x<=t;x++)
  {
      solve(x);
  }
  return 0;
}

/*
1
GEEKSFORGEEKS
GEEKS
*/

```
