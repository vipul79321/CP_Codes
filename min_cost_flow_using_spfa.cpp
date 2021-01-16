// Min cost problem - Find minimum cost for the desired flow in the network
// Algorithm description - O(n*m) * Time for each shortest path
// 1). Assumption if u->v exist then v<-u doesnt exist.
// 2). For each edge u->v add edge v->u with cap = 0  and cost[v][u] = - cost[u][v]
// 3). As long as path exist from s-t in residual graph find shortest path and then allowed flow.
// 4). update cost as dist[t] * allowed
// Do this till required flow isnt achieved or not possible.

// For case of undirected graph, consider each edge u-v as two edges u->v and v<-u.
// Now graph has become directed, and for each directed edge, add its reverse edge to graph with cap = 0 and cost its negative.
// Now solve it usually. One idea to store such graph is adj matrix of pair 
//where pair.first will store the index of original edge and pair.second will store the index of reversed edge with cap 0 and cost its negative



#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int n,m,i,j,s,t;
vector<vector<int> >cap,flow,cost;
vector<int>parent,dist;

int spfa(int s, int t)
{
    fill(parent.begin(),parent.end(),-1);
    fill(dist.begin(),dist.end(),INF);
    queue<int>q;
    vector<int>inqueue(n,0);

    q.push(s);
    inqueue[s] = 1;
    dist[s] = 0;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        inqueue[u] = 0;

        for(i=0;i<n;i++)
        {
            if(cap[u][i] - flow[u][i] > 0 && dist[u] + cost[u][i] < dist[i])
            {
                parent[i] = u;
                dist[i] = dist[u] + cost[u][i];
                if(inqueue[i] == 0)
                {q.push(i);inqueue[i] = 1;}
            }
        }
    }

    if(parent[t] == -1)
        return 0;
    return 1;
}


void solve(int test)
{
    cin>>n>>m;

    cap.resize(n,vector<int>(n,0));
    flow.resize(n,vector<int>(n,0));
    cost.resize(n,vector<int>(n,0));
    parent.resize(n);
    dist.resize(n);

    for(i=0;i<m;i++)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        cap[a][b] = c;
        cap[b][a] = 0;
        cost[a][b] = d;
        cost[b][a] = -d;
    }

    cin>>s>>t;

    int k;
    cin>>k;
    int ans = 0;
    int min_cost = 0;

    while(spfa(s,t) && ans < k)
    {
        int allow = k-ans;

        int curr = t;
        while(curr != s)
        {
            allow = min(allow, cap[parent[curr]][curr] - flow[parent[curr]][curr]);
            curr = parent[curr];
        }

        ans += allow;
        min_cost += dist[t] * allow;
        curr = t;

        while(curr != s)
        {
            flow[parent[curr]][curr] += allow;
            flow[curr][parent[curr]] -= allow;
            curr = parent[curr];
        }

    }


   if(ans == k || k== INF)
    cout<<"Minimum cost of "<<ans<<" flow is : "<<min_cost<<endl;
   else
    cout<<"-1"<<endl;





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
8 15
0 1 1 0
0 2 1 0
0 3 1 0
4 7 1 0
5 7 1 0
6 7 1 0
1 4 1 5
1 5 1 1000
1 6 1 1000
2 4 1 1000
2 5 1 5
2 6 1 1000
3 4 1 1000
3 5 1 1000
3 6 1 5
0 7
2
*/
