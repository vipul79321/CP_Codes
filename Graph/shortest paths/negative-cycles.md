### Finding any negative cycle(if it exists) in the graph using Bellman-Ford or SPFA
[Link](https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html#toc-tgt-0) | [Read last Paragraph](https://cp-algorithms.com/graph/bellman_ford.html#toc-tgt-7)

**Algorithm Description** - 
* Intiailize `distance[n] = {0}`, mimcking running of bellman-ford from all vertices
* Run bellman-ford as usual while maintaining the parent array
* If any node gets updated in the last phase(nth phase), use it to recover a cycle. See code below to see how to retrieve a cycle if found.
* [Problem Link](https://cses.fi/problemset/task/1197) | [Bellman-ford negative cycle detection submission](https://cses.fi/paste/7a1ed7d9d6527a652eccde/) | [SPFA negative cycle detection submission](https://cses.fi/paste/4f1083d78853f0872eccd2/)

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
    int start = x;
    for(int i=0;i<parent.size();i++)
    {
        start = parent[start];
    }

    vector<int>neg_cycle;
    int end = start;
    neg_cycle.pb(end); start = parent[start];
    
    for(start; start != end; start = parent[start])
        neg_cycle.pb(start);

    start = neg_cycle.back();
    reverse(neg_cycle.begin(),neg_cycle.end());
    neg_cycle.pb(start);

    for(auto a:neg_cycle)cout<<a+1<<" ";
    cout<<endl;
    return;
}


void solve(int test)
{
   int n,m;
   cin>>n>>m;

   vector<int>dist(n,0), parent(n,-1);
   vector<vector<int> >edges;

   for(int i=0;i<m;i++)
   {
       int a,b,c;
       cin>>a>>b>>c;
       a--,b--;
       edges.pb({a,b,c});
   }

   int last = -1;
   for(int phase=1;phase<=n;phase++)
   {
       last = -1;
       for(auto e:edges)
       {
           int u = e[0], v = e[1], w = e[2];
           if(dist[v] > dist[u] + w)
           {
               dist[v] = dist[u] + w;
               parent[v] = u;
               last = v;
           }
       }
   }

   if(last == -1)
   {
       cout<<"NO\n";
       return;
   }
   else
   {
       cout<<"YES\n";
       print_neg_cycle(last,parent);
   }
}
```

---

### Finding all pairs of vertices which have negative cycle between them (i.e shortest path for them is not defined) using Floyd-Warshall
[Link]()

**Algorithm Description** - 
* Simply run the original floyd warshall, by initializing `d[u][u] = 0` for all u
* Now loop through all pairs of vertices (u,v) and check if there exist a node t such that:
  * `u can reach to t and t can reach to v and dist[t][t] < 0` then (u,v) contains a negative cycle between them and hence shortest path for them is not defined


See code below for more details

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



