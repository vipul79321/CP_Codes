/*
* Range add and Range max queries using Lazy segment tree
* st will keep ans for range max queries
* lazy will keep info about propogation.
*/

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define hell 998244353
#define INF 1e6
int n;
vector<int>v,lazy_st,st;

void build_st(int id, int l, int r)
{
   if(l==r)
   {
       lazy_st[id] = 0;
       st[id] = v[l];
       return;
   }
   int mid = (l+r)/2;

   build_st(2*id+1,l,mid);
   build_st(2*id+2,mid+1,r);

   lazy_st[id] = 0;
   st[id] = max(st[2*id+1], st[2*id+2]);
}

void push(int id)
{
    lazy_st[2*id+1] += lazy_st[id];
    lazy_st[2*id+2] += lazy_st[id];
    st[2*id+1] += lazy_st[id];
    st[2*id+2] += lazy_st[id];
    lazy_st[id] = 0;
}

void update(int low, int high, int l, int r,int id, int addend)
{
    if(l>high || r<low)return;
    if(l>=low && r<=high)
    {
        lazy_st[id] += addend;
        st[id] += addend;
        return;
    }

    push(id);
    int mid = l+r;
    mid = mid/2;

    update(low,high,l,mid,2*id+1,addend);
    update(low,high,mid+1,r,2*id+2,addend);

    st[id] = max(st[2*id+1], st[2*id+2]);
}

int get(int low, int high, int id, int l, int r)
{
    if(low > r || high < l)return INT_MIN;
    if(low <= l && high >= r)
        return st[id];

    push(id);
    int mid = (l+r)/2;

    return max(get(low,high,2*id+1,l,mid), get(low,high,2*id+2,mid+1,r));
}

void solve(int test)
{
   cin>>n;

   int i,j;

   v.resize(n);

   for(i=0;i<n;i++)cin>>v[i];

   lazy_st.clear();
   st.clear();
   lazy_st.resize(4*n);
   st.resize(4*n,0);
   build_st(0,0,n-1);

   int q;
   cin>>q;

   while(q--)
   {
       int t;
       cin>>t;
       if(t==1)
       {
           int l,r,x;
           cin>>l>>r>>x;
           l--,r--;
           update(l,r,0,n-1,0,x);
       }
       else
       {
           int l,r;
           cin>>l>>r;
           l--,r--;
           int ans = get(l,r,0,0,n-1);
           cout<<ans<<endl;
       }
   }

   return;
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
5
1 2 3 4 5
6
1 2 3 1
2 1 4
2 2 5
2 3 3
2 2 4
2 1 5
*/
