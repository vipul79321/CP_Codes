/*
* CF problem where it was needed - https://codeforces.com/contest/1557/problem/D
* My submission - https://codeforces.com/contest/1557/submission/125451375
* Expected idea using Lazy Segment Tree - https://codeforces.com/contest/1557/submission/125412981
* Problem crux - Given an empty set of intervals initially, we need perform following request - 
* Insert range l,r in the set at the same time keeping each interval in set disjoint.
* Also preserving the latest insertion i.e. all the intervals intersecting with the latest request interval needs to be adjusted.
*/

#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;

set<pair<ll,ll> >s;
bool intersect(pair<ll,ll>&a, pair<ll,ll>&b)
{
    if(a.first <= b.second && a.second >= b.first)return 1;
    if(b.first <= a.second && b.second >= a.first)return 1;
    return 0;
}

void disjoint_set(pair<ll,ll>p)
{

    auto it = s.lower_bound(p);
    
    if(it!=s.begin())it--;

    // Removing / adjusting all the intervals intersecting with p
    while(it!=s.end())
    {
        if(it->first > p.second)break;

        pair<ll,ll>q = *it;
    
        if(intersect(q,p))
        {
            it = s.erase(it);
    
            if(q.first < p.first)
                s.insert(mp(q.first,min(p.first-1,q.second)));

            if(q.second > p.second)
                s.insert(mp(max(q.first,p.second+1),q.second));
        }
        else
            it++;
    }
    // Inserting latest interval
    s.insert(p);
}

void solve(int test)
{
   ll queries;
   while(queries--)
   {
       ll l,r;
       cin>>l>>r;
       disjoint_set(mp(l,r))
   }
}

int main()
{
  solve(x);
  return 0;
}
