## Longest Increasing Subsequence
[Link](https://cp-algorithms.com/sequences/longest_increasing_subsequence.html) | [Link](https://leetcode.com/problems/longest-increasing-subsequence/)

**Problem Description** - Given an array, print its lis in O(nlogn)

**Solution Description** - 
* First, we will obtain an normalized array so that each entry will be in range[1,n];
* Now, iterate over each i, and get maximum value and its index in range [0,normalize_nums[i] - 1]; (or [0,normalize_nums[i]] in case of non-decreasing subsequence)
* To get maximum value and index, we can maintain two Binary indexed tree, namely - max_bit and max_index_bit in code below;
* Now update both bits as **updating dp[i] at id == nums[i] and index = i(this will be used to retrieve LIS);** or update(nums[i],dp[i], i);
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

**Problem Description** - Given an array, we need to find the smallest number of non-decreasing subsequences which covers the whole array, that is, each entry should be present in exactly one of those subsequences.

**Solution Description** - 
* Return Length of LIS, refer CP-algo blog for proof.

### Use case - 2 - Number of longest increasing subsequences

**Problem Description** - Find number of ways to obtain LIS from given array.

**Solution Approach** - 
* We can use above coded approach with Segment tree instead of Fenwick Tree.
* Segment Tree will be like this - 
  * On querying it will return maximum in range[l,r] and its frequency in range[l,r]
  * It will have index update where will be add new_cnt if previous val is equal to new_val else simply replace previous freq with new_cnt.


