// Digit Dp with lb, ub and non_zero state
// Problem statement - Given range [a,b] find the number in this range with maximum digit products
// Problem link - https://codeforces.com/gym/100886/problem/G

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define hell 1000000007
ll a,b;
string num1,num2;
pair<ll,ll> dp[20][2][2][2];
ll power10[19];

pair<ll,ll> digit_dp(ll pos, bool l, bool r, bool non_zero)
{
    if(pos==num1.length())
    {
        if(non_zero == 1)return mp(1,0);
        return mp(0,0);
    }
    ll n=num1.length();

    if(dp[pos][l][r][non_zero].first!=-1)return dp[pos][l][r][non_zero];

    ll ub = r?9:num1[pos]-'0';
    ll lb = l?0:num2[pos]-'0';

    pair<ll,ll>ans1,ans;
    ans1 = mp(-1,0);
    ans = mp(-1,0);
    ll maxi = -1;
    pair<ll,ll>opt;

    for(ll dig=lb; dig<=ub;dig++)
    {
        if(dig == 0 && non_zero == 0)
            ans1 = digit_dp(pos+1,l||(dig>lb), r||(dig<ub), non_zero||dig);

        opt = digit_dp(pos+1,l||(dig>lb), r||(dig<ub),non_zero||dig);
        opt.first = opt.first*dig;
        opt.second = power10[n-pos-1]*dig+opt.second;

        if(opt.first >= maxi)
            ans = opt, maxi = opt.first;
    }
    if(ans1.first > ans.first)
        ans = ans1;

    dp[pos][l][r][non_zero] = ans;
    return ans;
}


void solve(int test)
{
    cin>>a>>b;

    num1 = to_string(b);
    num2 = to_string(a);

    for(int i=0;i<20;i++)
    {
        for(int l=0;l<=1;l++)
        {
            for(int r=0;r<=1;r++)
            {
                for(int z=0;z<=1;z++)dp[i][l][r][z] = mp(-1,-1);
            }
        }
    }

    reverse(num2.begin(),num2.end());
    while(num2.length()<num1.length())num2.append("0");
    reverse(num2.begin(),num2.end());

    pair<ll,ll> ans = digit_dp(0,0,0,0);
    cout<<ans.second<<endl;
    return;
}

int main()
{
  fast;

  int t = 1;
  ll p10=1;
  for(ll i=0;i<=18;i++)
  {
      power10[i] = p10;
      p10 = p10*10;
  }

  //cin>>t;

  for(int x=1;x<=t;x++)
  {
      solve(x);
  }
  return 0;

}
