[Link](https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html)

**Idea Description** - 
* The key idea of the algorithm is to partition the process of finding the shortest path between any two vertices to several incremental phases.
* Before k-th phase (k=1…n), d[i][j] for any vertices i and j stores the length of the shortest path between the vertex i and vertex j, which contains only the vertices 1,2,...,k−1 as internal vertices in the path.

**NOTE** - 
* If there exist a negative cycle, then there will be a node with `dist[self][self] < 0`
* But for all pairs of vertices i and j for which there doesn't exist a path starting at i, visiting a negative cycle, and end at j, the algorithm will still work correctly
* We can check that for which pair of vertices dont have negative cycle in between them using below code - 
```c++
for(k=0;k<n;k++)
   {
       if(d[k][k]>=0)continue;
       flag = 1;
       for(i=0;i<n;i++)
       {
           for(j=0;j<n;j++)
           {
               if(d[i][k]<INF && d[k][j] < INF && d[k][k]<0)
               {
                   d[i][j] = -INF;
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

void restore_path(int v, int s ,vector<vector<int> >&p)
{
    if(p[s][v]==-1){cout<<"No path"<<endl;return;}
    while(s!=v)
    {
        cout<<v<<" ";
        v = p[s][v];
    }
    cout<<endl;
}

void solve(int test)
{

   int n,m;
   cin>>n>>m;


   vector<vector<int> >d(n,vector<int>(n,INF));
   vector<vector<int> >p(n,vector<int>(n,-1));

   int i,j,k;

   for(i=0;i<n;i++)d[i][i] = 0;

   for(i=0;i<m;i++)
   {
       int a,b,c;
       cin>>a>>b>>c;

       d[a][b] = c;
       p[a][b] = a;

       d[b][a] = c;
       p[b][a] = b;
   }

   for(k=0;k<n;k++)
   {
       for(i=0;i<n;i++)
       {
           for(j=0;j<n;j++)
           {
               if(d[i][k]<INF && d[k][j] < INF && d[i][j] > d[i][k] + d[k][j])  // Important part - To never use undefined distance hence check < INF
               {
                   d[i][j] = d[i][k] + d[k][j];
                   p[i][j] = p[k][j];
               }
           }
       }
   }

   bool flag = 0;
    
   for(k=0;k<n;k++)
   {
       if(d[k][k]>=0)continue;
       flag = 1;
       for(i=0;i<n;i++)
       {
           for(j=0;j<n;j++)
           {
               if(d[i][k]<INF && d[k][j] < INF && d[k][k]<0)
               {
                   d[i][j] = -INF;
               }
           }
       }
   }
   if(flag){cout<<"Negative cycle found"; return;}
      
   for(i=0;i<n;i++){
    for(j=0;j<n;j++)cout<<d[i][j]<<" ";cout<<endl;}

    cout<<endl;

   for(i=0;i<n;i++){
    for(j=0;j<n;j++)cout<<p[i][j]<<" ";cout<<endl;}
    cout<<endl;

   restore_path(0,6,p);
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


