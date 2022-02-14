[Link](https://cp-algorithms.com/data_structures/disjoint_set_union.html)

### Disjoint Set-Union

* DSUs have two major operation - `find_set(v)` and `union_set(u,v)`
* DSUs with `path-compression` give an average time complexity of `O(logn)`
* DSUs with `union-by-rank/size` give an average time complexity of `O(logn)`
* DSUs with both `path-compression` and `union-by-rank/size` give an amortized complexity of `O(1)`

**find_set trivial implementation**
```c++
int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}
```

**find_set Path-Compression implementation**
```c++
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
```

**union_set trivial implementation**
```c++
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}
```

**union_set by rank implementation | Make set with bigger rank as parent of set with small(or equal rank)**
```c++
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}
```

**union_set by size implementation | Make set with bigger size parent of set with small(or equal) size**
```c++
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}
```

---

### Compress jumps along a segment | Painting subarrays offline
[Link](https://cp-algorithms.com/data_structures/disjoint_set_union.html#toc-tgt-10)

**Problem Description** - 
* Given an array of length L, in which initially all the elements are uncolored. 
* We recieve q queries of type (l,r,c) to re-color the sub-segment (l,r) with color c
* We need to output the final color of all elements after processing all the queries

**Solution Description** - 
* Maintain a dsu for whole array such that `parent[i] == i for i from [0,L]`
* Each DSU will point to next uncolored element or itself
* Process queries in the reverse order i.e, last to first
* We will use path-compression technique to achieve an average time complexity of `O(nlogn)`
* We cant use union-by-rank techinque because we need to make sure who becomes the leader after union

**Implementation**
```c++
int find_set(int u) {
    if(parent[u] == u)return u;
    return parent[u] = find_set(parent[u]);
}

for (int i = 0; i <= L; i++) {
    parent[i] = i;
}

for (int i = m-1; i >= 0; i--) {
    int l = query[i].l;
    int r = query[i].r;
    int c = query[i].c;
    for (int v = find_set(l); v <= r; v = find_set(v)) {
        answer[v] = c;
        parent[v] = v + 1; // simply make next element as its parent
    }
}
```

**NOTE** - We can use `union by rank`, if we store the next unpainted cell in an additional array end[]. Then we can merge two sets into one ranked according to their heuristics, and we obtain the solution in O(α(n))

---

### Support Distance upto Representative
[Link](https://cp-algorithms.com/data_structures/disjoint_set_union.html#toc-tgt-11)

**Problem Description** - 
* We want to store the distance of each node to its set-representative

**Solution Descripiton** - 
* We will parent array of pairs, where first entry will be parent element and second entry will be distance from that parent element

```c++
void make_set(int v) {
    parent[v] = make_pair(v, 0);
    rank[v] = 0;
}

pair<int, int> find_set(int v) {
    if (v != parent[v].first) {
        int len = parent[v].second;
        parent[v] = find_set(parent[v].first);
        parent[v].second += len;             // Imp line
    }
    return parent[v];
}

void union_sets(int a, int b) {
    a = find_set(a).first;
    b = find_set(b).first;
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = make_pair(a, 1);         // Imp Line
        if (rank[a] == rank[b])
            rank[a]++;
    }
}
```

---

### Support the parity of the path length | Checking bipartiteness online in amortized O(1)
[Link](https://cp-algorithms.com/data_structures/disjoint_set_union.html#toc-tgt-12)

**Problem Description** - 
* Initially we are given an empty graph, it can be added edges, and we have to answer queries of the form "is the connected component containing this vertex bipartite?"

**Solution Description** - 
* We will make a dsu storing representative of the set and parity of length of path from node to its set-representative
* Now while adding edges(u-v) following case arises - 
  * u and v belong to **same connected components and their parity is same**
    * Then adding edge u,v will make an odd length cycle and hence the set will lose its bipartiteness
  * u and v belong to **same connected components and their parity is different**
    * We can simply ignore this case and do nothing
  * u and v belong to **different connected components**
    * Without loss of generality assume that we will make set of v as parent of set of u, using union-by-rank or union-by-size
    * Now, we need to somewhat re-root set of u to u and then do union accordingly
    * But re-rooting will inefficient, so we need to calculate new-parity of leader of set u to avoid that
    * Let x be parity from u to its representative and y be parity from v to its representative
    * So the new parity of representative of u, will be `x^y^1` (1 comes from adding edge)

```c++
void make_set(int v) {
    parent[v] = make_pair(v, 0);
    rank[v] = 0;
    bipartite[v] = true;
}

pair<int, int> find_set(int v) {
    if (v != parent[v].first) {
        int parity = parent[v].second;
        parent[v] = find_set(parent[v].first);
        parent[v].second ^= parity;
    }
    return parent[v];
}

void add_edge(int a, int b) {
    pair<int, int> pa = find_set(a);
    a = pa.first;
    int x = pa.second;

    pair<int, int> pb = find_set(b);
    b = pb.first;
    int y = pb.second;

    if (a == b) {
        if (x == y)
            bipartite[a] = false;
    } else {
        if (rank[a] < rank[b])
            swap (a, b);
        parent[b] = make_pair(a, x^y^1);
        bipartite[a] &= bipartite[b];
        if (rank[a] == rank[b])
            ++rank[a];
    }
}

bool is_bipartite(int v) {
    return bipartite[find_set(v).first];
}
```

---

### Offline RMQ (range minimum query) in O(α(n)) on average | Arpa's trick
[Link](https://cp-algorithms.com/data_structures/disjoint_set_union.html#arpa)

**Problem Description** - Given an array, we need to answer range-minimum queries (L,R)

**Solution Description** - 
* We will iterate over the array and when we are ith element we will answer all the queries having `R==i`
* Answer to each query (L,R) will be `arr[find_set(L)]`

```c++
struct Query {
    int L, R, idx;
};

vector<int> answer;
vector<vector<Query>> container;

stack<int> s;
for (int i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] > a[i]) {
        parent[s.top()] = i;
        s.pop();
    }
    s.push(i);
    for (Query q : container[i]) {
        answer[q.idx] = a[find_set(q.L)];
    }
}
```

---

### Storing the DSU explicitly in a set list | Applications of this idea when merging various data structures
[Link](https://cp-algorithms.com/data_structures/disjoint_set_union.html#toc-tgt-15)

**Alternate DSU implementation** - 
* Here we will store each set as explicitly stored list of its elements.
* While doing union, we will add set of small size to set of larger size.
  * By doing this, we can obtain a total time complexity of `O(queries + nlogn)`
  * Because each element can be touched a maximum of logn times during union-set 
* Finding leader of set will be O(1) operation

```c++
vector<int> lst[MAXN];
int parent[MAXN];

void make_set(int v) {
    lst[v] = vector<int>(1, v);
    parent[v] = v;
}

int find_set(int v) {
    return parent[v];
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (lst[a].size() < lst[b].size())
            swap(a, b);
        while (!lst[b].empty()) {
            int v = lst[b].back();
            lst[b].pop_back();
            parent[v] = a;
            lst[a].push_back (v);
        }
    }
}
```

**Use case of above implementation** - 
* **Problem Description** - 
  * we are given a tree, each leaf has a number assigned (same number can appear multiple times on different leaves). 
  * We want to compute the number of different numbers in the subtree for every node of the tree.
* **Solution Description** - 
  * We can perform DFS, which will return a set containing all the nodes in that subtree
  * For a node, we will call DFS from each of its child and merge all the recieved sets together using the principle that smaller set will be added to larger set
