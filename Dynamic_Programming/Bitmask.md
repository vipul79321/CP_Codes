## Bridge and Torch Problem - Bitmasking Solution
[Link](https://www.geeksforgeeks.org/program-bridge-torch-problem/)

* Given n people standing on left of a bridge. only two people can cross the bridge at a time. Time taken by them will be maximum of both person.
* Observations - 
    * Use mask to denote people on left side of bridge.
    * At any time only the person with minimum travelling time will return to left with **torch**.
* See code for implementation
```c++
int dp[1<<n][2];
// dp[i][j] represents minimum time to achieve following set of people on left side.
// If turn is odd then we need to move from right to left first else from left to right
// Therefore ans will be dp[1<<n-1][0];  -->intial state.
int arr_time[n] // -> time taken by ith person to cross the bridge.

int findMinTime(int leftmask, int turn)
{
    if(leftmask == 0)return 0;
    
    if(dp[leftmask][turn] != -1)return dp[leftmask][turn];
    
    int rightmask = ((1<<n) - 1) ^ leftmask;
    int res = INT_MAX;
    
    if(turn == 1) // go from right to left
    {
        int ind = -1, min_time = INT_MAX;
        for(int i=0;i<n;i++)  //select person with minimum return time.
        {
            if(rightmask&(1<<i))
            {
                if(min_time > arr[i])ind = i,min_time = arr[i];
            }
        }
        
        if(ind == -1)return INT_MAX;
        
        res = arr[ind] + findMinTime(leftmask|(1<<ind),0);
    }
    else
    {
        if(__builtin_popcount(leftmask) == 1) // only one person remaining.
        {
            for(int i=0;i<n;i++)
            {
                if(leftmask&(1<<i))
                {
                    res = arr[i];
                }
            }
        }
        else
        {
            for(int i=0;i<n;i++) // select any two person to send.
            {
                for(int j=0;j<n;j++)
                {
                    if(leftmask&(1<<i))
                    {
                        if(leftmask&(1<<j))
                        {
                            res = min(res, max(arr[i],arr[j]) + findMinTime(leftmask^(1<<i)^(1<<j),1));
                        }
                    }
                }
            }
        }
    }
    
    dp[leftmask][turn] = res;
    return dp[leftmask][turn];
}

```
---

## Count ways to assign unique caps to every person
[Link](https://www.geeksforgeeks.org/bitmasking-and-dynamic-programming-set-1-count-ways-to-assign-unique-cap-to-every-person/)

**Problem Description**
* Given n persons(n<=10) and 
* We have their hat collections as hat[i] containing list of all the hats person i has.
* We want to find the count of such assignments such that each person wears a hat from their collection and that there is no two person with same hat.

**Solution Approach**
* First for each cap obtain a list of person possessing that cap. capList[i] represent a list of people having ith cap.
* See code for transitions

```c++
int findPossibleWays(int mask, int cap)
{
    if(mask == allmask)return 1;  // return as a possible assigment found
    if(cap > maxcap)return 0;  // if no more caps left and still there are persons remaining
    
    if(dp[mask][cap] != -1)return dp[mask][cap];
    
    int res = 0;
    
    res = res + findPossibleWays(mask,cap+1); //ignoring current cap;
    
    for(auto person : capList[i])
    {
        if(mask&(1<<person))continue;
        
        res = res + findPossibleWays(mask | (1<<person), cap+1);
    }
    
    dp[mask][cap] = res;
    return res;
}
```
