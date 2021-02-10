#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int n,m,i,j;
vector<int>present,visited,height;
vector<int>parent,ranked;
vector<vector<pair<int,int> > >adj;
vector<vector<int> >result;
vector<vector<pair<int,int> > >dp;
vector<vector<int> >up;

int find_parent(int a)
{
    if(parent[a] == a)return a;
    parent[a] = find_parent(parent[a]);
    return parent[a];
}

void union_set(int a, int b)
{
    int x = find_parent(a);
    int y = find_parent(b);
    if(x==y)return;
    if(ranked[x] > ranked[y]){parent[y] = x;return;}
    if(ranked[x] < ranked[y]){parent[x] = y;return;}
    if(ranked[x]==ranked[y]){parent[y] = x;ranked[x]++;return;}
}

pair<int,int> combine(pair<int,int>a, pair<int,int>b)  // utility function for finding first max and second max among 4 elements where first max != second max
{
    vector<int>temp = {a.first, a.second, b.first, b.second};
    int top_one = -2, top_two = -3;
    for(auto x:temp)
    {
        if(x>top_one)
        {
            top_two = top_one;
            top_one = x;
        }
        else if(x<top_one)top_two = max(top_two, x);
    }

    return {top_one,top_two};
}

void dfs(int u, int par, int w)
{

    if(par!= -1)
    height[u] = height[par] + 1;
    visited[u] = 1;
    up[u][0] = par;
    dp[u][0] = {w,-1};

    for(auto v:adj[u])
    {
        if(!visited[v.first])dfs(v.first,u,v.second);
    }
}
void make_lca()
{
    int i,j;
    for(i=1;i<21;i++)
    {
        for(j=0;j<n;j++)
        {
            int v = up[j][i-1];
            if(v!= -1)
            {
               up[j][i] = up[v][i-1];
               dp[j][i] = combine(dp[j][i-1], dp[v][i-1]);
            }
        }
    }
}
// standard function to find lca with addition of finding first max and second max and first max != second max edges in path from u to lca and lca to v
pair<int,int> lca_edges(int u, int v)
{
    pair<int,int>ans = {-2,-3};

    if(height[u] < height[v])swap(u,v);

    // Reach till level of v
    for(i=21-1;i>=0;i--)
    {
        if(up[u][i] != -1 && height[up[u][i]] >= height[v])
        {
            ans = combine(ans, dp[u][i]);
            u = up[u][i];
        }
    }
    if(u==v)return ans;

    for(i=21-1;i>=0;i--)
    {
        if(up[u][i] != -1 && up[v][i] != -1 && up[u][i] != up[v][i])
        {
            ans = combine(ans, dp[u][i]);
            ans = combine(ans, dp[v][i]);
            u = up[u][i];
            v = up[v][i];
        }
    }

    ans = combine(ans, combine(dp[u][0], dp[v][0]));
    return ans;
}

void second_mst(vector<vector<int> >&edges)
{

    parent.resize(n);  // For dsu purpose
    ranked.resize(n);  // For dsu purpose
    visited.resize(n,0);  // For dfs
    present.resize(m,0);  // To check whether edge is present in MST or not.
    adj.resize(n);  // adjacency list of MST
    height.resize(n,0);  // height of each node in MST rooted at node = 0
    up.resize(n,vector<int>(21,-1));  // ancestor
    dp.resize(n,vector<pair<int,int> >(21,mp(-3,-3)));  // To get first maximum and second maximum in path from u to up[u][i]

    int i,j;
    for(i=0;i<n;i++)parent[i] = i;
    int total =0;
 
    // standard kruskal
    for(i=0;i<edges.size();i++)
    {
        vector<int>e = edges[i];
        if(result.size()==n-1)break;
        int u = find_parent(e[0]);
        int v = find_parent(e[1]);
        if(u==v)continue;

        total += e[2];
        present[i] = 1;
        adj[e[0]].pb(mp(e[1],e[2]));
        adj[e[1]].pb(mp(e[0],e[2]));
        result.pb(e);
        union_set(u,v);
    }

   dfs(0,-1,0); // dfs to update base condition of up, dp, and height arrays

   make_lca(); // fill up and dp array completely

   int ans = INT_MAX;

   for(i=0;i<m;i++)
   {
       if(present[i])continue;

       int u = edges[i][0];
       int v = edges[i][1];
       int w = edges[i][2];
       pair<int,int>p = lca_edges(u,v);
       if(p.first >= 0 && p.first != w)
       {
           ans = min(ans, total + w - p.first);
       }
       else if(p.second >= 0)
       ans = min(ans,total + w-p.second);
   }
   if(ans == INT_MAX)cout<<total<<endl;
   else
    cout<<ans<<endl;
}

void solve(int test)
{
   cin>>n>>m;

   vector<vector<int>>edges(m);
   int i,j;

   for(i=0;i<m;i++)
   {
       int a,b,c;
       cin>>a>>b>>c;
       edges[i] = {a,b,c};
   }

    sort(edges.begin(),edges.end(), [ ]( const vector<int>& lhs, const vector<int>& rhs )
    {
       return lhs[2] < rhs[2];
    });

   second_mst(edges);

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
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/


