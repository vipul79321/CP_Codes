/*
* Problem - Calculate & Print LIS in NlogN using Fenwick Tree.
* Algorithm Description - 
* 1. Create a Fenwick tree of pair<int,int> which will store maximum value and its index.
* 2. Normalize the given array i.e, convert each element to [0..n]
* 3. Loop for i to 0..n
*     * get_max element in Fenwick tree in range [0, num_to_index]
*     * Update max_lis, lis_end, prev[i].
*     * Update Fenwick tree at id = num_to_index[v[i]], val = (lis_value,i)
* 4. Print LIS using prev and lis_end
*/


#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

vector<pair<int,int> >fenwick;
map<int,int>num_to_index;

void normalize(vector<int>&v)
{
    vector<int>temp = v;
    sort(temp.begin(),temp.end());
    for(int i=temp.size()-1;i>=0;i--)
    {
        num_to_index[temp[i]] = i;
    }
}


void update(int id, pair<int,int>val,int n)
{
    id++;
    while(id<=n)
    {
        if(fenwick[id].first <= val.first)
        {
            fenwick[id].first = val.first;
            fenwick[id].second = val.second;
        }
        id += id&(-id);
    }
}

pair<int,int>get_max(int id)
{
    id++;
    pair<int,int>mx = mp(0,-1);
    while(id>0)
    {
        if(mx.first <= fenwick[id].first)
        {
            mx.first = fenwick[id].first;
            mx.second = fenwick[id].second;
        }
        id -= id&(-id);
    }
    return mx;
}


void calc_and_print_lis(vector<int>&v)
{
    int n = v.size();
    if(n<=0)return;

    int i,j;
    fenwick.resize(n+5,mp(0,-1));
    vector<int>prev(n+1,-1);
    vector<int>lis;
    normalize(v);

    int lis_end = -1;
    int max_lis = 0;

    for(i=0;i<n;i++)
    {
        pair<int,int>last_max = get_max(num_to_index[v[i]]);
        prev[i] = last_max.second;

        if(max_lis < last_max.first + 1)
        {
            max_lis = last_max.first + 1;
            lis_end = i;
        }

        update(num_to_index[v[i]],mp(last_max.first+1,i),n);   // Important - Update using last_max.first + 1, i
    }

    while(lis_end >= 0)
    {
        lis.pb(v[lis_end]);
        lis_end = prev[lis_end];
    }

    reverse(lis.begin(),lis.end());

    cout<<lis.size()<<endl;
    for(auto val:lis)cout<<val<<" ";
    cout<<endl;

}

void solve()
{
   int n;
   cin>>n;
   vector<int>v(n);
   int i,j;
   for(i=0;i<n;i++)cin>>v[i];

   calc_and_print_lis(v);

}

int main()
{
  solve();
  return 0;
}
/*
16
0 8 4 12 2 10 6 14 1 9 5 13 3 11 7 15
Return
6
0 2 6 9 11 15
*/
