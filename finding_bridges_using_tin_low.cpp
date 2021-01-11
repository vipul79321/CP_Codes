// Algorithm Description - O(n+m)
// 1). Idea is that if there is a back edge from a vertex v to any of its ancestor then edge between parent[v]  and v is not a bridge.
// 2). To check if there is a back edge or not we can use concept of tin and low, here parent represent parent in dfs tree.
// 3). If there is a bridge then low[v] > tin[parent[v]].


#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int curr;
vector<int>tin,low,visited;
vector<pair<int,int> >bridges;

void dfs(int u, vector<vector<int> > &adj, int par)
{
    curr++;
    tin[u] = curr;
    low[u] = tin[u];
    visited[u] = 1;
    for(auto v:adj[u])
    {
        if(v==par)continue;
        if(visited[v])low[u] = min(low[u],tin[v]);
        else
        {
            dfs(v,adj,u);
            low[u] = min(low[u],low[v]);
            if(tin[u] < low[v])bridges.pb(mp(u,v));
        }
    }
}

void solve(int test)
{
   int n,m;
   cin>>n>>m;

   int i,j;
   vector<vector<int> >adj(n);
   for(i=0;i<m;i++)
   {
       int a,b;
       cin>>a>>b;
       adj[a].pb(b);
       adj[b].pb(a);
   }

   visited.resize(n,0);
   tin.resize(n,-1);
   low.resize(n,-1);
   bridges.clear();
   curr = 0;

   for(i=0;i<n;i++)
   {
       if(!visited[i])
        dfs(i,adj, -1);
   }

   cout<<bridges.size()<<endl;

   for(auto p:bridges)
   {
       cout<<p.first<<" "<<p.second<<endl;
   }

}

int main()
{
  int t = 1;
  cin>>t;

  for(int x = 1;x<=t;x++)
  {
      solve(x);
  }
  return 0;
}

/*
1
6 10
0 1
0 2
1 2
1 3
2 3
2 4
3 5
3 4
4 5
2 4
*/
/*
1
3 2
1 2
0 1
*/






