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

