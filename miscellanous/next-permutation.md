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
