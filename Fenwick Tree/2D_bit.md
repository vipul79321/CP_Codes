### 2-Dimensional Binary Indexed Tree
[Link](https://cp-algorithms.com/data_structures/fenwick.html#toc-tgt-6) | [Link](https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees#2d)

* Time Complexity for each query - `O(log(max_x) * log(max_y))`
* **sum(x,y)** - Returns sum from (0,0) to (x,y)
* **update(x,y,val)** - Update value at (x,y) with val

```c++
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back

int max_x, max_y;
vector<vector<int> >bit;

void update(int x, int y, int val)
{
    x++,y++;
    for(x;x<=max_x; x+=x&(-x))
    {
        for(y;y<=max_y; y+=y&(-y))
        {
            bit[x][y] += val;
        }
    }
}

int sum(int x, int y)
{
    x++,y++;
    
    int s = 0;
    for(x; x>0; x-=x&(-x))
    {
        for(y; y>0; y-=y&(-y))
        {
            s += bit[x][y];
        }
    }
    return s;
}

void solve(int test)
{
    int n;
    cin>>n;
    max_x = max_y = n;
    bit.resize(max_x+1,vector<int>(max_y+1,0));

    int q;
    cin>>q;

    while(q--)
    {
        int t,x,y;
        cin>>t>>x>>y;
        x--,y--;
        if(t==1)
        {
            int val;cin>>val;
            update(x,y,val);
        }
        else
        {
            int ans = sum(x,y);
            cout<<ans<<endl;
        }
    }


}

int main()
{
  fast;

  int t = 1;
  //cin>>t;

  for(int x = 1;x<=t;x++)
  {
      solve(x);
  }
  return 0;
}

/*
5
8
1 3 5 1
2 3 5
2 2 5
1 1 1 10
2 1 1
2 5 5
2 4 4
2 3 4
*/
```
