// Standard Digit dp
// Problem Link - https://vjudge.net/problem/LightOJ-1068
// Problem statement - Find count of numbers in range [a,b] whose value and sum of digit is divisible by k.
// 

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back

ll dp[20][200][200][2];
ll k;

ll digit_dp(string num, int pos, int rem, int sum, int f)
{
    if(pos==num.length())
    {
        if(rem==0 && sum%k==0)return 1;
        else
            return 0;
    }

    if(dp[pos][rem][sum][f]!=-1)return dp[pos][rem][sum][f];

    int ub = f==1? num[pos]-'0':9;
    ll ans = 0;

    for(int dig=0;dig<=ub;dig++)
    {
        if(dig==ub)
        {
            ans += digit_dp(num,pos+1, (rem*10+dig)%k, sum+dig,f&1);
        }
        else
        {
            ans += digit_dp(num,pos+1, (rem*10+dig)%k, sum+dig,0);
        }
    }
    dp[pos][rem][sum][f] = ans;
    return ans;

}

void solve(int test)
{
   ll a,b;
   cin>>a>>b>>k;
   if(a>b)swap(a,b);

   cout<<"Case "<<test<<": ";

   if(k>=200)
   {
       cout<<0<<endl;
       return;
   }

   memset(dp,-1,sizeof(dp));

   ll val1 = digit_dp(to_string(b),0,0,0,1);

   if(a==1)
   {
       cout<<val1-1<<endl;
       return;
   }

   memset(dp,-1,sizeof(dp));

   ll val2 = digit_dp(to_string(a-1),0,0,0,1);
   cout<<val1-val2<<endl;


}


int main()
{
  fast;

  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  int t = 1;
  cin>>t;

  for(int x = 1;x<=t;x++)
  {
      solve(x);
  }
  return 0;

}

/*
10
1 10
100 1
1 1000
1 10000
100000 100000
10202 10222
0 1
1 0
35435 3434
13132 22242
*/
