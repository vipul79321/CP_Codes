**Problem Description** - [Link](https://cp-algorithms.com/graph/cutpoints.html)
* Given an undirected graph find its all articulation points.
* **Articulation Point** is a vertex whose removal alongwith associated edges increase the number of connected components in the graph

**Solution Approach** - `O(n+m)`
* Idea is that if there is a back edge from a vertex v to any of its ancestor other than its parent then parent of v is not an articulation point.
* To check if there is a back edge or not we can use concept of tin and low, here parent represent parent in dfs tree.
* If `parent[v] is not root` and then `low[v] >= tin[parent[v]]` then `parent[v] is articulation point.`
* To check if `root is an articulation point` check whether it `has more than 1 child in dfs tree`

**Code Description** - 
* Call dfs from any node
* Inside dfs function
  * Initialize `tin[u] = low[u] = curr_time, child = 0, parent[u] = par`
  * Loop through all the neighbors v of u:
    * if v is visited then update `low[u] = min(low[u], tin[v])`
    * else 
      * call dfs from v; child++;
      * After dfs returns from v:
        * update `low[u] = min(low[u], low[v])` 
        * check if `low[v] >= tin[u] && parent[u] != -1` then u( or parent[v]) is articulation point
  * if `parent[u] = -1 and child > 1`, then u is an Articulation point      


```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int curr;
vector<int>tin,low,visited,is_ap;

void dfs(int u, vector<vector<int> > &adj, int par)
{
    curr++;
    tin[u] = curr;
    low[u] = tin[u];
    visited[u] = 1;
    int child = 0;
    for(auto v:adj[u])
    {
        if(v==par)continue;
        if(visited[v])low[u] = min(low[u],tin[v]);
        else
        {
            child++;
            dfs(v,adj,u);
            low[u] = min(low[u],low[v]);
            if(par!= -1 && tin[u] <= low[v])is_ap[u]=1;    // Changes from bridges code is here notice equality and special condition for root
        }
    }

    if(par==-1 && child>1)is_ap[u] = 1;
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
   is_ap.resize(n,0);
   curr = 0;

   for(i=0;i<n;i++)
   {
       if(!visited[i])
        dfs(i,adj, -1);
   }

   int ap = 0;
   for(i=0;i<n;i++)ap+=is_ap[i];

   cout<<ap<<endl;

   for(i=0;i<n;i++)if(is_ap[i])cout<<i<<" ";

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
