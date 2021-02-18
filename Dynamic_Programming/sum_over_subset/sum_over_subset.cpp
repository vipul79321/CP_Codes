// Digit Dp
// Problem Link - https://vjudge.net/problem/LightOJ-1205#author=0
// Problem statement - Find number of palindrome numbers in range [a,b]
// Dp formulation - To solve problem for [0,x]
// Consider following two cases -
// 1) length of palindrome number is less than length of x then answer will 9*pow(10,(len-1)/2);  First digit will be from 1-9 rest from 0-10;
// In above case 0 wont be counted so count it separately.
// 2) length of palindrome number == length of x
// Consider dp state as dp[pos][leftmost_lo][leftmost_hi]
// where leftmost_lo is the first/leftmost index where digit is less than value in curr
// leftmost_hi is the first/leftmost index where digit is greater than value in curr
// Now transition will be put dig from 0-9 at pos and update leftmost_lo, leftmost_hi for pos and n-pos-1;
// Finally if we have reached (n+1)/2 then check if leftmost_lo < leftmost_hi then return 1  else return 0;


#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back

ll dp[20][20][20];

ll power(ll x, ll p)
{
    ll ans = 1;
    for(ll i=1;i<=p;i++)
    {
       ans = ans*x;
    }
    return ans;
}

ll digit_dp(string num, int pos, int leftmost_lo, int leftmost_hi)
{
    int n = num.length();
    if(pos >= (n+1)/2)
    {
        if(leftmost_lo>leftmost_hi)
            return 0;
        return 1;
    }

    if(dp[pos][leftmost_lo][leftmost_hi]!= -1)return dp[pos][leftmost_lo][leftmost_hi];

    int curr = num[pos]-'0';
    int rev = num[n-pos-1] - '0';
    int start = 0;   // if length is greater than 1 or pos is greater than 0 then start from 0
    if(n!=1 && pos==0)start=1;

    ll ans = 0;

    for(int dig=start;dig<=9;dig++)
    {
        int new_hi = leftmost_hi;
        int new_lo = leftmost_lo;
        if(dig>curr)
        {
           new_hi = min(pos,new_hi);
           if(rev > dig)new_lo = min(new_lo, n-pos-1);
           if(rev < dig)new_hi = min(n-pos-1,new_hi);
        }
        else if(dig==curr)
        {
           if(rev > dig)new_lo = min(new_lo, n-pos-1);
           if(rev < dig)new_hi = min(n-pos-1,new_hi);
        }
        else if(dig<curr)
        {
            new_lo = min(new_lo, pos);
            if(rev > dig)new_lo = min(new_lo, n-pos-1);
            if(rev < dig)new_hi = min(n-pos-1,new_hi);
        }
        ans += digit_dp(num,pos+1,new_lo, new_hi);

    }

    //dp[pos][leftmost_lo][leftmost_hi] = ans;
    return ans;
}

void solve(int test)
{
   ll a,b;
   cin>>a>>b;
   if(a>b)swap(a,b);

   cout<<"Case "<<test<<": ";

   string num1 = to_string(b);
   string num2 = to_string(a-1LL);

   memset(dp,-1,sizeof(dp));

   ll val1 = digit_dp(num1,0,num1.length(),num1.length());


   // Compute for case when length of palindrome is less than length of num1
   for(ll len=1;len<=num1.length()-1;len++)
   {
       ll place = (len+1)/2;
       if(len==1)val1+=10;
       else
        val1 += 9LL*power(10LL,place-1);
   }

   if(a==0)
   {
       cout<<val1<<endl;
       return;
   }

   memset(dp,-1,sizeof(dp));

   ll val2 = digit_dp(num2,0,num2.length(),num2.length());

   // if length is greater than 1 or pos is greater than 0 then start from 0
   for(ll len=1;len<=num2.length()-1;len++)
   {
       ll place = (len+1)/2;
       if(len==1)val2+=10;
       else
        val2 += 9LL*power(10LL,place-1);
   }

   cout<<val1-val2<<endl;
   return;
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
