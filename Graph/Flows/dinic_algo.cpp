// Link to video tutorial - https://www.youtube.com/watch?v=M6cm8UeeziI&list=PLDV1Zeh2NRsDj3NzHbbFIC58etjZhiGcG&index=10
// Algorithm description - Time Complexity O(V^2 * E)
// 1).Do BFS in residual graph and assign level to each node. If sink not reachable return current flow as answer
// 2).Flow u-v only when level[u] +1 = level[v] and cap[u][v] - flow[u][v] > 0
// 3).After obtaining level, reset adj list pointer for each vertex to 0
// 4).Now call dfs from source as long as non-zero value is returned.
// Repeat step 1-4

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int n,m,i,j,s,t;
vector<vector<int> >cap,flow;
vector<int>ptr;   // To store ptr of v in its adjacency matrix during one iteration of innner while loop.
vector<int>level; // To store level of each node during one iteration of outer while loop
queue<int>q;

void bfs()    // Standard BFS along edges with positive residual capacity
{
    while(!q.empty())
    {
        int u = q.front();q.pop();

        for(i=0;i<n;i++)
        {
            if(level[i] == -1 && cap[u][i] - flow[u][i] > 0)
            {
                level[i] = level[u] + 1;
                q.push(i);
            }
        }

    }
}
// Important part
int dfs(int u, int min_flow)
{
    if(min_flow == 0)return 0;   // If minimum flow is already 0 that is not possible then return 0
    if(u==t)return min_flow;   // If sink reached then return current value of possible flow


    // loop through all its next neighbors and call dfs to its neighbor at next level and positive residual flow.
    for(ptr[u];ptr[u]<n;ptr[u]++)
    {
        int v = ptr[u];
        if(level[v] == level[u] + 1 && cap[u][v] - flow[u][v] > 0)
        {

            int fl = dfs(v, min(min_flow, cap[u][v] - flow[u][v]));

            if(fl==0)continue;
            flow[u][v] += fl;
            flow[v][u] -= fl;
            return fl;
        }
    }
    return 0;
}


void solve(int test)
{
    cin>>n>>m;

    cap.resize(n,vector<int>(n,0));
    flow.resize(n,vector<int>(n,0));
    level.resize(n,-1);
    ptr.resize(n);

    for(i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        cap[a][b] = c;
    }


    cin>>s>>t;

    int ans = 0;

    while(1)
    {
        fill(level.begin(),level.end(),-1);
        level[s] = 0;
        while(!q.empty())q.pop();
        q.push(s);
        bfs();
        if(level[t] == -1)break;

        fill(ptr.begin(),ptr.end(),0);

        while(1)
        {
            int x = dfs(s,INF);
            if(x<=0)break;
            ans+=x;
        }
    }

    cout<<ans<<endl;

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
