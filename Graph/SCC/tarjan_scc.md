
**Tarjan Algorithm for SCC** - `O(n+m)`
[Link](https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/)
* **Idea** - A head of SCC will have `low[u] == tin[u]`
* Start dfs by intializing low[u] = tin[u] = curr and **pushing u in stack and marking instack[u] = 1;**
* Now visit all its neighbors, if neighbor is unvisited then call dfs from there and after that update `low[u] = min(low[u],low[neighbor]);`
* If neighbor is already visited then check **if it is in stack then only update low[u] = min(low[u],tin[neighbor]);**
* Finally, `If (low[u] == tin[u])` then all the elements in stack **till u** will be part of same scc.

```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

vector<int>tin,low,instack,visited;
int curr,cnt;
stack<int>st;
vector<vector<int> >scc;
vector<int>v_to_scc;

void dfs(int u, vector<vector<int> >&adj)
{
    curr++;
    tin[u] = low[u] = curr;
    visited[u] = 1;
    st.push(u);
    instack[u] = 1;
    //cout<<u<<endl;

    for(auto x:adj[u])
    {
        if(!visited[x])
        {
            dfs(x,adj);
            low[u] = min(low[u],low[x]);
        }
        else if(instack[x] == 1)  // IMPORTANT CHECK
        {
            low[u] = min(low[u],tin[x]);
        }
    }

    if(low[u] == tin[u])   // head of scc find
    {
        vector<int>v;
        while(!st.empty() && st.top()!=u)
        {
           int x = st.top();
           v.pb(x);
           instack[x] = 0;
           v_to_scc[x] = cnt;
           st.pop();
        }
        v.pb(u);
        v_to_scc[u] = cnt;
        instack[u] = 0;
        st.pop();
        scc.pb(v);
        cnt++;
    }
}



void solve(int test)
{
    int n,m;
    cin>>n>>m;

    tin.resize(n,0);
    low.resize(n,0);
    instack.resize(n,0);
    visited.resize(n,0);
    v_to_scc.resize(n,-1);
    curr = 0,cnt = 0;
    int i,j;

    vector<vector<int> >adj(n);
    for(i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a].pb(b);
    }

    for(i=0;i<n;i++)
    {
        if(!visited[i])dfs(i,adj);
    }

    for(i=0;i<n;i++)cout<<v_to_scc[i]<<" ";
    cout<<endl;

    for(auto v:scc)
    {
        for(auto x:v)cout<<x<<" ";
        cout<<endl;
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
3 3
1 2
0 1
2 1
*/
```
