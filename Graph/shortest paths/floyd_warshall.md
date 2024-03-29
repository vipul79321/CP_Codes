[Link](https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html)

**Idea Description** - 
* The key idea of the algorithm is to partition the process of finding the shortest path between any two vertices to several incremental phases.
* Before k-th phase (k=1…n), d[i][j] for any vertices i and j stores the length of the shortest path between the vertex i and vertex j, which contains only the vertices 1,2,...,k−1 as internal vertices in the path.

**NOTE** - 
* If there exist a negative cycle, then there will be a node with `dist[self][self] < 0`
* But for all pairs of vertices i and j for which there doesn't exist a path starting at i, visiting a negative cycle, and end at j, the algorithm will still work correctly
* We can check that for which pair of vertices dont have negative cycle in between them using below code - 
```c++
for(int u=0;u<n;u++)
{
    for(int v=0;v<n;v++)
    {
        for(int t=0;t<n;t++)
        {
            if(dist[u][t] < INF && dist[t][v] < INF && dist[t][t] < 0)
            {
                dist[u][v] = -INF;
            }
        }
    }
}
```
---

**MAIN CODE** - 

```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

void restore_path(int src, int dest ,vector<vector<int> >&pred)
{
    if(pred[src][dest]==-1){cout<<"No path"<<endl;return;}
    
    vector<int>path;
    while(dest != src)
    {
        path.pb(dest);
        dest = pred[src][dest];
    }
    path.pb(src);
    reverse(path.begin(),path.end());
    
    for(auto vertices:path)cout<<vertices<<" ";
}

void solve(int test)
{

   int n,m;
   cin>>n>>m;


   vector<vector<int> >dist(n,vector<int>(n,INF));
   vector<vector<int> >pred(n,vector<int>(n,-1));

   int i,j,k;

   for(i=0;i<n;i++)dist[i][i] = 0;

   for(i=0;i<m;i++)
   {
       int a,b,c;
       cin>>a>>b>>c;

       dist[a][b] = c;
       pred[a][b] = a;

       // Assuming undirected graph
       dist[b][a] = c;
       pred[b][a] = b;
   }

   for(k=0;k<n;k++)
   {
       for(i=0;i<n;i++)
       {
           for(j=0;j<n;j++)
           {
               if(dist[i][k]<INF && dist[k][j] < INF && dist[i][j] > dist[i][k] + dist[k][j])  // Important part - To never use undefined distance hence check < INF
               {
                   dist[i][j] = dist[i][k] + dist[k][j];
                   pred[i][j] = pred[k][j];
               }
           }
       }
   }

   // Check if Negative cycle exist or not
   bool flag = 0;
   for(int i=0;i<n;i++)if(dist[i][i] < 0){flag = 1;break;}
    
   for(int u=0;u<n;u++)
   {
       for(int v=0;v<n;v++)
       {
           for(int t=0;t<n;t++)
           {
               if(dist[u][t] < INF && dist[t][v] < INF && dist[t][t] < 0)
               {
                   dist[u][v] = -INF;
               }
           }
       }
   }
   
   if(flag){cout<<"Negative cycle found"; return;}
      
   for(i=0;i<n;i++) 
   {
        for(j=0;j<n;j++)
            cout<<dist[i][j]<<" ";
        cout<<endl;
   }

    cout<<endl;

   for(i=0;i<n;i++)
   {
        for(j=0;j<n;j++)
            cout<<pred[i][j]<<" ";
        cout<<endl;
   }
    cout<<endl;

   restore_path(0,6,pred);
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
7 6
0 1 2
0 2 5
1 3 2
3 4 7
5 6 10
5 4 10

*/
```


