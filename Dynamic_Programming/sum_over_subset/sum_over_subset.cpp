// See https://codeforces.com/blog/entry/45223 for complete tutorial
// -------------------------------------------------------------------------
// DP formulation 
// Let s(mask,i) = {x | x is submask of mask && mask^x < 2^(i+1)} that is s(mask,i) is set of all x
// such that x is submask of mask and x differs from mask in first i bits only (zero-based).
// -------------------------------------------------------------------------
// DP transition
// s(mask,i) = s(mask,i-1) if ith bit is off. Because no submask of s can have ith bit set.
// s(mask,i) = s(mask,i-1) + s(mask^(1<<i),i-1) if ith bit is on. Consider two cases separately, when ith bit is set in submask and ith bit is unset in submasks.


#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back

int n,mask;
vector<vector<int> >dp;
vector<int>dp_optimized, v;

void solve_dp()
{
    dp.clear();
    dp.resize(mask,vector<int>(n+1,0));

    int i,j;
    for(int msk=0;msk<mask;msk++)dp[msk][0] = v[msk];


    for(i=1;i<=n;i++)
    {
        for(int msk=0;msk<mask;msk++)
        {
            int bit = i-1;
            if(msk&(1<<bit))
            {
                dp[msk][i] = dp[msk][i-1] + dp[msk^(1<<bit)][i-1];
            }
            else
            {
                dp[msk][i] = dp[msk][i-1];
            }
        }
    }

    for(int msk=0;msk<mask;msk++)
        cout<<dp[msk][n]<<" ";
    cout<<endl;
}
void solve_dp_optimized()
{
    dp_optimized.clear();
    dp_optimized.resize(mask,0);

    int i,j;
    for(int msk=0;msk<mask;msk++)dp_optimized[msk] = v[msk];

    for(i=0;i<n;i++)
    {
        for(int msk=0;msk<mask;msk++)
        {
            if(msk&(1<<i))dp_optimized[msk] +=  dp_optimized[msk^(1<<i)];
        }
    }

    for(int msk=0;msk<mask;msk++)
        cout<<dp_optimized[msk]<<" ";
    cout<<endl;
}



void solve(int test)
{
    cin>>n;
    mask = 1<<n;
    v.clear();
    v.resize(mask);

    int i,j;
    for(i=0;i<mask;i++)cin>>v[i];

    solve_dp();
    solve_dp_optimized();

}


int main()
{
   fast;

  int t = 1;
 

  for(int x = 1;x<=t;x++)
  {
      solve(x);
  }
  return 0;
}

/*
4
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/
