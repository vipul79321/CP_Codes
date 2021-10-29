### BFS
[Link](https://cp-algorithms.com/graph/breadth-first-search.html)

Applications of BFS - 
* **Find all the edges that lie on the shortest path from a to b** -
  * Call BFS from a and obtain dist_a[n]
  * Call BFS from b and obtain dist_b[n]
  * Now iterate over each edge (u,v) and check whether `dist_a[u] + 1 + dist_b[v] == dist_a[b]` or `dist_a[v] + 1 + dist_b[u] == dist_a[b]`
* **Find all the vertices that lie on the shortest path from a to b** -
  * Call BFS from a and obtain dist_a[n]
  * Call BFS from b and obtain dist_b[n]
  * Now iterate over each vertex v and check `dist_a[v] + dist_b[v] == dist_a[b]`
* **Find the shortest path of even length from a source vertex s to a target vertex t in an unweighted graph** - 
  * Make an auxiliary graph, where for each edge `u-v` in original graph add edge `(u,0) -> (v,1)` and `(u,1) - (v,0)`
  * Now call BFS from `(s,0)` and obtain distance of `(t,0)` and that will be our answer
* **Finding shortest cycle in directed unweighted graph** - 
  * Call BFS from each vertex v as source 
  * During BFS if there is an edge from popped vertex to source(v) then we have found a shortest cycle containing source(v), and update answer accordingly

---

### 0-1 BFS
[Link](https://cp-algorithms.com/graph/breadth-first-search.html)
* Just like normal BFS start from a source but whenever we encounter an unvisited vertex at distance 0 from popped vertex push it in front of queue.

---

### DFS
[Link](https://cp-algorithms.com/graph/depth-first-search.html)

Applications of DFS - 
* **Topological Sorting**
* **Find Articulation Points**
* **Find Bridges**
* **Detect a cycle in directed and undirected graph**
* **Find Strongly Connected Components in directed graph**

**Different type of edges in DFS** - 
* **Tree Edge** - If v is visited for the first time and u is currently being visited then (u,v) is called tree edge or `visited[v] == 0`. 
* **Back Edge** - If v is an ancestor of u then edge `(u,v)` is back edge. or `visited[v] == 1 && inRecursion[v] == 1 && entry[v] < entry[u]`.
* **Forward Edge** - If v is an descendant of u and v has been already visited and exited then edge `(u,v)` is forward edge. or `visited[v] == 1 && inRecursion[v] == 0 && entry[u] < entry[v]`
* **Cross Edge** - If v is neither an ancestor or descendant of u, then edge `(u,v)` is a cross edge. or `visited[v] == 1 && inRecursion[v] == 0 && entry[v] < entry[u]`

**NOTE** - Forward and Cross edges only exist in directed graphs

---

### Transitive Closure of given Graph
[Link](https://www.geeksforgeeks.org/transitive-closure-of-a-graph/)

* Transitive Closure of a graph is a matrix tc[n][n] where tc[i][j] represents whether node j is reachable from node i
* Call DFS from each node and fill the corresponding row of tc[n][n] matrix.

---

### Count nodes at a distance <= K from all the marked vertices in a tree
[Link](https://www.geeksforgeeks.org/count-nodes-within-k-distance-from-all-nodes-in-a-set/)

* Call BFS from any of the marked node and obtain last visited marked node from that BFS, let call it u.
* Call BFS from u and obtain last visited marked node from that BFS, let call it v.
* Now call BFS from v
* Now for each node check `dist_u[x] <= k and dist_v[x] <= k` then ans++;

---

### Minimum Edge Reversal in a directed tree to make a node as root so that it can reach all the other vertices
[Link](https://www.geeksforgeeks.org/minimum-edge-reversals-to-make-a-root/)

**Problem Description** - Given a directed tree with n veritces and n-1 edge, we need to find for each node minimum number of edge reversals so that it can reach every other vertex

**Solution Description** - 
* Intialize dist[n] = {-1}, revCount[n] = {0}, result = 0, ans[n] = {}
* Call BFS from node 0
  * Let u be a popped vertex, iterate over each v in its adjacency list
    * If visited[v] == 1 then continue
    * dist[v] = dist[u] + 1
    * If v->u edge exist then revCount[v] = revCount[u] + 1; result++;
    * else revCount[v] = revCount[u] 
* Finally, ans[i] = result - revCount[i] + (dist[i] - revCount[i]);
* See code below for more details 

```c++
void solve()
{
  vector<vector<pair<int,int> > >adj(n);
  for(auto e:edges)
  {
      adj[e[0]].pb(mp(e[1],0));
      adj[e[1]].pb(mp(e[0],1));  // representing a reverse edge
  }
  
  visited.resize(n,0);
  distance.resize(n,0);
  revCount.resize(n,0);
  result = 0;
  
  queue<int>q; q.push(0);
  
  while(!q.empty())
  {
      int u = q.front(); q.pop();
      
      for(auto &p: adj[u])
      {
          int v = p.first;
          if(visited[v])continue;
          
          distance[v] = distance[u] + 1;
          revCount[v] = revCount[u];
          if(p.second == 1)
          {
              revCount[v]++;
          }
          q.push(v); visited[v] = 1;
      }
  }
  
  vector<int>ans(n,0);
  ans[0] = revCount;
  for(int i=1;i<n;i++)
  {
      ans[i] = result - revCount[i] + (dist[i] - revCount[i]);
  }
}
```

---

### Minimum Edge Reversal in a directed tree to make a path from source to destination
[Link](https://www.geeksforgeeks.org/minimum-edges-reverse-make-path-source-destination/)
* Replace each directed edge (u->v) to (u -> v, weight = 0) and (u <- v, weight = 1)
* Now call 0-1 BFS from source and obtain distance of destination from source

---

### Check if two nodes are on a same path in a Tree
Approaches - 
* **LCA approach**  - O(logn) for each query
* **Intime-Outtime approach** - O(1), check `inTime[u] < inTime[v] && outTime[u] > outTime[v]` or vice-versa



