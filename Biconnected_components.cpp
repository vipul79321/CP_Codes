// Link to hackerearth tutorial - https://www.hackerearth.com/practice/algorithms/graphs/biconnected-components/tutorial/
// Algorithm description - O(n+m)
// In dfs we mark u as visited and intialize tin,low;
// 1). Now visit all its neighbor, if a neighbor is unvisited, then push edge u-v in stack, call dfs from that neighbor and then update low[u] = min(low[u],low[v])
// if u is an articulation point then pop and print from stack till edge u-v
// 2). If v != parent[u] && tin[v] < low[u] -->back edge condition and also condition for imrovement in low, then low[u] = tin[v] and push(u,v) to stack.
// Finally if one connected component is visited then print all content of stack.

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
            st.push(mp(u,v));
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
        else if(v!= par && tin[v] < low[u])  // IMPORTANT CHECK
        {
            low[u] = tin[v];
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
