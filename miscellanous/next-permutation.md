## Find next permutation for given array of integers. Array may contain repetitions
[Link](https://leetcode.com/problems/permutations-ii/) | [Link](https://leetcode.com/problems/next-permutation/)

**Solution Approach** - 
1. Find the **rightmost index** start such that `nums[start] < nums[start+1]`
2. Find the **rightmost index**, where `nums[start] < nums[min_index];`
3. swap `nums[start] and nums[min_index];`
4. Reverse `nums.begin() + start + 1, nums.end()` ;

```c++
class Solution {
public:
    
    bool isReverseSorted(vector<int>& v) { // Function to check whether there is any next permutation or not. Returns 1 if it is the greatest permutation
        if(v.size()==0)return 1;
        for(int i=1;i<v.size();i++) {
            if(v[i] <= v[i-1]) {
                continue;
            } else {
                return 0;
            }
        }
        return 1;
    }
    
    void next_perm(vector<int>&nums)
    {
        int n = nums.size();
        int i,j;
        int start = -1;
        
        for(i=n-1;i>0;i--) {
            if(nums[i] > nums[i-1]) {
                start = i-1;
                break; 
            }
        }
        
        int min_index = start + 1;
        for(i=n-1;i>=start+1;i--) {
            if(nums[i] > nums[start]) {
                min_index = i;
                break;
            }
        }

        swap(nums[start], nums[min_index]);
        reverse(nums.begin()+start+1, nums.end());
    }
    
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        
        vector<vector<int> >ans;
        sort(nums.begin(),nums.end());
        
        ans.push_back(nums);
        while(!isReverseSorted(nums))
        {
            next_perm(nums);
            ans.push_back(nums);
        }
        
        return ans;
        
    }
};
```

---

## Find the lexicographical next balanced sequence
[Link](https://cp-algorithms.com/combinatorics/bracket_sequences.html)
**Problem Description** - Given a balanced paranthesis sequence, find lexographically next balanced sequence

**Solution Approach** - 
* Loop from 0 to n, and maintain depth pointer.
* if s[i] == '(' then depth++; else depth--;
* Now find **rightmost index** such that `depth > 0 and s[index] == '('`
* Replace s[index] = ')'
* Now obtain the remaining number of open and close bracket.
* And fill the string s[index+1...n] with string(open,'(' ) + string(close,')') 


## Find All balanced sequences of size n
* Generate all the balanced sequences as mentioned above.

## Create a dp matrix to find count of all the sub-balanced bracket sequences of length 2 * n
```c++
int dp[2*n+2][2*n+2] = {0};

dp[0][0] = 1;
for(int i=1;i<=2*n;i++)
{
    for(int j=0;j<=2*n;j++)
    {
        if(j > 0)
        dp[i][j] += dp[i-1][j-1]; // putting open bracket
        if(j < 2 * n)
        dp[i][j] += dp[i-1][j+1]; // putting close bracket
    }
}
```

## Find the index of given balanced bracket sequence

**Problem Description** - Given a balanced bracket sequence, we need to find its index in lexographical ordering of all balanced paranthesis of size 2 * n.

**Solution Approach** - 
* Compute dp matrix as above
* Intialize depth = 0 , index = 0;
* Loop for i = 0 to i = 2 * n - 1:
  * if s[i] == ')'  `then index += dp[2 * n - (i+1)[depth + 1];` // Putting depth+1 signifies that we try to put opening bracket at i th index and obtain count of balanced expression possible from this state.  
  * Update depth as follows - if s[i] == '(' then depth++; else depth--;

**Note** - See blog to check how to deal with multiple bracket types

## Find kth balanced bracket sequence

**Solution Description** - 
* Compute dp matrix as above and initialize depth  = 0;
* Loop for i = 0 to 2 * n:
  * if `dp[2 * n - (i+1)][depth+1] <= k`: then put open bracket at ith index and depth++;
  * else `K -= dp[2 * n - (i+1)][depth+1];` and place close bracket at ith index and depth--;

```c++
string ans = "";
int depth = 0, K;
for(int i=0;i<2*n;i++)
{
    if(dp[2*n-(i+1)][depth+1] <=  K)
    {
        depth++;
        ans = ans + '(';
    }
    else
    {
        K -= dp[2*n - (i+1)][depth+1];
        depth--;
        ans = ans + '(';
    }
}
return ans;
```
