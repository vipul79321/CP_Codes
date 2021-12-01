### Complicated version with leftmost_lo and leftmost_hi

```c++
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

```


---

### Simplified Version

```c++

/*
* Digit Dp
* Problem Link - https://vjudge.net/problem/LightOJ-1205#author=0
* Problem statement - Find number of palindrome numbers in range [a,b]
* Dp formulation - To solve problem for [0,x]
* Consider following two cases -
* 1. length of palindrome number is less than length of x 
*    * then answer will 9*pow(10,(len-1)/2);  
*    * First digit will be from 1-9 rest from 0-10;
*    * make sure to count 0
* 2) length of palindrome number == length of x
*    * Calculate all palindrome strictly less than x in first half
*    * Check if palindrome equal in first half of x is valid or not and update answer accordingly
*/


#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back

ll dp[20][20];

ll power(ll x, ll p)
{
    ll ans = 1;
    for(ll i=1;i<=p;i++)
    {
       ans = ans*x;
    }
    return ans;
}


ll digit_dp(string num, ll index, ll f, ll len)
{
    if(len-index-1 < index)
    {
        return (f == 0);
    }
    
    if(dp[index][f] != -1)return dp[index][f];
    
    ll ans = 0;
    ll ub = f ? num[index]-'0' : 9;
    ll start = index ? 0:1;
    
    for(ll i=start;i<=ub;i++)
    {
        ans = ans + digit_dp(num,index+1, f&(i==ub),len);
    }
    
    dp[index][f] = ans;
    return ans;
}

string rev(string s)
{
    reverse(s.begin(),s.end());
    return s;
}

bool check(string num)
{
    if(num.length() == 1)return 1;
    
    string s = num.substr(0,num.length()/2);

    if(num.length()%2 == 1) {
        s = s + num[s.size()] + rev(s);
    }
    else {
        s = s + rev(s);
    }
    return (s <= num);
}

ll get_palindrome_less_than_equal(ll a)
{
    if(a < 0)return 0;
    
    string num = to_string(a);
    if(num.length() == 1)return a + 1;
    
    ll ans = 0;

   // Compute for case when length of palindrome is less than length of num
   for(ll len=1;len<=num.length()-1;len++)
   {
       ll place = (len+1)/2;
       if(len==1)ans += 10;
       else
        ans += 9LL*power(10LL,place-1);
   }
   
   memset(dp,-1,sizeof(dp));
   ans = ans + digit_dp(num,0,1,num.length());
   
   if(check(num))ans++;
   
   return ans;
}

void solve(int test)
{
   ll a,b;
   cin>>a>>b;
   if(a>b)swap(a,b);

   cout<<"Case "<<test<<": ";
   
   cout<<get_palindrome_less_than_equal(b) - get_palindrome_less_than_equal(a-1LL)<<endl;


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
```
