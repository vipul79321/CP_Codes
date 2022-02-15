[Link](https://cp-algorithms.com/graph/topological-sort.html)

**Topological Sort** - `O(n+m)`
* Graph should be acyclic. 
* Topological order will be the reverse order of exiting dfs.
* If there is edge `u->v` in graph then `index_of_u_in_topo_sort < index_of_v_in_topo_sort`

```c++
int n; // number of vertices
vector<vector<int>> adj; // adjacency list of graph
vector<bool> visited;
vector<int> ans;

bool dfs(int v) {
   visited[v] = 1;
   rec[v] = 1;
   for (int u : adj[v]) {
       //add this line in case of undirected graph - > if(u == parent[v]) continue;
       if (visted[u] == 0) {
           if (dfs(u))
               return true;
       } else if (rec[u] == 1) {
           return true;
       }
   }
   rec[v] = 0;
   ans.push_back(u);
   return false;
}

void topological_sort() {
    visited.assign(n, false);
    ans.clear();
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
        {
          if(dfs(i)){cout<<"Graph is cyclic. Hence no topological sorting\n";return;}
        }
    }
    reverse(ans.begin(), ans.end());
}
```
