### Bellman Ford Algorithm
[Link](https://cp-algorithms.com/graph/bellman_ford.html)
* Time Complexity - `O(nm)`
* Algorithm concept - **After the execution of ith phase, the Bellman-Ford algorithm correctly finds all shortest paths whose number of edges does not exceed i.**
* Finds shortest path lengths from given source to all other vertices.
* Works for directed graph with **no negative cycle reachable from source**.
* Can work for undirected graph given for each undirected edge `u-v` we add two directed `u->v` and `v->u`. There can be no negative edge weights. So can apply Dijkstra too.
* Can also be used to print any negative cycle in the graph | See `negative-cycle.md`
* Can also be used to print negative cycle reachable from source | see code below to print negative cycle detected which is reachable from source


```c++
/*
* let x be the vertex whose distance was improved in the last(nth phase). This vertex will either lie in a negative weight cycle, or is reachable from it.
* parent array be standard parent array to trace path back to source
* Idea is to - 
*    1. To get to the vertex that definitely lie in the negative cycle, start from x and pass through its parent n times, let the vertex reached be y
*    2. Now start from y and go through all its parents till we reach back to y, all those parent will together form the negative cycle.
*/
void print_neg_cycle(int x, vector<int>&parent)
{
    int y = x,i;
    for(i=0;i<n;i++)
    {
        if(y!= -1)
        y = parent[y];
    }
    x = y;

    vector<int>neg_cycle;

    for(y;y>=0;y=parent[y])
    {
        neg_cycle.pb(y);
        if(y==x && neg_cycle.size()>1)
            break;
    }
    for(auto a:neg_cycle)cout<<a<<" ";
    cout<<endl;
    return;
}

```

----

**MAIN CODE** - 

```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6
int n,m,source;

void restore_path(int v, int s, vector<int>&parent)
{
    if(v==s)return;

    while(v!=s)
    {
        cout<<v<<" ";
        v = parent[v];
    }
    cout<<s<<endl;
    return;
}

void print_neg_cycle(int x, vector<int>&parent)
{
    int y = x,i;
    for(i=0;i<n;i++)
    {
        if(y!= -1)
        y = parent[y];
    }
    x = y;

    vector<int>neg_cycle;

    for(y;y>=0;y=parent[y])
    {
        neg_cycle.pb(y);
        if(y==x && neg_cycle.size()>1)
            break;
    }
    for(auto a:neg_cycle)cout<<a<<" ";
    cout<<endl;
    return;
}

void bellman_ford(vector<vector<int> >&edges)
{
    int m = edges.size();

    vector<int>dist(n,INF);
    vector<int>parent(n,-1);
    int i,j,x;
    dist[source] = 0;

    for(i=0;i<n;i++)
    {
        x = -1;
        for(auto e:edges)
        {
            int u=e[0], v=e[1], w=e[2];
            if(dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                x = v;
            }
        }
        if(x == -1)break; // No vertex was updated in this phase
    }

    if(x== -1)
    {
        cout<<"No negative cycle reachable from source is found"<<endl;
        for(i=0;i<n;i++)cout<<dist[i]<<" ";
        cout<<endl;
    }
    else
    {
        cout<<"Negative cycle reachable from source found"<<endl;
        print_neg_cycle(x,parent);
    }

}

void solve(int test)
{

   cin>>n>>m;

   cin>>source;

   vector<vector<int> >edges(m);
   int i,j;

   for(i=0;i<m;i++)
   {
       int a,b,c;
       cin>>a>>b>>c;
       edges[i] = {a,b,c};
   }

   bellman_ford(edges);  // O(nm)
   spfa(edges);   // O(nm)  in practice a bit fast


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
7 11 0
0 1 2
0 2 5
1 2 2
3 4 -1
4 3 -1
5 6 10
3 5 10
5 4 10
4 3 10
5 3 10
2 3 10
*/
```

---

### Shortest Path Finding Algorithm (SPFA)
[Link](https://cp-algorithms.com/graph/bellman_ford.html#toc-tgt-8)

* `O(nm)` in worst case.
* Always better than Bellman Ford.
* Can also be used to detect negative cycle from source and print it.

**Algorithm Description** - 
* Make a queue and push source into it. In general, queue will store all the vertices which can further relax other vertices
* Pop a node from queue, mark `inQueue[u] = 0`
* Try to relax, neighbors of u, using u - 
  * If a neighbor is relaxed
    * update its parent
    * Push it in queue if not already present and mark inQueue[v] = 1
    * update cnt[v]++; if cnt[v] > n then negative cycle is present and break
* Print negative cycle as done in bellman-ford    


```c++
void spfa(vector<vector<int> >&edges)
{
    queue<int>q;
    vector<int>dist(n,INF);
    vector<int>inqueue(n,0);
    vector<int>parent(n,-1);
    vector<int>cnt(n,0); // - To store how many times a vertex has been relaxed, if it has been relaxed more than n times then there is a negative loop

    vector<vector<pair<int,int> > >adj(n);
    int i,j;
    for(auto e:edges)
    {
        adj[e[0]].pb(mp(e[1],e[2]));
    }

    q.push(source);
    dist[source] = 0;
    inqueue[source] = 1;

    bool flag = 1;
    int x = -1;

    while(!q.empty() && flag)
    {
        int u = q.front();
        q.pop();
        inqueue[u] = 0;
        for(auto p:adj[u])
        {
            int v = p.first;
            int w = p.second;
            if(dist[u] != INF && dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if(!inqueue[v])
                {
                   q.push(v);
                   inqueue[v] = 1;
                   cnt[v]++;
                   if(cnt[v] > n){x = v;flag = 0;break;}
                }
            }
        }
    }
    if(flag)
    {
        cout<<"No negative cycle reachable from source is found"<<endl;
        for(i=0;i<n;i++)cout<<dist[i]<<" ";
        cout<<endl;
    }
    else
    {
        cout<<"Negative cycle reachable from source found"<<endl;
        print_neg_cycle(x,parent);

    }
}
```



