#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back

int n;
vector<int>bit1,bit2;

void update(int id, int val, vector<int>&bit)
{
    id++;
    while(id<=n)
    {
        bit[id] += val;
        id += id&(-id);
    }
}

int sum(int id, vector<int>&bit)
{
    id++;
    int s = 0;
    while(id>0)
    {
        s+= bit[id];
        id -= id&(-id);
    }
    return s;
}

void range_update(int l, int r, int val)
{
    update(l,val,bit1);
    update(r+1,-val,bit1);

    update(l,val*(l-1),bit2);
    update(r+1,-val*r, bit2);
}

int range_sum(int l, int r)
{
    int lsum = sum(l-1,bit1)*(l-1) - sum(l-1,bit2);
    int rsum = sum(r,bit1)*r - sum(r,bit2);

    return rsum-lsum;
}


void solve(int test)
{
    cin>>n;
    int i,j;

    bit1.resize(n+1,0);
    bit2.resize(n+1,0);


    int q;
    cin>>q;

    for(i=0;i<q;i++)
    {
        int t,l,r;
        cin>>t>>l>>r;
        l--,r--;
        if(t==1)
        {
            int val;
            cin>>val;
            range_update(l,r,val);
        }
        else
        {
            int ans = range_sum(l,r);
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
10
7
1 3 5 1
2 1 10
1 4 8 3
1 7 9 2
2 6 10
2 8 8
2 5 5
*/
