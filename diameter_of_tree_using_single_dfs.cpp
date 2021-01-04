#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back

int diameter(int u, int par, vector<vector<int> >&adj, int* curr_max)
{
    int max1 = 0, max2 = 0, total = 0;
    
    // total will contain the length of longest path in the subtree rooted at u.
    // curr_max will maintain length of longest path starting from u in that subtree.

    for(auto v:adj[u])
    {
        if(v==par)continue;

        total = max(total, diameter(v,u,adj,curr_max));

        if(*curr_max>max1)
        {
            max2 = max1;
            max1 = *curr_max;
        }
        else
            max2 = max(max2, *curr_max);
    }

    total = max(total, max1 + max2);
 
    *curr_max = max1 + 1;

    return total;

}

void solve(int test)
{
   int n;
   cin>>n;

   vector<vector<int> >adj(n);

   int i,j;

   for(i=0;i<n-1;i++)
   {
       int a,b;
       cin>>a>>b;
       adj[a].pb(b);
       adj[b].pb(a);
   }

   int curr_max = 0;
   int diam = diameter(0,-1,adj,&curr_max);

   cout<<diam<<endl;

}

int main()
{

  int t = 1;
  //cin>>t;

  for(int x=1;x<=t;x++)
  {
      solve(x);
  }
  return 0;
}


/*
sample input
8
0 7
1 5
2 0
4 2
6 7
7 3
7 5
*/
