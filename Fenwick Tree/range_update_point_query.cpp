#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back

int n;
vector<int>bit;


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
    while(id>0)
    {
        s+= bit[id];
        id -= id&(-id);
    }
    return s;
}


void range_update(int l, int r, int val)
{
    update(l,val);
    update(r+1,-val);
}

int point_query(int l)
{
    return sum(l);
}

void solve(int test)
{
    cin>>n;
    int i,j;

    bit.resize(n+1,0);


    int q;
    cin>>q;

    for(i=0;i<q;i++)
    {
        int t;
        cin>>t;

        if(t==1)
        {
            int l,r,val;
            cin>>l>>r>>val;
            l--,r--; // if one based indexing l, r;
            range_update(l,r,val);
        }
        else
        {
            int l;
            cin>>l;
            l--;
            int ans = point_query(l);
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
2 4
1 4 8 3
1 7 9 2
2 6
2 8
2 5
*/
