[Link](https://cp-algorithms.com/graph/mst_kruskal.html) | [Link](https://cp-algorithms.com/graph/mst_kruskal_with_dsu.html)

**Kruskal Algorithm Time Complexity** - 
* _Brute Implementation_ - `O(MlogN + N^2)`
  * First part is from sorting the edge
  * Second part is from performing O(N) merge operation N-1 times 
* _DSU Implementation_ - `O(MlogN + N + M)`
  * First part is from sorting edges
  * second part is from making parent array
  * third part is from doing union under assumption that DSU union and find_parent take amortized O(1) time. 
  * We can achieve amortized O(1) using rank-compression method.

**Some IMP points about MST** - 
* Maximum spanning tree can be obtained by negating weights and then finding MST
* Minimum Product spanning tree will be equivalent to finding MST (as we can take logarithm of edge weights)


```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6
int find_parent(int a, vector<int>&parent)
{
    if(parent[a] == a)return a;
    parent[a] = find_parent(parent[a], parent);
    return parent[a];
}

void union_set(int a, int b, vector<int>&parent, vector<int>&rank)
{
    int x = find_parent(a, parent);
    int y = find_parent(b, parent);
    if(x==y)return;
    if(rank[x] > rank[y]){parent[y] = x;return;}
    if(rank[x] < rank[y]){parent[x] = y;return;}
    if(rank[x]==rank[y]){parent[y] = x;rank[x]++;return;}
}

void kruskal_brute(vector<vector<int> >&edges, int n)
{
   vector<int>parent(n);
   int i,j;
   for(i=0;i<n;i++)parent[i] = i;

   int total = 0;

   vector<vector<int> >result;

   for(auto e:edges)
   {
       if(result.size()==n-1)break;
       if(parent[e[0]] == parent[e[1]])continue;
       total += e[2];
       result.pb(e);

       int old_id = parent[e[0]];
       int new_id = parent[e[1]];

       for(i=0;i<n;i++)
       {
           if(parent[i] == old_id)parent[i] = new_id;
       }
   }

   cout<<total<<endl;

   for(auto e:result)
   {
       cout<<e[0]<<" "<<e[1]<<" "<<e[2]<<endl;
   }
}

void kruskal_dsu(vector<vector<int> >&edges, int n)
{
    vector<int>parent(n);
    vector<int>rank(n,0);
    int i,j;
    for(i=0;i<n;i++)parent[i] = i;
    int total =0;
    vector<vector<int> >result;

    for(auto e:edges)
    {
        if(result.size()==n-1)break;
        int u = find_parent(e[0],parent);
        int v = find_parent(e[1],parent);
        if(u==v)continue;

        total += e[2];
        result.pb(e);
        union_set(u,v, parent, rank);
    }

   cout<<total<<endl;

   for(auto e:result)
   {
       cout<<e[0]<<" "<<e[1]<<" "<<e[2]<<endl;
   }

}

void solve(int test)
{
   int n,m;
   cin>>n>>m;

   vector<vector<int>>edges(m);
   int i,j;

   for(i=0;i<m;i++)
   {
       int a,b,c;
       cin>>a>>b>>c;
       edges[i] = {a,b,c};
   }

    sort(edges.begin(),edges.end(), [ ]( const vector<int>& lhs, const vector<int>& rhs )
    {
       return lhs[2] < rhs[2];
    });

   // Time Complexity = O(n^2)
   kruskal_brute(edges,n);
   // Time Complexity = O(mlogn + n + m) , first part is sorting, second is making parent array,
   // third is main step assuming all dsu operation takes place in O(1)
   kruskal_dsu(edges,n);

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
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/
```


