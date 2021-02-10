#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
int n;
vector<int>bit,v;

void update(int id, int val)
{
    id++;
    while(id<=n)
    {
        bit[id] += val;
        id += id&(-id);
    }
}

int sum(int id)
{
    id++;
    int s = 0;
    while(id<=n)
    {
        s+= bit[id];
        id -= id&(-id);
    }
    return s;
}

// Return the greatest index where prefixsum[id] == presum
// Time complexity = O(logn)

int find_presum_ind(int presum)
{
    int id = 0;
    int bitmask = 1;
    while(bitmask*2<=n)bitmask = bitmask<<1;

    while(bitmask!=0)
    {
        int tid = id + bitmask;
        bitmask = bitmask/2;

        if(tid>n)continue;

        //if(bit[tid] == presum)return tid;  // uncomment this line when we want to return any index satisfying our condition

        if(bit[tid] <= presum)
        {
           presum -= bit[tid];
           id = tid;
        }

    }
    if(presum!=0)return -1;
    return id;
}


void solve(int test)
{
    cin>>n;
    int i,j;

    bit.resize(n+1);

    for(i=0;i<n;i++)
    {
        int x;
        cin>>x;
        update(i,x);
    }

    int q;
    cin>>q;

    while(q--)
    {
        int presum;
        cin>>presum;

        int ans = find_presum_ind(presum);
        cout<<ans<<endl;
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
10
1 0 2 1 1 3 0 4 2 5
5
1
5
25
8
6
*/
