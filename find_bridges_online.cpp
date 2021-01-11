// A 2 edge component is component from which we can remove 1 or less edge and it will still remain connected.


#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

// par = represents parent of that vertex in 2ecc tree.
// dsu_cc[u] = representative of connected component of u.
// dsu_cc_size[u] = size of u's connected component.
// dsu_2ee[u] = representative of 2edge connected component of u.


vector<int> par, dsu_2ecc, dsu_cc, dsu_cc_size;
int bridges;
int lca_iteration;
vector<int> last_visit;

int find_2ecc(int u)   // standard dsu stuff
{
    if(u == -1)return -1;
    if(u == dsu_2ecc[u])return u;
    return dsu_2ecc[u] = find_2ecc(dsu_2ecc[u]);
}

int find_cc(int u)  // standard dsu stuff
{
    u = find_2ecc(u);   // ***************
    if(dsu_cc[u] == u)return u;
    return dsu_cc[u] = find_cc(dsu_cc[u]);
}
void make_root(int u)
{
    u = find_2ecc(u);  // first we will find 2ecc representative of u
    int root = u;     // our final root
    int child = -1;

    while(u!=-1)   // Now we will traverse up in 2ecc tree of u and reverse edge.
    {
        int p = find_2ecc(par[u]);   // next = find_2ecc(par[u]);
        par[u] = child;       // curr->next = prev;
        dsu_cc[u] = root;
        child = u;   //prev = curr;
        u = p;     // curr = next;
    }
    dsu_cc_size[root] = dsu_cc_size[child];
}

void merge_path(int a, int b)
{
    lca_iteration++;   // To identify whether a vertex is visited in that iteration or not;
    vector<int>path_a,path_b;
    int lca = -1;
    
    while(lca==-1)
    {
        if(a!= -1)
        {
            a = find_2ecc(a);    // find representative node of a
            path_a.pb(a);  // push in path_a
            if(last_visit[a] == lca_iteration){lca = a;break;}  // if already visited then lca found

            last_visit[a] = lca_iteration;    // update last visit
            a = par[a];         // move up the tree
        }
        if(b!= -1)
        {
            b = find_2ecc(b);   // find representative node of a
            path_b.pb(b);   // push in path_a
            if(last_visit[b] == lca_iteration){lca=b; break;}  // if already visited then lca found

            last_visit[b] = lca_iteration;  // update last visit
            b =par[b];  // move up the tree
        }
    }

    for(auto v:path_a)
    {
        dsu_2ecc[v] = lca;   // unioning all the 2ecc in path and compress the graph
        if(v==lca)break;

        bridges--;
    }
    for(auto v:path_b)
    {
        dsu_2ecc[v] = lca;  // unioning all the 2ecc in path and compress the graph
        if(v==lca)break;

        bridges--;
    }
}

void add_edge(int a, int b)
{
     // 1). if a and b are in same 2ecc then do nothing.
     // 2). if a and b are in different 2ecc but in same cc then what will happen is 2ecc tree containing a and b will have a cycle and therefore gets compressed and number of bridges will reduce.
     // 3). if a and b are in different2ecc and cc then bridge count will increase. Now we will have to update 2ecc tree by make an edge from 2ecc of a to 2ecc of b


     a = find_2ecc(a);
     b = find_2ecc(b);

    if(a==b)return;

    int ca = find_cc(a);
    int cb = find_cc(b);
    if(ca!=cb)
    {
        bridges++;
        if(dsu_cc_size[ca] > dsu_cc_size[cb])
        {
            swap(a,b);
            swap(ca,cb);
        }
        make_root(a);
        par[a] = b;    
        dsu_cc[a] = b;   // ********
        dsu_cc_size[cb] += dsu_cc_size[a];
    }
    else
    {
        merge_path(a,b);
    }
}

void solve(int test)
{

   int n,m;
   cin>>n>>m;

   int i,j;
   par.resize(n,-1);
   dsu_2ecc.resize(n,-1);
   dsu_cc.resize(n,-1);
   dsu_cc_size.resize(n,1);
   last_visit.resize(n,-1);
   bridges = 0;
   lca_iteration = 0;

   for(i=0;i<n;i++)dsu_cc[i] = dsu_2ecc[i] = i;

   for(i=0;i<m;i++)
   {
       int a,b;
       cin>>a>>b;
       add_edge(a,b);
       cout<<bridges<<endl;
       //for(auto t:dsu_cc)cout<<t<<" ";cout<<endl;
       //for(auto t:dsu_2ecc)cout<<t<<" ";cout<<endl;
       //for(auto t:dsu_cc_size)cout<<t<<" ";cout<<endl;
       //for(auto t:par)cout<<t<<" ";cout<<endl;
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
