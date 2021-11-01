### Common Preprocessing Step for all approaches - DFS call
* Precompute - Euler Tour, height, tin, tout, first, dp[u][0]
```c++
void dfs(int u, vector<vector<int> >&adj,int level, int par)
{
    visited[u] = 1;
    curr++;
    tin[u] = curr;
    curr++;
    h[u] = level;
    dp[u][0] = par;
    first[u] = euler.size();
    euler.pb(u);

    for(auto v:adj[u])
    {
        if(!visited[v]){dfs(v,adj,level+1,u);euler.pb(u);}
    }
    curr++;
    tout[u] = curr;
    curr++;

}

```

---

### LCA using Euler Tour and RMQ
[Link](https://cp-algorithms.com/graph/lca.html)

**Solution Description** - 
* Preprocess Euler tour - We insert a node in euler tour when we first visit it and whenever a dfs call returns from its child
* Preprocess First[i] - stores the index of first occurence of node i in euler tour
* Preprocess height[i] - Height of node i
* Now to answer lca(u,v) - we need to find node at minimum height in range(min(first[u],first[v]) , max(first[u],first[v])) in Euler Tour
* So it basically becomes a range minimum query - 
  * Using Segment Tree: O(N)- Preprocessing Time, O(logN) - Query Time
  * Using Sparse Table: O(NlogN) - Preprocessing Time, O(1) - Query Time
  * Using Sqrt Decomposition: O(sqrt(N)) - Preprocessing Time, O(sqrt(N)) - Query Time

**Segment Tree Implementation** - 

```c++
// --------------------LCA using Euler tour and RMQ--------------------
void fillst(int l, int r, int id)
{
    if(l==r){st[id] = euler[l];return;}

    int mid = (l+r)/2;
    fillst(l,mid,2*id+1);
    fillst(mid+1,r,2*id+2);

    if(h[st[2*id+1]] > h[st[2*id+2]])st[id] = st[2*id+2];
    else
        st[id] = st[2*id+1];
}

int query(int low, int high, int l, int r, int id)
{
    if(l>high || r<low)return -1;
    if(low<=l && high>=r)return st[id];
    int mid = (l+r)/2;

    int left = query(low,high,l,mid,2*id+1);
    int right = query(low,high,mid+1,r,2*id+2);
    if(left==-1)return right;
    if(right==-1)return left;

    if(h[left]>h[right])return right;
    else
        return left;
}

int lca_rmq(int u, int v)
{
    int l = min(first[u],first[v]);
    int r = max(first[u],first[v]);
    int id = query(l,r,0,m-1,0);
    return id;
}

```

---

### LCA using Binary Lifting - O(logN) per query

**Solution Description** - 
* Preprocess - dp matrix, where dp[u][i] stores the 2^i th ancestor of node u
```c++
void fill_dp()
{
    for(int j=1;j<=LOGN;j++)
    {
        for(int i=0;i<n;i++)
        {
            int v = dp[i][j-1];
            if(v!=-1)dp[i][j] = dp[v][j-1];
        }
    }
}
```
* Preprocess - tin - time when node enters in dfs, tout - time when node exits dfs | Not required in standard version

```c++
int lca_binary_lifting_2(int u, int v)
{
    if(h[u] < h[v])swap(u,v);

    int diff = h[u] - h[v];
    for(i=LOGN;i>=0;i--)
    {
        int po = (1<<i);

        if(h[u] - h[v] >= po)u = dp[u][i];
    }
    if(u==v)return u;

    for(i=LOGN;i>=0;i--)
    {
        if(dp[u][i] != -1 && dp[v][i] != -1 && dp[u][i] != dp[v][i])
        {
            u = dp[u][i];
            v = dp[v][i];
        }
    }

    return dp[u][0];
}
```

---

**Alternate Implementation** - 
```c++
bool isancestor(int u, int v)
{
    if(u==-1)return 1;
    if(tin[u] <= tin[v] && tout[u] >= tout[v])return 1;
    return 0;
}

int lca_binary_lifting_1(int u, int v)
{
    if(isancestor(u,v))return u;
    if(isancestor(v,u))return v;

    for(i=LOGN;i>=0;i--)
    {
        if(!isancestor(dp[u][i],v))u = dp[u][i];
    }
    return dp[u][0];
}

```

---

### LCA using Tarjan Offline algorithm - O(DFS call + Number of Queries)

* Each query (u,v) will be answered in single DFS call
* For query(u,v) if we visit u after v then query will be answered at u and vice-versa
* We maintain a DSU, to get the ancestor of previously visited node and that ancestor will be the ans to our lca query

```c++
// ----------------------------------- Tarjan Offline Algorithm -------------------------
int find_set(int u)
{
    if(u==ancestor[u])return u;
    return ancestor[u] = find_set(ancestor[u]);
}

void union_set(int u, int v)  // can apply rank-compression too
{
     u = find_set(u);
     v = find_set(v);
     if(u==v)return;
     ancestor[v] = u;
}

void tarjan_offline(int u, vector<vector<int> >&adj)
{
    visited[u] = 1;
    ancestor[u] = u;

    for(auto v:adj[u])
    if(!visited[v])
    {
       tarjan_offline(v,adj);
       union_set(u,v);

       ancestor[find_set(u)] = u; // Making sure that u becomes representative of its group | using this we can apply rank compression
       ancestor[u] = u; // Making u has its own representative
    }

    for(auto v:queries[u])
    {
        if(visited[v])
        {
            cout<<"lca of "<<u<<" and "<<v<<" is "<<ancestor[find_set(v)]<<endl;
        }
    }
}
```

---
### Final Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int n,edges,m,LOGN,curr,i,j;
vector<int>visited,h,euler,st,tin,tout,ancestor,first;
vector<vector<int> >dp,queries;

bool isancestor(int u, int v)
{
    if(u==-1)return 1;
    if(tin[u] <= tin[v] && tout[u] >= tout[v])return 1;
    return 0;
}
// ----------------DFS to obtain Euler tour and dp[i][0]---------------------
void dfs(int u, vector<vector<int> >&adj,int level, int par)
{
    visited[u] = 1;
    curr++;
    tin[u] = curr;
    curr++;
    h[u] = level;
    dp[u][0] = par;
    first[u] = euler.size();
    euler.pb(u);

    for(auto v:adj[u])
    {
        if(!visited[v]){dfs(v,adj,level+1,u);euler.pb(u);}
    }
    curr++;
    tout[u] = curr;
    curr++;

}

// --------------------LCA using Euler tour and RMQ--------------------
void fillst(int l, int r, int id)
{
    if(l==r){st[id] = euler[l];return;}

    int mid = (l+r)/2;
    fillst(l,mid,2*id+1);
    fillst(mid+1,r,2*id+2);

    if(h[st[2*id+1]] > h[st[2*id+2]])st[id] = st[2*id+2];
    else
        st[id] = st[2*id+1];
}

int query(int low, int high, int l, int r, int id)
{
    if(l>high || r<low)return -1;
    if(low<=l && high>=r)return st[id];
    int mid = (l+r)/2;

    int left = query(low,high,l,mid,2*id+1);
    int right = query(low,high,mid+1,r,2*id+2);
    if(left==-1)return right;
    if(right==-1)return left;

    if(h[left]>h[right])return right;
    else
        return left;
}

int lca_rmq(int u, int v)
{
    int l = min(first[u],first[v]);
    int r = max(first[u],first[v]);
    int id = query(l,r,0,m-1,0);
    return id;
}
// ----------------------------------------------------------------------------------------

// ----------------LCA using binary lifting both versions---------------------------------

void fill_dp()
{
    for(int j=1;j<=LOGN;j++)
    {
        for(int i=0;i<n;i++)
        {
            int v = dp[i][j-1];
            if(v!=-1)dp[i][j] = dp[v][j-1];
        }
    }
}

int lca_binary_lifting_1(int u, int v)
{
    if(isancestor(u,v))return u;
    if(isancestor(v,u))return v;

    for(i=LOGN;i>=0;i--)
    {
        if(!isancestor(dp[u][i],v))u = dp[u][i];
    }
    return dp[u][0];
}

int lca_binary_lifting_2(int u, int v)
{
    if(h[u] < h[v])swap(u,v);

    int diff = h[u] - h[v];
    for(i=LOGN;i>=0;i--)
    {
        int po = (1<<i);

        if(h[u] - h[v] >= po)u = dp[u][i];
    }
    if(u==v)return u;

    for(i=LOGN;i>=0;i--)
    {
        if(dp[u][i] != dp[v][i])
        {
            u = dp[u][i];
            v = dp[v][i];
        }
    }

    return dp[u][0];
}
//-------------------------------------------------------------------------------------

// ----------------------------------- Tarjan Offline Algorithm -------------------------
int find_set(int u)
{
    if(u==ancestor[u])return u;
    return ancestor[u] = find_set(ancestor[u]);
}

void union_set(int u, int v)  // can apply rank-compression too
{
     u = find_set(u);
     v = find_set(v);
     if(u==v)return;
     ancestor[v] = u;
}

void tarjan_offline(int u, vector<vector<int> >&adj)
{
    visited[u] = 1;
    ancestor[u] = u;


    for(auto v:adj[u])
    if(!visited[v])
    {
       tarjan_offline(v,adj);
       union_set(u,v);

       ancestor[find_set(u)] = u; // Making sure that u becomes representative of its group | using this we can apply rank compression
       ancestor[u] = u; // Making u has its own representative
    }

    for(auto v:queries[u])
    {
        if(visited[v])
        {
            cout<<"lca of "<<u<<" and "<<v<<" is "<<ancestor[find_set(v)]<<endl;
        }
    }
}

// -------------------------------------------------------------------------------------

void solve(int test)
{
    cin>>n>>edges;
    LOGN = 0;
    while((1<<LOGN) <= n)LOGN++;
    LOGN++;
    cout<<LOGN<<endl;


    visited.resize(n,0);
    h.resize(n,0);
    euler.clear();
    tin.resize(n,-1);
    tout.resize(n,-1);
    first.resize(n,-1);
    curr = 0;

    dp.resize(n,vector<int>(LOGN+1,-1));

    vector<vector<int> >adj(n);
    for(i=0;i<edges;i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs(0,adj,0,-1);
    m = euler.size();
    st.resize(4*m,0);
    fillst(0,m-1,0);
    fill_dp();


    int q;
    cin>>q;

    queries.clear();
    queries.resize(n);

    while(q--)
    {
        int u,v;
        cin>>u>>v;

        queries[u].pb(v);
        queries[v].pb(u);
        //cout<<h[u]<<" "<<h[v]<<endl;

        cout<<lca_rmq(u,v)<<" ";
        cout<<lca_binary_lifting_1(u,v)<<" ";
        cout<<lca_binary_lifting_2(u,v)<<endl;
    }

    cout<<endl;

    cout<<"Now using tarjan offline algorithm: "<<endl;

    ancestor.resize(n,-1);
    for(i=0;i<n;i++){visited[i] = 0;ancestor[i] = i;}

    tarjan_offline(0,adj);

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
12 11
0 1
0 2
0 3
1 8
1 10
2 4
2 5
3 6
3 7
4 9
5 11
8
9 11
5 6
4 11
4 5
9 4
8 0
6 9
10 1
*/
```
