// Algorithm description - O(V * E^2)
// Idea of Ford - Fulkerson algorithm is that we always try to find a path with non-zero flow in residual graph from source to sink
// then update the residual graph accordingly.
// See notes also for terminology.


#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

int n,m,i,j;
vector<vector<int> >cap,flow;
vector<int>parent;

int bfs(int s, int t)
{
    queue<pair<int,int> >q;
    q.push(mp(s,INF));

    while(!q.empty())
    {
        int u = q.front().first;
        int f = q.front().second;
        q.pop();

        for(i=0;i<n;i++)
        {
            if(i==s || i==u)continue;

            if(parent[i] == -1 && cap[u][i] - flow[u][i] > 0)
            {
                parent[i] = u;
                q.push(mp(i,min(f,cap[u][i] - flow[u][i])));
                if(i==t)
                    return min(f,cap[u][i] - flow[u][i]);
            }
        }
    }
    return 0;

}

void solve(int test)
{
    cin>>n>>m;
    cap.resize(n,vector<int>(n,0));
    flow.resize(n,vector<int>(n,0));
    parent.resize(n);

    for(i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        cap[a][b] = c;
    }

    int s,t;
    cin>>s>>t;
    int ans = 0;

    while(1)
    {
        fill(parent.begin(),parent.end(),-1);
        int x = bfs(s,t);
        //cout<<x<<endl;
        if(x==0)break;
        ans +=x;
        int temp = t;
        while(temp!=s)
        {
            int p = parent[temp];
            flow[p][temp] += x;
            flow[temp][p] -= x;
            temp = p;
        }
    }

    cout<<"Max flow is: "<<ans<<endl;

    fill(parent.begin(),parent.end(),-1);
    bfs(s,t);

    cout<<"s t min-cut is : ";
    for(i=0;i<n;i++)
    {
        if(i==s || parent[i] != -1)cout<<i<<" ";
    }
    cout<<endl;

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
