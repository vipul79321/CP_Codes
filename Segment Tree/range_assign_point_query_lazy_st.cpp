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
vector<int>v,lazy_st,marked;

void build_lazy_st(int id, int l, int r)
{
   if(l==r)
   {
       lazy_st[id] = v[l];
       marked[id] = 0;
       return;
   }
   int mid = (l+r)/2;
   build_lazy_st(2*id+1,l,mid);
   build_lazy_st(2*id+2,mid+1,r);
   lazy_st[id] = 0;
   marked[id] = 0;
}

void push(int id)
{
    if(marked[id])
    {
        lazy_st[2*id+1] = lazy_st[id];
        lazy_st[2*id+2] = lazy_st[id];
        marked[2*id+1] = 1, marked[2*id+2]=1;
        marked[id] = 0;
    }
    return;
}

void update_lazy_st(int low, int high, int l, int r,int id, int new_val)
{
    if(l>high || r<low)return;
    if(l>=low && r<=high)
    {
        lazy_st[id] = new_val;
        marked[id] = 1;
        return;
    }
    push(id);
    int mid = l+r;
    mid = mid/2;
    update_lazy_st(low,high,l,mid,2*id+1,new_val);
    update_lazy_st(low,high,mid+1,r,2*id+2,new_val);
}

int get_lazy_st(int id, int l, int r, int pos)
{
    if(l==r)return lazy_st[id];

    if(marked[id])return lazy_st[id];

    int mid = l+r;
    mid = mid/2;
    if(mid >= pos)return get_lazy_st(2*id+1,l,mid,pos);
    else
        return get_lazy_st(2*id+2,mid+1,r,pos);
}

void solve(int test)
{
   cin>>n;

   int i,j;

   v.resize(n);

   for(i=0;i<n;i++)cin>>v[i];

   lazy_st.clear();
   marked.clear();
   lazy_st.resize(4*n);
   marked.resize(4*n,0);
   build_lazy_st(0,0,n-1);

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
           update_lazy_st(l,r,0,n-1,0,x);
       }
       else
       {
           int pos;
           cin>>pos;
           pos--;
           int ans = get_lazy_st(0,0,n-1,pos);
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
1 2 3 5
2 1
2 2
2 3
2 4
2 5
*/
