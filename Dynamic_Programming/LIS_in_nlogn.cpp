#include<bits/stdc++.h>
using namespace std;
#define pb push_back

// Link to article - https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
// Printing LIS in nlogn - https://www.geeksforgeeks.org/construction-of-longest-monotonically-increasing-subsequence-n-log-n/
// Printing LIS using Fenwick Tree in nlogn - https://github.com/vipul79321/CP_Codes/blob/main/Fenwick%20Tree/LIS_in_nlogn.cpp

int calc_lis(vector<int>&v)
{
    int n = v.size();
    if(n <= 1)return n;

    vector<int>lis(n+1,-1);
    lis[0] = v[0];
    int length = 1;

    for(int i=1;i<n;i++)
    {
        if(v[i] > lis[length-1])
        {
            lis[length] = v[i];
            length++;
            continue;
        }

        if(v[i] < v[0])
        {
            lis[0] = v[i];
            continue;
        }

        int ub = upper_bound(lis.begin(),lis.begin() + length,v[i]) - lis.begin();
        lis[ub] = v[i];
    }

    return length;

}


void solve()
{
   int n;
   cin>>n;
   vector<int>v(n);
   int i,j;
   for(i=0;i<n;i++)cin>>v[i];

   int ans = calc_lis(v);
   cout<<"LIS of given array is: "<<ans<<endl;
}

int main()
{
  solve();
  return 0;
}
/*
16
0 8 4 12 2 10 6 14 1 9 5 13 3 11 7 15
Return
6
*/
