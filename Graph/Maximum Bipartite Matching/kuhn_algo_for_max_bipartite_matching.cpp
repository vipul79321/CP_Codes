// Algorithm Description - Time Complexity O(n1*n1*n2)
// Idea is to find augmenting path from the existing matching. And thereby improving the existing matching.

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int n1,n2,i,j;
vector<vector<int> >adj1,adj2;
vector<int>matching,visited;

bool try_kuhn(int u)
{
    if(visited[u])return 0;

    visited[u] = 1;

    for(auto v:adj1[u])
    {
        if(matching[v] == -1 || try_kuhn(matching[v]))
        {
            matching[v] = u;
            return 1;
        }
    }
    return 0;
}


void solve(int test)
{
   cin>>n1>>n2;
   int m;
   cin>>m;

   adj1.resize(n1);
   adj2.resize(n2);

   for(i=0;i<m;i++)
   {
       int a,b;
       cin>>a>>b;
       adj1[a].pb(b);
       adj2[b].pb(a);
   }
   matching.resize(n2,-1);
   visited.resize(n1);

   int ans = 0;

   for(i=0;i<n1;i++)
   {
       fill(visited.begin(),visited.end(),0);
       ans += try_kuhn(i);
   }
   
   cout<<ans<<endl;
   for(i=0;i<n2;i++)
   {
       if(matching[i] != -1)cout<<matching[i] <<" "<<i<<endl;
   }





}

int main()
{
  int t = 1;
  cin>>t;

  for(int x=1;x<=t;x++)
  {
      solve(x);
  }
  return 0;
}
/*
1
3 3
9
0 1
0 2
0 0
1 0
1 1
1 2
2 0
2 1
2 2
*/
