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
