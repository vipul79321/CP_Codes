**Problem Description** - [Link](https://cp-algorithms.com/graph/bridge-searching.html)
* Given an undirected graph we need to find all those edges which are bridges i.e, whose removal increases the number of connected components

**Solution Approach** - `O(n+m)`
* Idea is that if there is a back edge from a vertex v to any of its ancestor then edge between parent[v]  and v is not a bridge.
* To check if there is a back edge or not we can use concept of tin and low, here parent represent parent in dfs tree.
* If there is a bridge then low[v] > tin[parent[v]].

**Code Description** - 
* Call dfs from any node
* Inside dfs function
  * Intialize `tin[u] = low[u] = curr_time`
  * Loop through all the neighbors v of u:
    * if v is visited then update `low[u] = min(low[u], tin[v])`
    * else 
      * call dfs from v
      * After dfs returns from v:
        * update `low[u] = min(low[u], low[v])`
        * check if `low[v] > tin[u]` then edge (u - v) is a bridge 

**NOTE** - This code ignores the case of multiple edges in graph. To handle that we can check additionally that the reported bridge is not a multiple edge. Or Alternatively it's possible to pass to dfs the index of the edge used to enter the vertex instead of the parent vertex (and store the indices of all vertices).


```c++
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
            if(tin[u] < low[v])bridges.pb(mp(u,v));  // Here check that u,v is not a multiple edge, by making map<pair<int,int>, int>edges and check if edges[mp(u,v)]>1 || edges[mp(v,u)]>1
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
```




