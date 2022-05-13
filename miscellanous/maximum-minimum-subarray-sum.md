## Search the subarray with the maximum/minimum average
[Link](https://cp-algorithms.com/others/maximum_average_segment.html)

---

**Sub-Problem - 1** - Given an array and a number x, check if there exist a subarray whose average is greater than equal to x.

**Solution Approach to above sub-problem** - Subtract x from all elements in the array and check if there exist a non-negative sum subarray.

---

**Sub-Problem - 2** - Given an array and a range [L,R], find maximum sum subarray whose length lies in range [L,R]

**Solution Approach** - 
* Make a prefix array, and ans for index i, will be prefix[i] - minimum of prefix in range [i-R+1, i-L+1];
* For finding minimum in that range we can use segment tree.
* Or we can also use the sliding window minimum for every window of size `R-L+1`

---

**Problem Description** - Given an array find subarray whose length is in range [L,R] and average is maximum among all such subarray.

**Solution Description** - 
* If L <= 1 then simply return maximum element in the array.
* Otherwise, apply binary search as follows - 
  * low = -inf, high = inf;
  * Check if there exist a subarray, whose average is greater than equal to x and length is range [L,R] - using concept in sub-problem 1 & 2


