### Inplace Right rotate the given array in O(n) time
[Link](https://www.geeksforgeeks.org/reversal-algorithm-right-rotation-array/)

**Solution Approach for right rotation by d** - 
* reverse arr[0...n-1]
* reverse arr[0...d-1]
* reverse arr[d...n-1]

---

### Find the smallest positive integer value that cannot be represented as sum of any subset of a given array
[Link](https://www.geeksforgeeks.org/find-smallest-value-represented-sum-subset-given-array/)

**Solution Approach** - 
* Sort the given array
* Let `res` represents the smallest element that cannot be obtained from elements till now.
* Now for the current element two scenario happens if `arr[i] <= res` then we simply need to update `res = res + arr[i]`
* else return `res`

```c++
int findSmallest(vector<int>&arr, int n)
{
   int res = 1; // Initialize result
   for (int i = 0; i < n && arr[i] <= res; i++)
       res = res + arr[i];
 
   return res;
}
```
---

### Find the two repeating elements in a given array of size n+2 where elements are in range [1,n]
[Link](https://www.geeksforgeeks.org/find-the-two-repeating-elements-in-a-given-array/)

**Problem Description** - Given an array of size n+2, containing all the element from 1 to n. All the elements occur once except two elements which occur twice

**Solution Approach by XOR** -
* Let all_xor represents xor all numbers in range 1 to n, xor_arr represents xor of all array elements
* Now, x_xor_y = all_xor ^ xor_arr
* Now obtain rightmost set bit in x_xor_y as `rsb = x_xor_y&(-x_xor_y)`
* Now intialize x =  0, and y = 0
* Now loop for each element in arr and `if(arr[i] & rsb)` then `x = x ^ arr[i];` else `y = y ^ arr[i];`
* Now loop for each element in range 1..n, `if(i & rsb)` then `x = x ^ i;` else `y = y ^ i;`

**Solution using marking indexes as visited by making value at them negative** - 

```c++
for(int i=0;i<n+2;i++)
{
    if(arr[abs(arr[i])] > 0)
      arr[abs(arr[i])] = -arr[abs(arr[i])];
    else
      cout<<abs(arr[i])<<" ";
}
```

---

### K-maximum sum of overlapping contiguous subarrays in O(nk)
[Link](https://www.geeksforgeeks.org/k-maximum-sum-overlapping-contiguous-sub-arrays/)

**Solution Approach** - 
* Maintain a multiset containing k smallest prefix-sums till now
* Maintain a max-heap of size k
* At every index, loop through each smallest prefix-sums in the multiset till now and try to insert `curr_prefix_sum - smallest_prefix_sum_till_now` in max-heap.

---

### k-th smallest absolute difference of two elements in an array
[Link](https://www.geeksforgeeks.org/k-th-smallest-absolute-difference-two-elements-array/)

**Solution Approach** - 
* Sort the given array and obtain low = min(arr[i] - arr[i-1] for all i) and high = arr[n-1] - arr[0];
* Now apply binary search and check how many pairs have distance less than equal to mid and move accordingly
* To check how many pairs have distance less than equal to mid use `upper_bound`

---

### Number of subsets with product less than k in O(n * pow(2,n/2))
[Link](https://www.geeksforgeeks.org/number-subsets-product-less-k/)

**Solution Approach meet in the middle** - 
* Divide the array into two equal parts containing n/2 elements each
* Now obtain all possible subset products for each part and sort one of them
* Now iterate over non-sorted one and find count of all possible subsets in sorted-one which yields product less than k using `upper_bound`

---

### Rearrange positive and negative numbers with constant extra space while maintaining there order of occurences
[Link](https://www.geeksforgeeks.org/rearrange-positive-and-negative-numbers/)

* We can simply use insertion sort with O(n^2) complexity

**Solution Approach using modified merge sort** -
* Merge operation description -
* Let `[L_n, L_p]` `[R_n, R_p]` be two obtained partition. Now to merge them we follow these steps - 
  * Reverse `L_p` and `R_n` then Reverse `[L_p,R_n]` and done.

---

### Rearrange an array in maximum minimum form | Set 2 (O(1) extra space)
[Link](https://www.geeksforgeeks.org/rearrange-array-maximum-minimum-form-set-2-o1-extra-space/)

**Problem Description** - Given an array, make it such that first element is maximum second element is minimum then third element is second maximum fourth element is second minimum and so on.

**Solution Description** - 
* Sort the given array.
* Intialize mod = arr[n-1] + 1;
* Now update each element as `arr[i] = arr[req_index]%mod*mod + arr[i]%n;`
* Above trick may fail in case of negative numbers. See this link to handle negative numbers using extra space - [Link](https://www.geeksforgeeks.org/rearrange-array-maximum-minimum-form/)

---

### Minimize the maximum difference between the heights
[Link](https://www.geeksforgeeks.org/minimize-the-maximum-difference-between-the-heights/) | [Explanation](https://stackoverflow.com/questions/63000076/minimize-the-maximum-difference-between-the-heights)

**Problem Description** - 
* Given height of n towers, for each tower we can either increase its height by k or decrease its height by k(if possible). Find minimum difference between maximum and minimum height of towers after aforementioned operations

**Solution Approach** - 
* Sort the given array.
* Now for each element, try to increase its height. - 
  * Hence we will increase height of all the towers in the left and decrease height of all towers in the right if possible.
  * So `maximum_h = max(height[i] + k, height[n-1] - k)` and `minimum_h = min(height[0] + k, height[i+1]-k)`, update `ans = min(ans, maximum_h - minimum_h)`
* Return ans

---

### Minimum Swaps required to sort the given array without duplicates
[Link](https://www.hackerrank.com/challenges/minimum-swaps-2/problem) | [Link](https://www.geeksforgeeks.org/minimum-number-swaps-required-sort-array/)

**Note** - If array contains duplicate then its an NP-Complete problem and hence no polynomial time solution.

**Solution Approach** - 
* Normalize the given array, i.e. make every element in range [0,n-1]
* Make an undirected-graph where there is an edge between i to arr[i]
* Now ans will be sum of cycle_size - 1 for every cycle in graph.

```c++
int minimumSwaps(vector<int> nums) {
    vector<int>normalize_nums = normalize_vector(nums);
    for(int i=0;i<n;i++)
    {
        if(normalize_nums[i] == i || visited[i] == 1)
        {
            visited[i] = 1; continue;
        }
        else 
        {
            int curr = i;
            int sz = 0;
            while(visited[curr] != 1)
            {
                visited[curr] = 1;
                curr = normalize_nums[curr];
                sz++;
            }
            ans = ans + sz-1;
        }
    }
    
    return ans;
}
```

---

## Difference Array
[Link](https://www.geeksforgeeks.org/difference-array-range-update-query-o1/)

**Problem Description** - Given an array with following queries - 
* Update(l,r,x) - Adds x to all values in range [l,r] inclusive
* printArray() - Print the whole array. 

**Solution Approach** - 
* We first start by making an difference array where D[0] = A[0] and D[i] = A[i] - A[i-1] for all i > 0
* Then for query of update type we will update as follows
  * D[l] += x;
  * D[r+1] -= x; if r+1 is in range else do nothing
* Now for query of printing the whole array - 
  * arr[i] will be prefix-sum of D[0..i]; 

---
