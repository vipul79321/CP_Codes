[Link](https://cp-algorithms.com/graph/strongly-connected-components.html)

**Kosaraju Algorithm Description** - `O(n+m)`
* Obtain topological sort of the given graph
* Now call dfs in transpose of original graph(reverse of original graph) from each unvisited node in the topological order
* Nodes visited in same dfs call will belong to same SCC

```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

vector<int>order,visited;
int cnt;
vector<int>v_to_scc;
vector<vector<int> >scc;

void dfs1(int u, vector<vector<int> > &adj)
{
    visited[u] = 1;
    for(auto v:adj[u])if(!visited[v])dfs1(v,adj);

    order.pb(u);
}

void dfs2(int u, vector<vector<int> >&rev_adj)
{
    v_to_scc[u] = cnt;
    scc[cnt].pb(u);
    visited[u] = 1;

    for(auto v:rev_adj[u])
    {
        if(!visited[v])dfs2(v,rev_adj);
    }
}

void solve(int test)
{
   int n,m;
   cin>>n>>m;

   int i,j;
   vector<vector<int> >adj(n);
   vector<vector<int> >rev_adj(n);
   vector<pair<int,int> >edges;
   for(i=0;i<m;i++)
   {
       int a,b;
       cin>>a>>b;
       adj[a].pb(b);
       rev_adj[b].pb(a);
       edges.pb(mp(a,b));
   }

   visited.resize(n,0);
   v_to_scc.resize(n,-1);
   order.clear();
   scc.clear();
   cnt = 0;

   for(i=0;i<n;i++)
   {
       if(!visited[i])dfs1(i,adj);
   }
   for(i=0;i<n;i++)visited[i] = 0;

   reverse(order.begin(),order.end());

   for(auto v:order)
   {
       if(!visited[v])
       {
           vector<int>temp;
           scc.pb(temp);
           dfs2(v,rev_adj);
           cnt++;
       }
   }

   for(i=0;i<n;i++)cout<<v_to_scc[i]<<" ";
   cout<<endl;

   cout<<scc.size()<<endl;


   for(i=0;i<scc.size();i++)
   {
       cout<<"SCC "<<i<<": ";
       for(j=0;j<scc[i].size();j++)cout<<scc[i][j]<<" ";
       cout<<endl;
   }

   // make scc graph

   vector<set<int> >scc_graph(scc.size());

   for(auto p:edges)
   {
       int u = v_to_scc[p.first];
       int v = v_to_scc[p.second];
       if(u==v)continue;
       scc_graph[u].insert(v);
   }

   for(auto s:scc_graph)
   {
       for(auto v:s)cout<<v<<" ";
       cout<<endl;
   }
   cout<<endl;

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
3 3
1 2
0 1
2 0
*/
```
