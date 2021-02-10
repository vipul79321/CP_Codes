#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back

int n;
vector<vector<int> >bit;

void update(int x, int y, int val)
{
    x++,y++;
    int x1=x ,y1 = y;

    for(x=x1; x<=n; x+=x&(-x))
    {
        for(y=y1; y<=n; y+=y&(-y))
        {
            bit[x][y] += val;
        }
    }
}

int sum(int x, int y)
{
    x++,y++;
    int x1=x ,y1 = y;
    int s = 0;
    for(x=x1; x>0; x-=x&(-x))
    {
        for(y=y1; y>0; y-=y&(-y))
        {
            s += bit[x][y];
        }
    }
    return s;
}

void solve(int test)
{
    cin>>n;
    bit.resize(n+1,vector<int>(n+1,0));

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
