---

**NOTE** -
* If a graph doesnt contain any odd length cycle then it is bipartite and vice-versa
---
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
  * Make an auxiliary graph, where for each edge `u-v` in original graph add edge `(u,0) - (v,1)` and `(u,1) - (v,0)`
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

* Transitive Closure of a graph is a matrix `tc[n][n]` where `tc[i][j]` represents whether node j is reachable from node i
* Call DFS from each node and fill the corresponding row of tc[n][n] matrix.

---

### Count nodes at a distance <= K from all the marked vertices in a tree
[Link](https://www.geeksforgeeks.org/count-nodes-within-k-distance-from-all-nodes-in-a-set/)

* Call BFS from any of the marked node and obtain last visited marked node from that BFS, let call it u.
* Call BFS from u and obtain last visited marked node from that BFS, let call it v.
* Now call BFS from v
* Now for each node check `dist_u[x] <= k and dist_v[x] <= k` then `ans++;`

---

### Minimum Edge Reversal in a directed tree to make a node as root so that it can reach all the other vertices
[Link](https://www.geeksforgeeks.org/minimum-edge-reversals-to-make-a-root/)

**Problem Description** - Given a directed tree with n veritces and n-1 edge, we need to find for each node minimum number of edge reversals so that it can reach every other vertex

**Solution Description** - 
* Intialize `dist[n] = {-1}, revCount[n] = {0}, result = 0, ans[n] = {}`
* Call BFS from node `0`
  * Let u be a popped vertex, iterate over each v in its adjacency list
    * If `visited[v] == 1` then continue
    * `dist[v] = dist[u] + 1`
    * If `v->u` edge exist then `revCount[v] = revCount[u] + 1; result++;`
    * else `revCount[v] = revCount[u]`
* Finally, `ans[i] = result - revCount[i] + (dist[i] - revCount[i]);`
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
* Replace each directed edge `(u->v)` to `(u -> v, weight = 0)` and `(u <- v, weight = 1)`
* Now call 0-1 BFS from source and obtain distance of destination from source

---

### Check if two nodes are on a same path in a Tree
Approaches - 
* **LCA approach**  - O(logn) for each query
* **Intime-Outtime approach** - O(1), check `inTime[u] < inTime[v] && outTime[u] > outTime[v]` or vice-versa

---

### Detect a cycle in a directed or undirected graph and print any if exist
[Link](https://cp-algorithms.com/graph/finding-cycle.html)

```c++
bool dfs(int v) {
   visited[v] = 1;
   rec[v] = 1;
   for (int u : adj[v]) {
       //add this line in case of undirected graph - > if(u == parent[v]) continue;
       if (visted[u] == 0) {
           parent[u] = v;
           if (dfs(u))
               return true;
       } else if (rec[u] == 1) {
           cycle_end = v;
           cycle_start = u;
           return true;
       }
   }
   rec[v] = 0;
   return false;
}

void find_cycle() {
   visited.assign(n, 0);
   rec.assign(n,0);
   parent.assign(n, -1);
   cycle_start = -1;

   for (int v = 0; v < n; v++) {
       if (visited[v] == 0 && dfs(v))
           break;
   }

   if (cycle_start == -1) {
       cout << "Acyclic" << endl;
   } else {
       vector<int> cycle;
       cycle.push_back(cycle_start);
       for (int v = cycle_end; v != cycle_start; v = parent[v])
           cycle.push_back(v);
       cycle.push_back(cycle_start);
       reverse(cycle.begin(), cycle.end());

       cout << "Cycle found: ";
       for (int v : cycle)
           cout << v << " ";
       cout << endl;
   }
}
```

---

### Number of paths of fixed length
[Link](https://cp-algorithms.com/graph/fixed_length_paths.html#toc-tgt-0)

**Problem Description** - 
* Given an unweighted directed graph in adjacency matrix form, where `G[i][j] represent number of edges going from i to j`. 
* We need to find number of paths of length K for all vertex pairs

**Solution Approach** - `O(n^3 logK)`
* Number of path of length k from (u,v) will be - A[u][v] , where A = power(G,K). 
* A can be calculated from G using binary exponentiation and hence in O(n^3 logK)

---

### Shortest Path of length K
[Link](https://cp-algorithms.com/graph/fixed_length_paths.html#toc-tgt-1)

**Problem Description** - 
* Given a weighted directed graph in matrix form, where G[i][j] = w, if there is an edge from i to j of weight w, otherwise G[i][j] = INFINITY
* We need to find shortest path of length K for all vertex pairs

**Solution Approach** - `O(n^3 logK)`
* Shortest path of length k from (u,v) will be - A[u][v] , where A = power(G,K), but here instead of adding in normal matrix multiplication we will take minimum that is
`A[i][j] = min(power(G,K-1)[i][k], G[k][j]) for k in range 0 to n` 

---

### Shortest path of length atmost K
[Link](https://cp-algorithms.com/graph/fixed_length_paths.html#toc-tgt-1)

**Problem Description** - 
* Given an unweighted directed graph in adjacency matrix form, where `G[i][j] represent number of edges going from i to j`. 
* We need to find number of paths of length **upto K** for all vertex pairs

**Solution Description** - 
* For each vertex v, create a vertex `(v+n)` and add following two edges `v - > (v+n)` and `(v+n) -> (v+n)`
* Now, number of paths of length upto K from (u,v) will be equal to number of path length `K+1` from `(u, (v+n))`, which can be calculated as mentioned above
* This works because there is a bijection from any path of `length <= K` from `u to v` and any path of length `K+1` from `u to (v+n)`

---

### Kirchoff's Theorem to find number of different Spanning Trees
[Link](https://cp-algorithms.com/graph/kirchhoff-theorem.html)

**Problem Description** - 
* You are given a **connected undirected graph (with possible multiple edges)** represented using an adjacency matrix.
* Find the number of different spanning trees of this graph

**Solution Description** - 
* Let G be adjacency matrix representation of graph, where G[i][j] represents number of edges between i and j
* Let D be diagonal matrix such that D[i][i] represents degree of node i
* Let Laplace Matrix of this graph will be `L = D - G`
* **All cofactors of L will have same value and will be our required ans.**

---

### Tree Painting
[Link](https://cp-algorithms.com/graph/tree_painting.html)

**Problem Description** - 
* Given a tree, we recieve three types of query paint an edge(u,v) and unpaint an edge(u,v) and number of colored edges in path from (u,v)

**Solution Description** - 
* **Preprocessing** - 
  * Firstly assign each node an unique id. 
  * Now call dfs and obtain euler tour and also edges list containing order in which edges are explored in dfs
```c++
void dfs(int v, const graph& g, const graph& edge_ids, int cur_h = 1) {
    h[v] = cur_h;
    dfs_list.push_back(v);
    for (size_t i = 0; i < g[v].size(); ++i) {
        if (h[g[v][i]] == -1) {
            edges_list.push_back(edge_ids[v][i]);
            dfs(g[v][i], g, edge_ids, cur_h + 1);
            edges_list.push_back(edge_ids[v][i]);
            dfs_list.push_back(v);
        }
    }
}
```
  * Implement LCA finding using Euler tour
  * For each edge in edge list, obtain the index of first_time_e and second_time_e
  * Make two range-sum segment trees of size edge_list and initialize them to zero, T1 and T2

* **Query answering**
  * For query of painting edge x : 
    * update(T1, first_time_e, 1) - Update value at index first_time_e[x] to 1 in Segment Tree T1
    * update(T2, second_time_e, 1) - Update value at index second_time_e[x] to 1 in Segment Tree T2
  * For query of unpainting edge x:
    * update(T1, first_time_e, -1) - Update value at index first_time_e[x] to -1 in Segment Tree T1
    * update(T2, second_time_e, -1) - Update value at index second_time_e[x] to -1 in Segment Tree T2
  * For query of counting number of colored edges in path from u to v:
    * Let lca = LCA(u,v)
    * So answer to our query will ans(lca, u) + ans(lca, v)
    * ans(x,y) will be (assuming x is ancestor of y) - 
      * ans(x,y) = range_sum_T1(first[x], first[y]) - range_sum_T2(first[x], first[y]), here first[x] represents index where node x appears first time in euler tour
      * This works because range_sum_T1 will contain all the colored edges, but there will be some useless edges which doesnt lead to y, but all those edge will be present in T2 too, so subtracting range_sum_T2 will give us the final answer

---

### Number of Spanning Trees of a Complete Graph | Prufer Code | Number of ways to make a graph connected with k-connected components
[Link](https://cp-algorithms.com/graph/pruefer_code.html)

**Prufer Code** - 
* It an encoding of size n-2 of Tree with n vertices, each n-2 entries will be in range[0,n-1]
* We can obtain a unique tree from given prufer code
* Number of times a node is present in prufer code is its degree-1

**Number of Spanning Tree of a complete graph of n vertices | Cayley's Formula**  - `power(n,n-2)`
* Explanation is - Assume a prufer code for a spanning tree, at each n-2 places we have n options

**Number of ways to make a graph connected with k-connected components** - `sz_1 * sz_2 * sz_3 .. sz_k * power(n,n-2)`
[Explanation](https://cp-algorithms.com/graph/pruefer_code.html#toc-tgt-8)

---

### Given an undirected graph minimize number of weakly connected vertices(i.e vertices with indegree == 0) when graph is converted to directed
**Solution** -
* Count number of edges and size of each connected components
* If number of edges  == sz - 1 then there will always be one vertex with indegree == 0 and hence ans++;
* else we can always make every node to have indegree != 0
* To count number of edges, we can simply add degree of each node in the component and divide it by 2

---

### Karp's Minimum Mean Weight Cycle
[Link](https://www.geeksforgeeks.org/karps-minimum-mean-average-weight-cycle-algorithm/) | [Link](https://www.hackerearth.com/practice/notes/karp-minimum-mean-weighted-cycle/)

**Problem Description** - Given a strongly connected graph, we need to find value of **minimum mean weight cycle**

**Solution Description | Karp's Algorithm for Minimum Mean weight cycle** - 
* Initialize source = 0, dp[n][n] = {INF}, dp[0][source] = 0; 
* dp[i][v] represents shortest distance from source to v with exactly i edges
* Fill dp-matrix with following transition - dp[i][v] = min(dp[i][v], dp[i-1][u] + weight_edge(u,v) for all the neighbors u of v )
* Now our ans will be min( `max( (dp[n][v] - dp[k][v]) / (n-k) for all k in range 0 to n-1)` for all v)
![Karp's Minimum Mean Weight Cycle Formula](https://github.com/vipul79321/CP_Codes/blob/main/images/karp-minimum-mean-weight-cylce.jpeg)

---

### Shortest Path in Directed Acyclic Graph
[Link](https://www.geeksforgeeks.org/shortest-path-for-directed-acyclic-graphs/)

* We can find shortest path in DAG in O(n+m) time, by visiting and updating distance of vertices in topological order

---

### Longest Path in Directed Acyclic Graph
[Link](https://www.geeksforgeeks.org/longest-path-in-a-directed-acyclic-graph-dynamic-programming/)

* We can find longest path in DAG in O(n+m) time during dfs and dynamic programming
  * Initialize dp[n] = {0};
  * dp[u] = max(dp[u], weight(u->child) + dp[child])
  * ans will be maximum entry in dp array

---

