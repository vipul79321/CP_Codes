/*
* DP on broken profiles
* Blog link - http://sk765.blogspot.com/2012/02/dynamic-programming-with-profile_13.html
* Problem Statement -
* Given n*m grid.
* For each cell we can either color or leave it empty with the following conditions -
* A colored square must have an even number of colored squares adjacent to it.
* Find number of such valid grid coloring mod 1e9+7;
* Constraints - 1 <= N <= 100 && 1 <= M <= 8
*/

/*
* DP will become like this -
* dp[i][profile] -  number of valid configuration for (i)th row when (i-1)th row, or previous row, has configuration of `profile`.
* profile is ternary representation where -
* if (j)th bit is 0, corresponding cell is uncolored
* if (j)th bit is 1, corresponding cell is colored and count of colored neighbors is odd
* if (j)th bit is 2, corresponding cell is colored and count of colored neighbors is even
*/

#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;

const ll mod = 1e9+7;
// 3^8 = 6561
ll dp[101][6570];
ll n,m;
ll pow3[9], get3[6570][9], set3[6570][9][3];

// Helper function to pre-compute some values for smooth ternary conversion
void preCompute()
{
    // pow3[i] - To store (i)th power of 3
    pow3[0] = 1;
    for(ll i=1;i<=8;i++)pow3[i] = (pow3[i-1]*3)%mod;

    // get3[i][j] - To get the (j)th bit in ternary representation of i
    for(ll i=0;i<=6561;i++)
    {
        for(ll j=0;j<=8;j++)
        {
            get3[i][j] = (i/pow3[j])%3;
        }
    }

    // set3[i][j][k] - To get the value by setting (j)th bit in ternary representation of i to k.
    for(ll i=0;i<=6561;i++)
    {
        for(ll j=0;j<=8;j++)
        {
            for(ll k=0;k<=2;k++)
            {
                set3[i][j][k] = i + (k - get3[i][j])*pow3[j];
            }
        }
    }
}


bool isSet(ll val, ll bit)
{
    if(val&(1<<bit))return 1;
    else
        return 0;
}

// solving for row = row where previous row had profile = profile
ll solve_dp(ll row, ll profile)
{
    if(dp[row][profile]!= -1)return dp[row][profile];

    if(row == n)
    {
        for(ll j=0;j<m;j++)
        {
            if(get3[profile][j] == 1){dp[row][profile]=0;return 0;}
        }
        dp[row][profile]=1; return 1;
    }

    ll ans = 0;

    for(ll coloring=0;coloring<(1<<m);coloring++)  // loop over all possible coloring
    {
        // check if previous row's profile is valid with this coloring scheme 
        // Also maintain profile for current row
        bool valid = true;
        ll curr_profile = 0;

        for(ll j=0;j<m && valid;j++)
        {
            bool isColored = isSet(coloring,j);
            if(isColored && get3[profile][j] == 2)valid = false;
            if(!isColored && get3[profile][j] == 1)valid = false;


            if(!isColored){curr_profile = set3[curr_profile][j][0];continue;}

            ll coloredNeighbors = 0;
            if(get3[profile][j] != 0)coloredNeighbors++;
            if(j>0 && isSet(coloring,j-1))coloredNeighbors++;
            if(j<m-1 && isSet(coloring,j+1))coloredNeighbors++;

            if(coloredNeighbors%2==1)
                curr_profile = set3[curr_profile][j][1];
            else
                curr_profile = set3[curr_profile][j][2];
        }

        if(!valid)continue;

        ans = (ans + solve_dp(row+1,curr_profile))%mod;
    }
    dp[row][profile] = ans;
    return ans;
}


void solve()
{

  n,m;
  cin>>n>>m;

  memset(dp,-1,sizeof(dp));

  ll ans = solve_dp(0,0);
  cout<<ans<<endl;

  return;
}


int main()
{
  preCompute();
  solve();

  return 0;
}

/*
47
7
Returns: 944149920
*/
