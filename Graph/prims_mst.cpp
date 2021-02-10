#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

void prims_set(vector<vector<pair<int,int> > >&adj)
{
    int n = adj.size(),i;

    set<pair<int,int> >s;
    vector<int>parent(n,-1);
    vector<int>wt(n);
    vector<int>visited(n,0);

    s.insert(mp(0,0));
    wt[0] = 0;

    for(i=1;i<n;i++)
    {
       s.insert(mp(INF,i));
       wt[i] = INF;
    }
    int total = 0;

    while(!s.empty())
    {
        int u = s.begin()->second;
        total = total + s.begin()->first;
        visited[u] = 1;

        s.erase(s.begin());

        for(auto p:adj[u])
        {
            int v = p.first;
            int w = p.second;
            if(!visited[v] && w < wt[v])
            {
                s.erase(mp(wt[v],v));
                wt[v] = w;
                parent[v] = u;
                s.insert(mp(wt[v],v));
            }
        }
    }
    cout<<total<<endl;
    for(i=0;i<n;i++)
    {
        cout<<i<<" "<<parent[i]<<endl;
    }

    return;
}

void prims_pq(vector<vector<pair<int,int> > >&adj)
{
    int n = adj.size(),i;

    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > >pq;

    pq.push(mp(0,0));

    vector<int>visited(n,0);
    vector<int>parent(n,-1);

    vector<int>wt(n,INF);
    wt[0] = 0;

    int count = 0;
    int total = 0;

    while(count<n)
    {
        pair<int,int> p = pq.top();
        pq.pop();
        if(visited[p.second])continue;

        count++;

        visited[p.second] = 1;
        total += p.first;

        for(auto v:adj[p.second])
        {
            if(!visited[v.first] && wt[v.first] > v.second)
            {
                pq.push(mp(v.second,v.first));
                parent[v.first] = p.second;
                wt[v.first] = v.second;
            }
        }
    }


    cout<<total<<endl;
    for(i=0;i<n;i++)
    {
        cout<<i<<" "<<parent[i]<<endl;
    }


}

void prims_vector(vector<vector<pair<int,int> > >&adj)
{
    int n = adj.size(),i,j;
    vector<int>visited(n,0);
    vector<int>parent(n,-1);
    vector<int>wt(n,INF);
    wt[0] = 0;

    int total = 0;

    for(i=0;i<n;i++)
    {
        int v = -1;
        for(j=0;j<n;j++)
        {
            if(!visited[j] && (v== -1 || wt[j] < wt[v]))
                v = j;
        }

        visited[v] = 1;
        total += wt[v];

        for(auto x:adj[v])
        {
            if(!visited[x.first] && wt[x.first] > x.second)
            {
                wt[x.first] = x.second;
                parent[x.first] = v;
            }
        }
    }

    cout<<total<<endl;
    for(i=0;i<n;i++)
    {
        cout<<i<<" "<<parent[i]<<endl;
    }

}

void solve(int test)
{
   int n,m;
   cin>>n>>m;

   vector<vector<pair<int,int> > >adj(n);
   int i,j;

   for(i=0;i<m;i++)
   {
       int a,b,c;
       cin>>a>>b>>c;
       adj[a].pb(mp(b,c));
       adj[b].pb(mp(a,c));
   }


   prims_set(adj);  // Time Complexity = O(mlogn) , Space complexity = O(n);  -> Good for sparse graph i.e with less edges.
   prims_pq(adj);   // Time Complexity = O(mlogn) , Space complexity = O(m);  -> Good for sparse graph i.e with less edges.
   prims_vector(adj); // Time Complexity = O(n^2) , Space complexity = O(n);  -> Good for dense graph i.e with more edges.
   
   // prims_min_heap(adj); // Can be implemented using implemented MinHeap which support decrease key, but waste of time and same complexity as prims_set
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


