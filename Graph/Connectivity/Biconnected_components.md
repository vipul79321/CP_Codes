**Biconnected Graphs** - A graph is said to be biconnected if it is connected and doesnt have any articulation points

**Problem Description** - Given a undirected graph (as we generally work with undirected graphs in case of bridges and APs), we need to output its all biconnected components.

---
**NOTE** - All biconnected components are edge disjoint. They may or may not be vertex disjoint

---
**NOTE** - While pushing edges to stack during dfs, we only push two types of edges
* Tree edge (u,v) - That is v is discovered first time
* Back edge (u,v) - v has been discovered already and before u and tin[v] < tin[u]
---

**Solution Approach** - O(n+m)
[Hackerearth-Link](https://www.hackerearth.com/practice/algorithms/graphs/biconnected-components/tutorial/) | [GFG link](https://www.geeksforgeeks.org/biconnected-components/)
* call dfs for each connected component
* In dfs we mark u as visited and intialize tin,low;
* Now visit all its neighbor v, 
  * if v unvisited, then push edge u-v in stack, call dfs from that neighbor and then update `low[u] = min(low[u],low[v])`
    * if u is an articulation point then pop and print from stack till edge u-v
  * If `v != parent[u]` and `visited[v]`:
    * `low[u] = min(low[u], tin[v])`
    * if `tin[v] < tin[u]`  -->back edge condition 
      * then push(u,v) to stack.
* Finally if one connected component is visited then print all content of stack.


```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

vector<int>tin,low,visited;
int curr,cnt;
stack<pair<int,int> >st;

void print_bcc(int u,int v)
{
    while(!st.empty() && st.top().first != u && st.top().second!=v)
    {
        cout<<st.top().first<<" "<<st.top().second<<" , ";
        st.pop();
    }
    if(!st.empty())
    {cout<<st.top().first<<" "<<st.top().second<<" end";st.pop();}
    cout<<endl;
    return;
}

void dfs(int u, vector<vector<int> >&adj,int par)
{
    curr++;
    tin[u] = low[u] = curr;
    visited[u] = 1;
    int child = 0;

    for(auto v:adj[u])
    {
        if(!visited[v])
        {
            st.push(mp(u,v)); // pushing tree edge in stack
            dfs(v,adj,u);
            low[u] = min(low[u],low[v]);
            child++;

            if(par != -1 && low[v] >= tin[u])
            {
                print_bcc(u,v);
            }
            if(par == -1 && child>1)
            {
                print_bcc(u,v);
            }
        }
        else if(v!= par)
        {
            low[u] = min(low[u],tin[v]);
           // IMPORTANT CHECK - Making sure u->v goes from descendant to parent and hence a back-edge and then only pushing it in stack. This is to avoid taking same edge two times
           if(tin[u] > tin[v])
            st.push(mp(u,v));
        }
    }

}

void solve(int test)
{
    int n,m;
    cin>>n>>m;

    tin.resize(n,0);
    low.resize(n,0);
    visited.resize(n,0);

    curr = 0,cnt = 0;
    int i,j;

    vector<vector<int> >adj(n);
    for(i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    for(i=0;i<n;i++)
    {
        if(!visited[i])dfs(i,adj,-1);
        while(st.size()>1)
        {
            cout<<st.top().first<<" "<<st.top().second<<" , ";
            st.pop();
        }
        if(st.size()==1)
        {
            cout<<st.top().first<<" "<<st.top().second<<" end";
            st.pop();
            cout<<endl;
        }

    }

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
Hackerearth code fails on following input but gfg one works
1
4 5
0 1
1 2
2 3
3 0
3 1
*/

/*
1
6 10
0 1
0 2
1 2
1 3
2 3
2 4
3 5
3 4
4 5
2 4
*/
/*
1
3 2
1 2
0 1
*/

```
