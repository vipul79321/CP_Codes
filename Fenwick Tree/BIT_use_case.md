**Some Important Points** - 
* 0-indexed binary indexed tree
  * while updating we iterate `for(id; id<n; id = id|(id+1))` 
    * id|(id+1) -> Flips the last unset bit 
  * while computing we iterate `for(id; id>=0; id = id&(id+1)-1)`
    * id&(id+1) -> If last bit is 0 then do nothing, else flips all the one in the ending
* 1-indexed binary indexed tree
  * while updating we iterate `id++; for(id; id<=n; id += id&(-id))`
  * while computing we iterate `id++; for(id; id>0; id -= id&(-id))`
    * id&(-id) -> Return the last set bit  

---

### Fenwick Tree | Binary Indexed Tree
[Link](https://cp-algorithms.com/data_structures/fenwick.html)

* Let, f be some **reversible function** and A be an array of integers of length N.
* Fenwick tree is a data structure which:
 * **calculates f(Al,Al+1,…,Ar)) in O(logn) time**
 * **updates** the value of an element of A in **O(logn)** time
 * requires **O(N) memory**, or in other words, exactly the same memory required for A
 * is easy to use and code, especially, in the case of multidimensional arrays.

---

### Calculate Inversion in given array
```c++
// Given an array for each index, we need to ans number of elements less than the value at that index which has appeared till that index.
#include<bits/stdc++.h>
using namespace std;
void update(vector<int>&bit, int idx, int n)
{
    idx += 1;

    while(idx <= n)
    {
        bit[idx] += 1;
        idx += idx&(-idx);
    }
}

int sum(vector<int>&bit, int idx, int n)
{
    idx+=1;
    int sum = 0;
    while(idx>0)
    {
        sum += bit[idx];
        idx -= idx&(-idx);
    }
    return sum;
}

vector<int> solve(vector<int>& nums) {
    int n = nums.size();
    vector<int>temp;
    int i,j;
    for(i=0;i<nums.size();i++)temp.push_back(nums[i]);

    sort(temp.begin(),temp.end());

    map<int,int>m;
    for(i=0;i<n;i++)m[temp[i]] = i;   // store sorted index of each element

    vector<int>bit(n+10,0);
    vector<int>ans(n,0);
    for(i=0;i<n;i++)
    {
        ans[i] = sum(bit,m[nums[i]], n);
        update(bit, m[nums[i]], n);
    }
    return ans;
}

int main()
{
  int n;
  cin>>n;
  vector<int>v = {3,5,1,4,2};
  //vector<int>v(n);

  vector<int>ans = solve(v);
  for(auto a:ans)cout<<a<<" ";

  }
```
