**Condition for Euler path or cycle in directed graph is** - 
* Indegree[u] == outdegree[u], for atleast n-2 vertices
* All vertices should be part of same SCC.

**Condition for Euler path or cycle in undirected graph is** - 
* All vertices should have even degree, atleast n-2 vertices.
* All vertices should be connected.

**HeirHolzer algorithm for finding Euler path or cycle whichever exist** - 
* Time Complexity = `O(m + nlogn)` for undirected graph, have to use vector of multiset to represent adjacency list
* Time Complexity = `O(m)` for directed graph
* Time Complexity = `O(m + n*n)` for adjacency matrix representation
* Following cases arise - 
  * If number of odd degree vertices is greater than 2 then no euler path or cycle
  * If no odd degree vertices then there exist a Euler cycle.
  * If odd degree vertices are 2 then there exist a Euler path. In this case **add an edge between odd vertices** and find euler cycle. See note below to further handle this case

**NOTE** - In result array which we obtain from finding euler cycle, `result[0] == result.back()`

**Code Description** - 
* Push any node in stack
* While stack is not empty
  * u = st.top(); 
  * if `adj[u].size() == 0, push u to result array` and pop stack
  * else:
    * v = adj[u].begin(); push v to stack
    * remove v from adj[u] and remove u from adj[v] (in case of undirected graph)
* Result array will contain the euler cycle, with `result[0] == result.back()`

**NOTE** - 
* If we added an edge to handle odd degree vertices then to print euler path do this - 
  * Let odd degree vertices be v1 and v2
  * Find index result array such that result[i] == v1 && result[i+1] == v2 or vice versa, let call that index `id` 
  * `print result from (id + 1 to result.size() - 1)`
  * `print result from (1 to id)`

```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define INF 1e6

void solve(int test)
{
   int n,m;
   cin>>n>>m;

   vector<multiset<int> >adj(n);
   int i,j;

   for(i=0;i<m;i++)
   {
       int a,b;
       cin>>a>>b;
       adj[a].insert(b);
       adj[b].insert(a);
   }

   vector<int>deg(n,0);
   int odd = 0;
   int v1 = -1,v2 = -1;
   for(i=0;i<n;i++)
   {
       deg[i] = adj[i].size();
       cout<<deg[i]<<" ";
       if(deg[i]%2==1){odd++;v2 = v1; v1 = i;}
   }
   cout<<endl;

   if(odd>2)
   {
       cout<<"No euler path or cycle"<<endl;
       return;
   }
   if(odd == 2)
   {
       adj[v1].insert(v2);
       adj[v2].insert(v1);
   }

   stack<int>s;
   s.push(0);

   vector<int>res;
   while(!s.empty())
   {
       int u = s.top();

       if(adj[u].size()==0)
       {
           res.pb(u);
           s.pop();
       }
       else
       {
           int v = *adj[u].begin();
           adj[u].erase(adj[u].begin());
           auto it = adj[v].find(u);   // first find one iterator pointing to u. Because simply calling multiset.erase(value) removes all instances of that value.
           adj[v].erase(it);
           s.push(v);
       }
   }

   for(i=0;i<n;i++)
   {
       if(adj[i].size()!=0)
       {
           cout<<"No euler path or cycle exist because of disconnectedness"<<endl;
           return;
       }
   }


   if(odd==2)
   {
       vector<int>path;
       int id = -1;
       for(i=0;i<res.size()-1;i++)
       {
           if(res[i] == v1 && res[i+1] == v2){id=i;break;}
           if(res[i] == v2 && res[i+1] == v1){id=i; break;}
       }

       for(i=id+1;i<res.size();i++)path.pb(res[i]);
       for(i=1;i<=id;i++)path.pb(res[i]);    // start from i = 1 because res[res.size()-1] == res[0] because it was a euler cycle ******

       cout<<"Euler path found"<<endl;
       for(auto v:path)cout<<v<<" ";
       cout<<endl;
       return;
   }
   cout<<"Euler cycle found"<<endl;

   for(auto v:res)cout<<v<<" ";
   cout<<endl;

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
graph with Euler cycle and one isolated vertex
1
7 10
0 1
0 2
1 2
1 3
2 3
2 4
3 5
3 4
4 5
1 4
*/
/*
graph with even degree but disconnected
1
7 11
0 1
0 2
1 2
1 3
2 3
2 4
3 5
3 4
4 5
1 4
6 6
*/

```
