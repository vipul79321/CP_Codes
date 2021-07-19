/*
* DP on broken profiles
* Problem link - http://community.topcoder.com/stat?c=problem_statement&pm=8397&rd=10806
* Problem Statement -
* Given n*m room. We have to lay floorboards in this room.
* floorboards have width 1 and any positive length.
* Some cells maybe blocked as they contain pillar
* We need to find minimum number of floorboards required to fill the floor
* Constraints N,M [1,10];
*/

/*
* DP will become like this -
* dp[i][profile] -  minimum number of boards we can use to cover all the areas from row[0] to row[i] when (i-1)th row has configuration of profile..
* Profile description -
* If (j)th bit is set in profile then (j)th column of previous row contains a vertical floorboard
* Else the (j)th column in previous row contains a pillar or horizontal floorboard
*/

#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;
int n,m;
vector<string>room;
const int inf = 1e6;
int dp[11][2000];

int solve_dp(int row, int profile)
{
    if(row == n)
    {
        return 0;
    }

    if(dp[row][profile] != inf)return dp[row][profile];

    int ans = inf;

    for(int config = 0; config < (1<<m); config++)
    {
        int floorboardCount = 0;
        bool isHorizontal = false;
        bool valid = true;
        for(int j=0;j<m;j++)
        {
            if(config&(1<<j) && room[row][j] == '#'){valid = false;break;}

            if(config&(1<<j))
            {
                isHorizontal = false;
                if(profile&(1<<j));
                else
                    floorboardCount++;
            }
            else
            {
                if(room[row][j] == '#')
                {
                    isHorizontal = false;
                }
                else if(!isHorizontal)
                {
                    isHorizontal=true;
                    floorboardCount++;
                }
            }
        }
        if(valid)
            ans = min(ans,floorboardCount + solve_dp(row+1,config));
    }

    dp[row][profile] = ans;
    return dp[row][profile];
}


void solve()
{
   cin>>n>>m;
   room.resize(n);
   for(int i=0;i<n;i++)cin>>room[i];

   for(int i=0;i<=10;i++)
    for(int j=0;j<2000;j++)dp[i][j] = inf;

   int ans = solve_dp(0,0);
   cout<<ans<<endl;

}


int main()
{
  solve();

  return 0;
}

/*
6 6
...#..
##....
#.#...
.#....
..#...
..#..#
Return
9
*/
/*
6 7
.......
.#..##.
.#.....
.#####.
.##..#.
....###
Return
7
*/
