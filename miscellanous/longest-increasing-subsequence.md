## Longest Increasing Subsequence
[Link](https://cp-algorithms.com/sequences/longest_increasing_subsequence.html) | [Link](https://leetcode.com/problems/longest-increasing-subsequence/)

**Problem Description** - Given an array, print its lis in O(nlogn)

**Solution Description** - 
* First, we will obtain an normalized array so that each entry will be in range[1,n];
* Now, iterate over each i, and get maximum value and its index in range [0,normalize_nums[i] - 1]; (or [0,normalize_nums[i]] in case of non-decreasing subsequence)
* To get maximum value and index, we can maintain two Binary indexed tree, namely - max_bit and max_index_bit in code below;
* Now update both bits as **update(id = normalize_num[i], val = dp[i], index = i);, index will be used to retrieve LIS**
* Update ans and end_of_lis according to dp[i];

See code below for more details - 
```c++
vector<int>max_bit, max_index_bit;
vector<int>parent,dp;

void update(int id, int val, int index, int n)
{
    id++;
    while(id <= n)
    {
        if(max_bit[id] < val)
        {
            max_bit[id] = val;
            max_index_bit[id] = index;
        }
        id += id&(-id);
    }
}

pair<int,int>get(int id)
{
    id++;
    int maxi = 0, index = -1;
    while(id > 0)
    {
        if(maxi < max_bit[id])
        {
            maxi = max_bit[id];
            index = max_index_bit[id];
        }
        id -= id&(-id);
    }
    
    return make_pair(maxi,index);
}


vector<int> normalize_vector(vector<int>&nums)
{
    map<int,int>val_to_index;
    for(auto a:nums)
    {
        val_to_index[a] = 1;
    }
    
    int curr = 1;
    for(auto it=val_to_index.begin();it!=val_to_index.end();it++)
    {
        it->second = curr;
        curr++;
    }
    
    vector<int>normalize_num(nums.size());
    
    for(int i=0;i<nums.size();i++)
    {
        normalize_num[i] = val_to_index[nums[i]];
    }

    return normalize_num;
}

vector<int> makeLIS(int index, vector<int>&nums)
{
    vector<int>lis;
    while(index != -1)
    {
        lis.push_back(nums[index]);
        index = parent[index];
    }
    
    reverse(lis.begin(),lis.end());
    
    return lis;
}


vector<int> computeLIS(vector<int>&nums)
{
    int n = nums.size();
    vector<int>normalize_num = normalize_vector(nums);  // normalize the given array
    
    max_bit.clear(); max_bit.resize(n+1,0);
    max_index_bit.clear(); max_index_bit.resize(n+1,0);
    dp.clear();dp.resize(n,0);
    parent.clear();parent.resize(n,-1);
    
    int end = -1, ans = 0;
    for(int i=0;i<n;i++)
    {
        pair<int,int>p = get(normalize_num[i] - 1);
        dp[i] = 1 + p.first;
        parent[i] = p.second;
        /*
        * Update at normalize_num[i] with value dp[i] and index = i;
        */
        
        update(normalize_num[i],dp[i],i,n);  /********************************** IMP STEP *************************/
        
        if(ans < dp[i])
        {
            ans = dp[i];
            end = i;
        }
    }
    
    return makeLIS(end,nums);
}
```


### Use Case - 1 - Smallest number of non-increasing subsequences covering the whole array

**Problem Description** - Given an array, we need to find the smallest number of non-increasing subsequences which covers the whole array, that is, each entry should be present in exactly one of those subsequences.

**Solution Description** - 
* Return Length of LIS, refer [CP-algo blog](https://cp-algorithms.com/sequences/longest_increasing_subsequence.html#toc-tgt-13) for proof.
* To Retrieve these non-increasing subsequences - 
  * The desired partition of the sequence into subsequences can be done greedily. 
  * go from left to right and assign the **current number(signifying start of new subsequence)** or **that subsequence number which ends with the minimal number which is greater than or equal to the current one(i.e select one of the existing subsequence whose last element is greater than current value and is minimum among all such candidates)**. 

### Use case - 2 - Number of longest increasing subsequences
[Link](https://leetcode.com/problems/number-of-longest-increasing-subsequence/)

**Problem Description** - Find number of ways to obtain LIS from given array.

**Solution Approach** - 
* We can use above coded approach with Segment tree instead of Fenwick Tree.
* Segment Tree will be like this - 
  * On querying it will return maximum in range[l,r] and its frequency in range[l,r]
  * It will have index update `pair(new_val,new_cnt)` where we will add new_cnt if previous_val is equal to new_val else simply replace with `pair(new_val,new_cnt)` if previous_val is less than new_val
* So solution will be like this - 
  * Loop from i = 0 to i = n:
    * dp[i].first will be length of LIS ending at ith index and dp[i].second will be count of such LIS 
    * `dp[i] = query(0, normalize_nums[i]-1)`
    * `update(normalize_nums[i], dp[i])`



