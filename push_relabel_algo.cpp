// Algorithm description - see in notes
// version 1 - Time Complexity - O(V^2 * E)
// version 2 - Time Complexity - O(VE + V^2 * E^0.5) ~= O(V^3)

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int n,m,i,j;
vector<vector<int> >cap,flow,adj;
vector<int>h,excess,seen;
queue<int>excess_vertices;

// function to push from u to v max amount possible. And update excess of v and accordingly push in excess_vertices queue if necessary
void push(int u, int v)
{
    int d = min(excess[u], cap[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[v] += d;
    excess[u] -= d;
    if(d && excess[v] == d){cout<<"pushed from "<<u<<" to "<<v<<endl;excess_vertices.push(v);  } // first condition to check if there is any transfer and second to check if it already in queue.
}

// update height of u as the min height of pushable vertex + 1
void relabel(int u)
{
    int d = INT_MAX;
    for(i=0;i<n;i++)
    {
        if(cap[u][i] - flow[u][i] > 0)d = min(d, h[i]);
    }
    if(d != INT_MAX)
    h[u] = d + 1;
}

// function to check all the neighbors in a circular manner and push in them accordingly, if not pushable then move to next. 
// If no next then relabel and start again from 1st neighbor
void discharge(int u)
{
    while(excess[u] > 0)
    {
        int v = seen[u];
        if(v < n)
        {
            if(cap[u][v] - flow[u][v] > 0 && h[u] > h[v])
                push(u,v);
            else
                seen[u]++;
        }
        else
        {
            relabel(u);
            seen[u] = 0;
        }
    }
}
// function to extract all the vertices other than source and sink whose excess is greater than 0 and have height == max among them.
vector<int> max_height_vertices(int s, int t)
{
    vector<int>vert;
    for(i=0;i<n;i++)
    {
        if(i==s || i==t || excess[i] <= 0)continue;
        if(!vert.empty() && h[vert[0]] < h[i])vert.clear();
        if(vert.empty() || h[vert[0]] == h[i])vert.pb(i);
    }
    return vert;
}

// 1st version of push relabel algo
// 1). First make labelling valid by pushing from source to all its neighbor and updating queue excess_Vertices accordingly.
// 2). Now as long as queue is not empty pop and discharge u if u is not source or sink.
void push_relabel_1(int s, int t)
{
    fill(excess.begin(),excess.end(),0);
    fill(h.begin(),h.end(),0);
    fill(seen.begin(),seen.end(),0);

    while(!excess_vertices.empty())excess_vertices.pop();

    h[s] = n;
    excess[s] = INF;
    for(i=0;i<n;i++)
    {
        if(cap[s][i] - flow[s][i] > 0){push(s,i);}
    }

    while(!excess_vertices.empty())
    {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if(u!=s && u!=t)discharge(u);
    }

    int ans = 0;

    for(i=0;i<n;i++)ans += flow[i][t];

    cout<<"Maximum flow is : ";
    cout<<ans<<endl;
}

// 2nd version of push relabel more efficient 
// 1). First make labelling valid by pushing from source to all its neighbor and updating queue excess_Vertices accordingly.
// 2). Run a while loop containing all the active vertices of max height. Push from them, if anyone of them is not pushed then relabel it and break
// because heights have changed.

void push_relabel_2(int s, int t)
{
    fill(excess.begin(),excess.end(),0);
    fill(h.begin(),h.end(),0);
    fill(seen.begin(),seen.end(),0);


    h[s] = n;
    excess[s] = INF;
    for(i=0;i<n;i++)
    {
        if(cap[s][i] - flow[s][i]){push(s,i);}
    }

    while(1)
    {
        vector<int>curr = max_height_vertices(s,t);
        if(curr.empty())break;

        for(auto v:curr)
        {
            bool pushed = 0;
            for(i=0;i<n && excess[v];i++)
            {
                if(cap[v][i] - flow[v][i] > 0 && h[v] == h[i] + 1)
                {push(v,i); pushed = 1;}
            }
            if(!pushed){relabel(v);break;}
        }
    }
    int ans = 0;
    for(i=0;i<n;i++)ans += flow[i][t];

    cout<<"Maximum flow is : ";
    cout<<ans<<endl;
}

void solve(int test)
{
    cin>>n>>m;
    adj.resize(n,vector<int>(n,0));
    cap.resize(n,vector<int>(n,0));
    flow.resize(n,vector<int>(n,0));
    seen.resize(n);
    excess.resize(n);
    h.resize(n);

    for(i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        cap[a][b] = c;
        adj[a][b] = c;
    }

    int s,t;
    cin>>s>>t;

    push_relabel_1(s,t);

    for(i=0;i<n;i++)for(j=0;j<n;j++){cap[i][j] = adj[i][j]; flow[i][j] = 0;}

    push_relabel_2(s,t);

}

int main()
{
  int t = 1;
  cin>>t;

  for(int x=1;x<=t;x++)
  {
      solve(x);
  }
  return 0;
}
/*
1
6 9
0 1 7
0 4 4
4 1 3
1 2 5
1 3 3
4 3 2
3 2 3
3 5 5
2 5 8
0 5
*/

/*
1
6 8
0 1 10
0 4 12
4 1 5
1 2 15
4 3 6
2 3 8
3 5 17
2 5 3
0 5
*/
