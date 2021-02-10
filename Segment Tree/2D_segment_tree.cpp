#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define hell 998244353
#define INF 1e6

int n,m;
vector<vector<int> >st,a;

void build_y(int id_x, int lx, int rx, int id_y, int ly, int ry)
{
    if(ly==ry)
    {
        if(lx==rx)st[id_x][id_y] = a[lx][ly];
        else
            st[id_x][id_y] = st[2*id_x+1][id_y] + st[2*id_x+2][id_y];
    }
    else
    {
        int mid_y = (ly+ry)/2;
        build_y(id_x, lx, rx, 2*id_y+1, ly, mid_y);
        build_y(id_x, lx, rx, 2*id_y+2, mid_y+1, ry);
        st[id_x][id_y] = st[id_x][2*id_y+1] + st[id_x][2*id_y+2];
    }
}

void build_x(int id_x, int lx, int rx)
{
    if(lx!=rx)
    {
        int mid_x = (lx+rx)/2;
        build_x(2*id_x+1, lx, mid_x);
        build_x(2*id_x+2, mid_x+1, rx);
    }

    build_y(id_x, lx, rx, 0, 0, m-1);
}

void update_y(int id_x, int lx, int rx, int id_y, int ly, int ry, int x, int y, int new_val)
{
    if(ly==ry)
    {
        if(lx==rx){st[id_x][id_y] = new_val;a[x][y] = new_val;}
        else
        {
            st[id_x][id_y] = st[2*id_x+1][id_y] + st[2*id_x+2][id_y];
        }
    }
    else
    {
        int mid_y = (ly+ry)/2;
        if(mid_y >= y)update_y(id_x, lx, rx, 2*id_y+1, ly, mid_y, x, y, new_val);
        else
            update_y(id_x, lx, rx, 2*id_y+2, mid_y+1, ry, x, y, new_val);

        st[id_x][id_y] = st[id_x][2*id_y+1] + st[id_x][2*id_y+2];
    }
}

void update_x(int id_x, int lx, int rx, int x, int y, int new_val)
{
    if(lx!=rx)
    {
        int mid_x = (lx+rx)/2;
        if(mid_x>=x)update_x(2*id_x+1, lx, mid_x, x, y, new_val);
        else
            update_x(2*id_x+2, mid_x+1, rx, x, y, new_val);
    }

    update_y(id_x, lx, rx, 0, 0, m-1, x, y, new_val);
}

int sum_y(int id_x, int id_y, int ly, int ry, int qly, int qry)
{
    if(ly>qry || ry < qly)return 0;
    if(qly <= ly && qry >= ry)return st[id_x][id_y];

    int mid_y = (ly+ry)/2;

    return sum_y(id_x, 2*id_y+1, ly, mid_y, qly, qry) +
           sum_y(id_x, 2*id_y+2, mid_y+1, ry, qly, qry);
}

int sum_x(int id_x, int lx, int rx, int qlx, int qrx, int qly, int qry)
{
    if(lx>qrx || rx<qlx)return 0;
    if(qlx<=lx && qrx>= rx)
        return sum_y(id_x, 0, 0, m-1, qly, qry);

    int mid_x = (lx+rx)/2;

    return sum_x(2*id_x+1, lx, mid_x, qlx, qrx, qly, qry) +
           sum_x(2*id_x+2, mid_x+1, rx, qlx, qrx, qly, qry);

}


void solve(int test)
{
   cin>>n>>m;
   int i,j;

   st.clear();
   a.clear();
   a.resize(n,vector<int>(m));
   st.resize(4*n,vector<int>(4*m));

   for(i=0;i<n;i++)for(j=0;j<m;j++)cin>>a[i][j];

   build_x(0,0,n-1);


   int q;
   cin>>q;
   while(q--)
   {
      int t;
      cin>>t;
      if(t==1)
      {
          int qlx,qrx,qly,qry;
          cin>>qlx>>qly>>qrx>>qry;
          qlx--,qrx--,qly--,qry--;

          int ans = sum_x(0,0,n-1,qlx,qrx,qly,qry);

          cout<<ans<<endl;
      }
      else
      {
          int x,y,c;
          cin>>x>>y>>c;
          x--,y--;
          update_x(0,0,n-1,x,y,c);
      }

   }


}

int main()
{

    fast;

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
3 3
1 2 3
4 5 6
7 8 9
5
1 1 1 3 3
2 2 2 11
1 1 1 3 3
1 3 2 3 3
1 2 2 3 3
*/
