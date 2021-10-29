// Q1). Problem Description -
// Given an undirected graph, direct its edges in such a way that number of SCCs are minimized.
// Minimum number of SCCs will be no. of connected components + no. of bridges
// -------------------------------------------------------------------------------
// Q2). How to orient a bridgeless undirected graph to make it a SCC.
// 1). Make all the tree edges point to their child.
// 2). Make all the back edges point to their parent.

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

vector<int>visited,used,low,tin;
int curr,bridges,cc_count;
vector<pair<int,int> >edges;


void dfs(int u,vector<vector<pair<int,int> > >&adj,int par)
{
    visited[u] = 1;
    tin[u] = curr;
    low[u] = tin[u];
    for(auto p:adj[u])
    {
        int v = p.first, id = p.second;
        if(used[id]!=0)continue;

        if(edges[id].first == u && edges[id].second == v)used[id] = 1;
        else
            used[id] = -1;
        if(!visited[v])
        {
            dfs(v,adj,u);
            low[u] = min(low[u],low[v]);
            if(low[v] > tin[u])bridges++;
        }
        else if(v != par)
        {
            low[u] = min(low[u],tin[v]);
        }
    }
}


void solve(int test)
{
   curr = 0,bridges=0,cc_count = 0;
   edges.clear();
   int n,m;
   cin>>n>>m;

   int i,j;
   vector<vector<pair<int,int > > >adj(n);

   for(i=0;i<m;i++)
   {
       int a,b;
       cin>>a>>b;
       adj[a].pb(mp(b,i));
       adj[b].pb(mp(a,i));
       edges.pb(mp(a,b));
   }

   visited.resize(n,0);
   used.resize(m,0);
   low.resize(n,-1);
   tin.resize(n,-1);

   for(i=0;i<n;i++)
   {
       if(!visited[i]){dfs(i,adj,-1);cc_count++;}
   }


   // ans to Q1. - Number of SCCs
   cout<<cc_count + bridges<<endl;

   // ans to Q2

   for(i=0;i<m;i++)
   {
       if(used[i] < 0)cout<<edges[i].first<<" <- "<<edges[i].second<<endl;
       else
        cout<<edges[i].first<<" -> "<<edges[i].second<<endl;
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
