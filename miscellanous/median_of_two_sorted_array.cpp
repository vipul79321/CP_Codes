#include<bits/stdc++.h>
using namespace std;
// Algorithm Description - 
// 1) We need to make two partition of equal size, with help of both arrays
// 2) Total size of each partition should be (n+m+1)/2
// 3) Now to obtain partition do binary search on smaller array and obtain corresponding partition in larger array.
// 4) To check if partition is valid or not. Check left_1 <= right_2 && left_2 <= right_1
// 5) After finding optimal partition obtain required median based on size.
// 6) Time complexity = O(log(min(n,m)))
// Link to youtube tutorial - https://www.youtube.com/watch?v=LPFhl65R7ww

void solve(int test)
{
    int n,m;
    cin>>n>>m;
    int i,j;

    vector<int>nums1(n),nums2(m);

    for(i=0;i<n;i++)cin>>nums1[i];
    for(j=0;j<m;j++)cin>>nums2[j];

    if(n>m)
    {
        swap(nums1,nums2);
        swap(n,m);
    }

    int left_size = (n+m+1)/2;
    int low = 0, high = n;
    bool odd = (n+m)%2;

    while(low <= high)
    {
        int mid = (low+high)/2;

        int left_1 = mid-1 >= 0 ? nums1[mid-1] : INT_MIN;
        int right_1 = mid < n ? nums1[mid] : INT_MAX;

        int req = left_size - mid;
        if(req > m)
        {
            low = mid + 1;
            continue;
        }

        int left_2 = req - 1 >= 0 ? nums2[req-1] : INT_MIN;
        int right_2 = req < m ? nums2[req] : INT_MAX;

        if(left_1 <= right_2 && left_2 <= right_1)
        {
            if(!odd)
            {
                double val1 = max(left_1, left_2);
                double val2 = min(right_1, right_2);
                cout<<0.5*val1 + 0.5*val2<<endl;
                return;
            }
            else
            {
                cout<<max(left_1,left_2)<<endl;
                return;
            }
        }

        if(left_1 > right_2)
            high = mid - 1;
        else
            low = mid + 1;
    }

    cout<<0.0<<endl;
    return;

}

int main()
{
  int t = 1;
  cin>>t;

  for(int x=1;x<=t;x++)
  {
      solve(x);
  }

  return 0;
}
