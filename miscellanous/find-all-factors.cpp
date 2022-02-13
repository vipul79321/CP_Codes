// Use case - Given a number N and Q queries with integer x <= N, we need to output all the divisors of x

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define mp make_pair
#define ll long long
#define pb push_back
#define hell 998244353
#define pii pair<int,int>

vector<int> find_all_div(int num, vector<int>&sieve)
{
    map<int,int>cnt; // to store count of each prime factor

    while (num > 1) {
      cnt[sieve[num]]++;
      num /= sieve[num];
    }
    vector<int>divs;
    divs.pb(1);

    for (pair<int,int> p : cnt)
    {
      int sz = divs.size();
      for (int q = 0; q < sz * p.second; ++q)divs.push_back(divs[q] * p.first);
    }
    sort(divs.begin(), divs.end());

    return divs;
}


void solve(int test) {

    int n;
    cin >> n;
    vector<int> sieve(n + 2);
    for (int i = 2; i <= n; i++)
    {
        if(!sieve[i])
        {
            for(int j=i;j<=n;j+=i)sieve[j] = i;
        }
    }

    int q;
    cin>>q;

    while(q--)
    {
        int num;
        cin>>num;

        vector<int>divisors = find_all_div(num, sieve);

        for(auto v:divisors)cout<<v<<" ";

        cout<<endl;

    }

}

int main()
{

  int t = 1;
  //cin>>t;

  for(int x = 1;x<=t;x++)
  {
      solve(x);
  }
  return 0;
}
