// Algorithm description - Time Complexity = O(V^0.5 * E)
// Consider a dummy node, every unmatched vertex is connected to it. So if we can start our bfs from an unmatched vertex 
//and reach that dummy node again then there exist an augmenting path
// Steps - 
// 1). Create adj list of the given graph and dummy node == 0
// 2). Fill pair1, pair2 array with pair1 = {dummy}, pair2= {dummy}
// 3). Now while(bfs()){do dfs from unmatched vertex in set1 i.e pair1[i] == dummy, if dfs returns 1 then ans++}
// --------------------------------------------------------------------------
// BFS Description - 
// 1). Do bfs as follow, push all the unmatched vertices of set1 in queue with their dist = 0, 
//  and for all the remaining vertices in set1 their dist is INF, also dist[dummy] = INF
// 2). while(!q.empty()){ pop, if u == dummy continue, else for(auto v:adj[u]) if(dist[pair2[to]] == INF){push in q and update dist[pair2[v]] = dist[u] + 1}}
// 3). Finally return dist[dummy] != INF
// --------------------------------------------------------------------------
// DFS(u) description -
// 1). If u == dummy return 1;
// 2). for(auto v:adj[u]){  if(dist[pair2[v]] == dist[u]+1){ if(dfs(pair2[v])then update matching and return true;} }
// 3). If in step 3 no update then assign dist[u] = INF, so to avoid revisiting of vertex u. and return 0 




#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6
#define dummy 0

int n1,n2,i,j;
vector<vector<int> >adj;
vector<int>dist,pair1,pair2;

bool bfs()
{
    queue<int>q;
    fill(dist.begin(),dist.end(),INF);
    for(i=1;i<=n1;i++)
    {
        if(pair1[i] == dummy){q.push(i);dist[i] = 0;}
    }
    dist[dummy] = INF;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        if(u==dummy)continue;
        for(auto v:adj[u])
        {
            int x = v - n1;
            if(dist[pair2[x]] == INF)
            {
                q.push(pair2[x]);
                dist[pair2[x]] = dist[u] + 1;
            }
        }
    }

    return dist[dummy] != INF;

}

bool dfs(int u)
{

    if(u==dummy)return 1;

    for(auto v:adj[u])
    {
        int x = v - n1;
        int to = pair2[x];
        if(dist[to] == dist[u] + 1)
        {
            if(dfs(to))
            {
                pair1[u] = x;
                pair2[x] = u;
                return 1;
            }
        }

    }
    dist[u] = INF;
    return 0;

}

void solve(int test)
{
    cin>>n1>>n2;
    adj.resize(n1+n2+1);
    dist.resize(n1+1);
    pair1.resize(n1+1);
    pair2.resize(n2+1);

    int edges;
    cin>>edges;
    for(i=0;i<edges;i++)
    {
        int u,v;
        cin>>u>>v;
        v = v+n1;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    for(i=0;i<=n1;i++)
    {
        pair1[i] = dummy;
    }
    for(i=0;i<=n2;i++)
    {
        pair2[i] = dummy;
    }

    int ans = 0;

    while(bfs())
    {
        for(i=1;i<=n1;i++)
        {
            if(pair1[i] == dummy && dfs(i))ans++;
        }
    }

    cout<<ans<<endl;
    return;

    for(i=1;i<=n1;i++)
    {
        if(pair1[i] != dummy)cout<<i<<" "<<pair1[i]+n1<<endl;
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
1 4
1 5
1 6
2 4
2 5
2 6
3 4
3 5
3 6
*/
