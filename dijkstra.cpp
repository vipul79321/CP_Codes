#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

void restore_path(int v, int s, vector<int>&parent)
{
    if(v==s)return;

    while(v!=s)
    {
        cout<<v<<" ";
        v = parent[v];
    }
    return;
}

void dijkstra_set(vector<vector<pair<int,int> >>&adj, int u)
{
    int n = adj.size(),i,j;
    vector<int>dist(n,INF);
    vector<int>parent(n,-1);
    dist[u] = 0;

    set<pair<int,int> >s;
    for(i=0;i<n;i++)s.insert(mp(dist[i],i));
    vector<int>visited(n,0);

    while(!s.empty())
    {
        auto p = *s.begin();
        s.erase(s.begin());
        visited[p.second] = 1;
        if(p.first == INF)break;
        for(auto x:adj[p.second])
        {
            if(!visited[x.first] && x.second + dist[p.second] < dist[x.first])
            {
                s.erase(mp(dist[x.first],x.first));
                dist[x.first] = x.second + dist[p.second];
                s.insert(mp(dist[x.first],x.first));
                parent[x.first] = p.second;
            }
        }
    }

    for(i=0;i<n;i++)
    {
       cout<<dist[i]<<" ";
    }
    cout<<endl;

}
void dijkstra_pq(vector<vector<pair<int,int> >>&adj, int u)
{
    int n = adj.size(),i,j;
    vector<int>dist(n,INF);
    vector<int>parent(n,-1);
    dist[u] = 0;

    priority_queue<pair<int,int>,vector<pair<int,int> >, greater<pair<int,int> > >pq;
    pq.push(mp(0,u));
    vector<int>visited(n,0);

    while(!pq.empty())
    {
        auto p = pq.top();
        pq.pop();
        if(visited[p.second])continue;

        visited[p.second] = 1;
        if(p.first == INF)break;
        for(auto x:adj[p.second])
        {
            if(!visited[x.first] && x.second + dist[p.second] < dist[x.first])
            {
                dist[x.first] = x.second + dist[p.second];
                pq.push(mp(dist[x.first],x.first));
                parent[x.first] = p.second;
            }
        }
    }

    for(i=0;i<n;i++)
    {
       cout<<dist[i]<<" ";
    }
    cout<<endl;

}

void dijkstra_brute(vector<vector<pair<int,int> >>&adj, int u)
{
    int n = adj.size(),i,j;
    vector<int>dist(n,INF);
    vector<int>parent(n,-1);
    dist[u] = 0;

    vector<int>visited(n,0);

    for(i=0;i<n;i++)
    {
        int v = -1;
        for(j=0;j<n;j++)
        {
            if(!visited[j] && (v== -1 || dist[v] > dist[j]))
                v = j;
        }
        visited[v] = 1;

        if(dist[v] == INF)break;

        for(auto p:adj[v])
        {
            if(!visited[p.first] && dist[v] + p.second < dist[p.first])
            {
                dist[p.first] = dist[v] + p.second;
                parent[p.first] = v;
            }
        }
    }

    for(i=0;i<n;i++)
    {
       cout<<dist[i]<<" ";
    }
    cout<<endl;

}


void solve(int test)
{
   int n,m;
   cin>>n>>m;
   int source;
   cin>>source;

   vector<vector<pair<int,int> > >adj(n);
   int i,j;

   for(i=0;i<m;i++)
   {
       int a,b,c;
       cin>>a>>b>>c;
       adj[a].pb(mp(b,c));
       adj[b].pb(mp(a,c));
   }

   dijkstra_set(adj,source);  // Time Complexity = O(nlogn + mlogn) = O(mlogn)  -->sparse graph
   dijkstra_pq(adj,source);   // Time Complexity = O(nlogn + mlogn) = O(mlogn)  In practice faster than set method  --> Sparse graph
   dijkstra_brute(adj,source); // Time Complexity = O(n^2 + m) Good for dense graph
   // dijkstra_fib(adj,source)  // Time Complexity = O(nlogn + m)  --> very complicated and large constants

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
9 14 0
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


