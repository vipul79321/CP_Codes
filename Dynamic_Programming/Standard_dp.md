## Coin Change problem (Similar to finding number of positive solutions of given linear equation)
[Link](https://leetcode.com/problems/coin-change-2/) | [Linear Equation](https://www.geeksforgeeks.org/find-number-of-solutions-of-a-linear-equation-of-n-variables/)

```c++
n = coin.size();
dp[n+1][target+1] = {0};
for(i=0;i<=n;i++)dp[i][0] = 1;

// dp[i][amt] - number of ways to make amount = amt using coins till ith index
for(int i=1;i<=coin.size();i++) {
    for(int amt=1;amt<=target;amt++) {
	dp[i][amt] = dp[i-1][amt];
	
	if(coin[i-1] <= amt)
	  dp[i][amt] += dp[i][amt-coin[i-1]];
    }
}
 ```
 
 ```c++
 // Memory efficient implementation
 n = target;
 m = coins.size();
 
 dp[n+1] = 0; 
 dp[0] = 1;
 
 // dp[i] = for each phase dp[i] represents number of ways to make amount i using coins till that phase
 for(j=1;j<=m;j++)
 {
   for(i=coins[j-1];j<=n;j++)
   {
      dp[i] += dp[i-coins[j-1]];
   }
 }
  ```
---

## Subset Sum problem
[Link](https://www.geeksforgeeks.org/subset-sum-problem-dp-25/)

* Calculations
```c++
dp[n+1][sum+1] = {0};

for(i=0;i<=n;i++)dp[i][0] = 1;

for(i=1;i<=n;i++)
{
   for(j=1;j<=sum;j++)
   {
      dp[i][j] = dp[i-1][j];
      if(j>=arr[i-1])dp[i][j] = dp[i][j] | dp[i-1][j-arr[i-1]];
   }
}

// Since we only need last row for dp transition we can reduce space complexity by making dp[2][sum+1] array and using curr and prev variables.
```
* Printing
```c++
for(i=n;i>0 && sum>0;i--)
{
    if(dp[i-1][sum])continue;
    else
    {
        cout<<arr[i-1]<<" ";
        sum = sum - arr[i-1];
    }
}
```
---

## Domino Tiling - Fill 3xN profile with 2x1 tile
[Link](https://www.geeksforgeeks.org/tiling-with-dominoes/)
* A[n] - Number of ways to completely fill 3xN profile
* B[n] - Number of ways to fill such that first element of top column is empty
* C[n] - Number of ways to fill such that last element of top column is empty

Transitions - 
* B[n] = C[n]
* A[n] = A[n-2] + B[n-1] + C[n-1] or A[n-2] + 2 * B[n-1];
* B[n] = A[n-1] + B[n-2];
* A[0] = 1, A[1] = 0
* B[0] = 0, B[1] = 1

---

## Maximum Games Played by winner - Good one. Have to think inversely.
[Link](https://www.geeksforgeeks.org/maximum-games-played-winner/)

* Given N players, output maximum number of games played by winner, with condition that two players are allowed to compete against one another if and only if difference between number of games played by them is <=1.

Hint - Think of **minimum number** of players required so that winner plays i games. `dp[i] = dp[i-1] + dp[i-2]`.
```c++

dp[0] = 1;
dp[1] = 2;
i = 2;
while(1) {
   dp[i] = dp[i-1] + dp[i-2];
   if(dp[i] > n)return i-1;
}
```
---
## Maxium sum increasing subsequence from a prefix and a given element after prefix is must
[link](https://www.geeksforgeeks.org/maximum-sum-increasing-subsequence-from-a-prefix-and-a-given-element-after-prefix-is-must/)

---

## Maximum sum contiguous subarray - Kadane's algo 

```c++
   int start = 0,s,e;
   int max_so_far = INT_MIN;
   int curr = 0;
   
   for(i=0;i<n;i++)
   {
       curr += a[i];
       if(curr >= max_so_far)
       {
           s = start;
           e = i;
           max_so_far = curr;
       }
       if(curr < 0)
       {
           start = i+1;
           curr = 0;
       }
   }
   
   return e-s+1;
   ```
---

## Maximum sum such that no two elements are adjacent using O(1) space
[Link](https://www.geeksforgeeks.org/maximum-sum-such-that-no-two-elements-are-adjacent/)

```c++
int incl = v[0],excl = 0;
for(int i=1;i<n;i++)
{
    new_excl = max(incl,excl);
    incl = excl + v[i];
    excl = new_excl;
}
return max(incl,excl);
```
---

## Count of arrays having each element from [1,k] & no two adjacent elements same & first element is 1 and last element is x
[Link](https://www.geeksforgeeks.org/count-arrays-consecutive-element-different-values/)

* Let dp[i] - number of such arrays such that last element is not equal to 1
* Two cases to consider - 
    * ```if x != 1 : ans = dp[i]/(k-1)```
    * ```if x == 1 : ans = dp[i-1]```
* Transitions - ```dp[i] = (k-1)*dp[i-2] + (k-2)*dp[i-1]```

---

## Calculate number of Dearangements
[Link](https://www.geeksforgeeks.org/count-derangements-permutation-such-that-no-element-appears-in-its-original-position/)

```c++
Derangements[n] = (n-1)*(Derangements[n-1] + Derangements[n-2])
```
Explaination - 
1. For last element there are n-1 places, hence the multiplication.
2. Now, lets say if last element is placed at i<sup>th</sup> index then following cases arise-
    * i<sup>th</sup> is placed at last index, hence it is equivalent to solving for n-2.
    * i<sup>th</sup> is not placed at last index, hence it is equivalent to solving for n-1.

---

## 0-1 Knapsack
* Calculation
```c++
for(int i=0;i<=n;i++)
{
    for(int weight=0;weight<=cap;weight++)
    {
        if(i==0 || weight == 0)
        {
            dp[i][weight] = 0;
            continue;
        }
 
        if(weight > wt[i-1])
            dp[i][weight] = max(dp[i][weight],val[i-1] + dp[i-1][weight-wt[i-1]]);

        dp[i][weight] = max(dp[i][weight], dp[i-1][weight]);
    }
}
```

* Printing
```c++
int res = dp[n][cap];

for(i=n,w=cap;i>0 && res>0;i--)
{
    if(dp[i-1][w] == res)
    continue;
    else
    {
        cout<<i<<" ";  // include in ans
        res = res - val[i-1];
        w = w - wt[i-1];
    }
}
```

---

## Dice Throw Problem
[Link](https://www.geeksforgeeks.org/dice-throw-dp-30/)
* Given n dice with m faces, find number of ways to achieve score x
```c++
dp[n+1][x+1] = {0};
dp[0][0] = 1;
for(i=1;i<=n;i++)
{
    for(j=1;j<=x;j++)
    {
        for(k=1;k<=m && k<=j;k++) // can be avoided using prefix-sum array
        {
            dp[i][j] += dp[i-1][j-k]; 
        }
    }
}
```

---

## Word Break Problem
[Link](https://www.geeksforgeeks.org/word-break-problem-dp-32/)
```c++
dp[n+1]=0;
dp[0] = 1;

for(int i=1;i<=n;i++)
{
    for(j=i;j>0;j--)
    {
        if(dictionaryContains(s.substr(j,i-j+1)))
        dp[i] = dp[i]|dp[j];
    }
}
```
---

## Minimum Vertex Cover Problem in Binary Tree
[Link](https://www.geeksforgeeks.org/vertex-cover-problem-set-2-dynamic-programming-solution-tree/)
* A vertex cover of an undirected graph is a subset of its vertices such that for every edge (u, v) of the graph, either ‘u’ or ‘v’ is in vertex cover. Although the name is Vertex Cover, the set covers all edges of the given graph. 
```c++
int vertexCover(TreeNode* root)
{
    if(root == null)return 0;
    if(root->left == null && root->right == null)return 1;
    
    int size_incl = 1 + vertexCover(root->left) + vertexCover(root->left);  // including root in answer
    
    int size_excl = 0;  // excluding root in ans
    if(root->left!=null)
    size_excl += 1 + vertexCover(root->left->left) + vertexCover(root->left->right);
    
    if(root->right!=null)
    size_excl += 1 + vertexCover(root->right->left) + vertexCover(root->right->right);
    
    return min(size_excl,size_incl); 
}
```
---
## Largest Independent Set in Binary Tree
[Link](https://www.geeksforgeeks.org/largest-independent-set-problem/)
* Largest Independent set of nodes in binary tree is a set of maximum size such that there is no edge between any two nodes in the set.
```c++
int largestIndependentSet(TreeNode* root)
{
    if(root == null)return 0;
    if(root->left == null && root->right == null)return 1;
    
    int size_excl = largestIndependentSet(root->left) + largestIndependentSet(root->right);
    
    int size_incl = 1;
    if(root->left!=null)
    size_incl += largestIndependentSet(root->left->left) + largestIndependentSet(root->left->right);
    
    if(root->right!=null)
    size_incl += largestIndependentSet(root->right->left) + largestIndependentSet(root->right->right);
    
    return max(size_excl,size_incl);
}
```
---

## Longest Alternating Subsequence
[Link](https://www.geeksforgeeks.org/longest-alternating-subsequence/)

```c++
inc[n] = {0},dec[n] = {0};
inc[0] = 1,dec[0] = 1;
int ans = 1;
for(i=1;i<n;i++)
{
    for(j=i-1;j>=0;j--)
    {
        if(arr[i] > arr[j])
        inc[i] = max(inc[i],dec[j]);
        if(arr[i] < arr[j])
        dec[i] = max(dec[i],inc[j]);
    }
    inc[i]++;
    dec[i]++;
    ans = max(ans, max(inc[i],dec[i]));
}
return ans;
```

---

## Minimum Number of Jumps to reach the end of an array
[Link](https://www.interviewbit.com/problems/min-jumps-array/) | [Link](https://leetcode.com/problems/jump-game-ii/discuss/18014/Concise-O(n)-one-loop-JAVA-solution-based-on-Greedy)


```c++
int jumps = 0, curEnd = 0, curFarthest = 0;
for (int i = 0; i < A.size() - 1; i++) {
   curFarthest = max(curFarthest, i + A[i]);
   if (i == curEnd) {
      jumps++;
      if(curEnd >= curFarthest)
         return -1;

      curEnd = curFarthest;
   }
}
return jumps;
```

---

## Choose Maximum weight with given weight/value ratio
[Link](https://www.geeksforgeeks.org/choose-maximum-weight-given-weight-value-ratio/)

Given two arrays of size n - Wt[n] , val[n] and a number k. We need to select subset with whose sum of weight / sum of val  == k and sum of weight is maximum among all the possibilities.

Solution - 
* Let dp[i][j] denote the maximum weight that can be obtained from first i elements such that sum of their weight - k * (sum of their value) is j. 
* Ans will be dp[n][0]
* Transition will be dp[i][j] = max(dp[i-1][j], dp[i-1][j + wt[i] - k * val[i]] + wt[i] )

---


## Minimum Initial Points to reach the destination
[Link](https://www.geeksforgeeks.org/minimum-positive-points-to-reach-destination/)

```c++
dp[n-1][m-1] = mat[n-1][m-1] > 0 ? 1 : abs(mat[n-1][m-1]) + 1;

for(int i=n-1;i>=0;i--)
{
    for(int j=m-1;j>=0;j--)
    {
        if(i==n-1 || j==m-1)continue;

        int min_points_on_exit = INT_MAX;
        if(j<m-1)
        min_points_on_exit = min(min_points_on_exit, dp[i][j+1]);
        if(i<n-1)
        min_points_on_exit = min(min_points_on_exit, dp[i+1][j]);
        
        dp[i][j] = max(min_points_on_exit - mat[i][j], 1);
    }
}

return dp[0][0];
```
---

## Number of Permutations with K inversions
[Link](https://www.geeksforgeeks.org/number-of-permutation-with-k-inversions/)

* dp[n][k] = sum(dp[n-1][j] where j = k...0)

---

## Sum of Average of all subsets
[Link](https://www.geeksforgeeks.org/sum-average-subsets/)

* Ans = summation of (sum of all subset of size sz) / sz; for sz = 1 to sz = N;
* sum of all subset of size sz = (Sum of all elements) * Binomial(N-1,sz-1)

---

## Sum of XOR of all subarrays
[Link](https://www.geeksforgeeks.org/sum-of-xor-of-all-subarrays/)

Algorithm - 
* At each index we want to keep the count of how many subarrays starting from index = j has odd numbers of ith bit set.
* Let c_odd be count of such subarrays, then we can simply add ans = ans + c_odd*(1<<i)

```c++
int findXorSum(vector<int>&arr, int n)
{
	// variable to store the final sum
	int sum = 0;

	for (int i = 0; i < 30; i++) {

		// variable to store number of sub-arrays with odd number of elements with ith bits starting from the first
		// element to the end of the array
		int c_odd = 0;

		// variable to check the status of the odd-even count while calculating c_odd
		bool odd = 0;

		// loop to calculate initial value of c_odd
		for (int j = 0; j < n; j++) {
			if ((arr[j] & (1 << i)) > 0)
				odd = (!odd);
			if (odd)
				c_odd++;
		}

		// loop to iterate through all the elements of the array and update sum
		int mul = 1<<i;
		for (int j = 0; j < n; j++) {
			sum += (mul * c_odd);

			if ((arr[j] & (1 << i)) > 0) // Update c_odd, if ith bit was set then number of even count subarray will become number of odd count subarrays
				c_odd = (n - j - c_odd);
		}
	}

	// returning the sum
	return sum;
}
```

---

## Number of ways to form max-heap from N distinct integers
[Link](https://www.geeksforgeeks.org/number-ways-form-heap-n-distinct-integers/)

* Since in a max-heap structure and root node will be fixed.
* Let number of nodes in left subtree be L and number of nodes in right subtree be R, L+R == N-1
* dp[N] = binomial(N-1,L) * dp[L] * dp[R]

---

## Another variation of subset sum problem
[Link](https://www.geeksforgeeks.org/number-ordered-pairs-ai-aj-0/)

* Given an array with element in range [0,(1<<15)-1]. We need to find number of pairs (i,j) such that A[i]&A[j] == 0
* For each i given problem can be repharsed as sum of frequency of all the elements which are subset of (mask = (A[i]^(1<<15-1)))
* So, now for each mask we need to find number of elements which are subset of mask.

DP - formulation
* Let dp[mask][i] represents number of elements which are subset of mask and doesnt differ from mask till (i+1)th bit. May or may not differ at & after ith bit.
* Base condition -
    * dp[mask][0] = frequency[mask] if 0th bit is not set in mask
    * dp[mask][0] = frequency[mask] + frequency[mask^1] if 0th bit is set in mask
* DP transition - 
    * dp[mask][i] = dp[mask][i-1] if ith bit is not set in mask
    * dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1] if ith bit is set in mask

* So for each mask number of elements which are subset of it will be dp[mask][15]

---

## Matrix Chain Multiplication
[Link](https://www.geeksforgeeks.org/printing-brackets-matrix-chain-multiplication-problem/)

* **Obtaining optimal cost for given matrix chain**
```c++
/*
* p[] : p[i-1]*p[i] represents dimension of A[i-1] matrix. So total number of matrix will be p.size()-1; 
* cost[i][j] : Optimal bracketing cost for the matrix chain[i..j]
* bracket[i][j] : Bracketing position for optimal cost of matrix chain[i..j]
*/
int n = p.size();
int cost[n][n], bracket[n][n], i, j;
for(i=0;i<n;i++)
{
    for(j=0;j<n;j++)
    {
        cost[i][j] = INT_MAX; bracket[i][j] = -1;
    }
}

for(i=0;i<n;i++)cost[i][i] = 0;

for(int len=2;len<=n-1;len++)
{
    for(int i=1;i<=n-len;i++)
    {
        int j = i+len-1;
        
        for(int k=i;k<=j-1;k++)
        {
            if(cost[i][j] > cost[i][k] + cost[k+1][j] + p[i-1]*p[k]*p[j])
            {
                cost[i][j] = cost[i][k] + cost[k+1][j] + p[i-1]*p[k]*p[j];
                bracket[i][j] = k;
            }
        }
    }
}

cout<<"Optimal cost for given matrix chain: "<<dp[1][n-1]<<endl;
printingBracketSequence(1,n-1,0)
```

* **Printing Bracket Sequence**
```c++
printingBracketSequence(int i, int j)
{
    if(i==j)
    {
        cout<<matrixName[i-1]<<" ";
        return;
    }
    
    cout<<"(";
    
    printingBracketSequence(i,bracket[i][j]);
    
    printingBracketSequence(bracket[i][j]+1,j);
    
    cout<<")";
}
```

---

## Number of Palindromic Paths in given Matrix from (0,0) to (n-1,m-1)
[Link]()

* Approach is to used memoized dp map with entries as starting cell(rs,cs) and ending cell(re,ce)
* See code for transition details - 
```c++
bool solveDP(int rs, int cs, int re, int ce)
{
    if(rs<0 || rs>=n || cs<0 || cs >= m)return 0;
    if(re<0 || re>=n || ce<0 || ce >= m)return 0;
    
    if(rs>re || cs > ce)return 0;
    
    if(mat[rs][cs] != mat[re][ce])return 0;
    
    if(dp[mp(mp(rs,cs),mp(re,ce))] != dp.end())
    return dp[mp(mp(rs,cs),mp(re,ce))];
    
    if(abs(rs-re) + abs(cs-ce) == 1) // adjacent cell scenario
    {
        return 1;
    }
    
    int ans = 0;
    ans = ans + solveDP(rs+1,cs,re-1,ce);
    ans = ans + solveDP(rs+1,cs,re,ce-1);
    ans = ans + solveDP(rs,cs+1,re-1,ce);
    ans = ans + solveDP(rs,cs+1,re,ce-1);
    
    dp[mp(mp(rs,cs),mp(re,ce))] = ans;
    
    return ans;
    
}
```

---

## Check whether Row swaps or Column swaps produce a maximum area submatrix with all 1's
[Link](https://www.geeksforgeeks.org/check-whether-row-column-swap-produces-maximum-size-binary-sub-matrix-1s/)

**Problem Description** - 
* We are given a matrix with 0's or 1's. We are either allowed to swap rows or swap columns. What is the maximum area submatrix we can obtain with all 1's.

**Solution Description** - 
* Without loss of generality, if we can compute value for row swaps then we can compute value for column swap in similar manner or on transpose matrix.
* Computation for row swaps - 
    * Create a dp[n][n] matrix, where dp[i][j] will contain length of longest subarray in row[i] with all 1's ending at cell(i,j)
    * DP transition - dp[i][j] = mat[i][j] == 1 ? 1 + dp[i][j-1] : 0;
    * After filling the dp matrix, take each column of dp matrix, sort it and find maximum value `col[i]* (col.size()-i)`, this will give maximum area submatrix ending at that column.

---

## Minimum number of elements which are not part of Increasing or decreasing subsequence in array
[Link](https://www.geeksforgeeks.org/minimum-number-of-elements-which-are-not-part-of-increasing-or-decreasing-subsequence-in-array/)

**Problem Description** - 
* Given an array, we want to obtain one LIS and one LDS(both disjoint) from it such that this value is minimized - > (n - len(LIS) - len(LDS) );

**Solution Description**
* Create a dp[n][n][n] matrix, where dp[i][j][k] where i > j && i > k represents minimum number of elements which are not part of LIS and LDS where LIS ends at index j and LDS ends at index k.
* See code for more details - 
```c++
int id = n; // index to represent values of y,z that acts as both INT_MAX and INT_MIN to start LIS and LDS
int countMin(int x, int y, int z)
{
    if(x >= n)return 0;
    if(dp[x][y][z] != -1)return dp[x][y][z];
    
    int res = INT_MAX;
    if(z == id || arr[x] < arr[z])res = min(res, countMin(x+1,y,x)); // including xth element in LDS
    
    if(y == id || arr[x] > arr[y] )res = min(res, countMin(x+1,x,z)); // including xth element in LIS
    
    res = min(res, 1 + countMin(x+1,y,z)); // Not including xth element
    dp[x][y][z] = res;
}
```

---

## Word Wrap Problem
[Link](https://www.geeksforgeeks.org/word-wrap-problem-dp-19/)

**Problem description** - 
* Given a sequence of words, and a limit on the number of characters that can be put in one line. Assume length of each word is less than given limit.
* Put line breaks in given sequence such that sum of (extra space)^3 for each line is minimized.
* Extra spaces in line having limit L and number of words X is given by - `L - sum(len of each word) - X-1` if it is not the last line else 0 otherwise

**Solution**
* We will first calculate Extra[i][j], which is number of extra spaces if we put words[i..j] in one line. 
* Then we will calculate Cost[i][j], which is (Extra[i][j])^3 if Extra[i][j] >= 0 else INF otherwise.
* Finally we will calculate, dp[i], which contains the optimal cost of arranging words from [0..i];

**Finding Optimal Cost**
```c++
int extra[n+1][n+1], cost[n+1][n+1], dp[n+1], prev[n+1];

for(int i=1;i<=n;i++)
{
    extra[i][i] = limit - len(word[i-1]);
    cost[i][j] = (extra[i][i])^3;

    for(int j=i+1;j<=n;j++)
    {
        extra[i][j] = extra[i][j-1] - len(word[j-1]) - 1;
        
        if(j==n && extra[i][j] >= 0)
        {
            cost[i][j] = 0;
        }
        else if(extra[i][j] < 0)
        {
            cost[i][j] = INF;
        }
        else
        {
            cost[i][j] = (extra[i][j])^3;
        }
    }
}

dp[0] = 0;
for(int i=1;i<=n;i++)
{
    dp[i] = INF;
    for(int j=1;j<=i;j++)
    {
        if(dp[i] > dp[j-1] + cost[i][j]))
        {
            prev[i] = j;
            dp[i] = dp[j-1] + cost[i][j];
        }
    }
}
```

**Printing Solution**
```c++
int printSolution(int ind)
{
    int k;
    if (prev[ind] == 1)
        k = 1;
    else
        k = printSolution (prev[ind]-1) + 1;
    cout<<"Line number "<<k<<": From word no. "<<prev[ind]<<" to "<<ind<<endl;
    return k;
}

```

---

## Count number of Airthmetic Progression Subsequences in given array - O(n * range_elements)
[Link](https://www.geeksforgeeks.org/count-arithmetic-progression-subsequences-array/)

**Problem Description** - Given an array of n **positive** integers and **1<=arr[i]<=100000**. Find number of AP subsequences in it. 

**Solution Approach** - 
* Iterate over all possible common difference in range `[minArr - maxArr, maxArr - minArr]`.
* For each common difference calculate number of APs with length >= 2
* Intialize ans as n. As all the single elements also form an AP.
* See code for more details

```c++
const int maxVal = 100005;
int dp[n]; // Stores the count of AP having common difference d and having arr[i] as last element.
int sum[maxVal];  // Stores the count of AP having common difference d and having i as last element.
int ans = n;
int maxArr = *max_element(arr.begin(),arr.end());
int minArr = *min_element(arr.begin(),arr.end());

for(int d = (minArr - maxArr); d<= (maxArr - minArr); d++)
{
    memset(sum,0,sizeof(sum));
    
    for(int i=0;i<n;i++)
        dp[i] = 1;
    
    for(int i=0;i<n;i++)
    {
        int prev = arr[i] - d;
        if(prev > 0 && prev < maxVal)
        {
            dp[i] = dp[i] + sum[prev];
        }
        sum[arr[i]] += dp[i];
        ans = ans + dp[i] - 1; // -1 to remove single element AP.
    }
}
```

---

## Length of Longest Airthmetic Progression from given set of numbers - O(n * n)
[Link](https://www.geeksforgeeks.org/longest-arithmetic-progression-dp-35/)

**Problem Description** - Given a set of numbers, find length of longest possible AP.

**Solution Approach** - 
* First, we will sort all the elements.
* Create a dp[n][n] matrix, where dp[i][j] stores length of longest AP having first two elements as arr[i] and arr[j] respectively.
* See code for more details. 

```c++
int dp[n][n];
memset(dp,0,sizeof(dp));

for(int i=0;i<n-1;i++)
{
    dp[i][n-1] = 2;
}

int ans = min(n,2); // as any two elements can form an AP;

for(int mid=n-2;mid>=0;mid--)
{
    int left = mid-1, right = mid+1;
    
    while(left >= 0 && right < n) // using two pointer approach to find two elements on both side of mid which satisfy property of AP.
    {
        if(set[left] + set[right] == 2*set[mid])
        {
            dp[left][mid] = dp[mid][right] + 1;
            ans = max(ans, dp[left][mid]);
        }
        else if(set[left] + set[right] > 2*set[mid])
        {
            dp[left][mid] = 2;
            ans = max(ans, dp[left][mid]);
            left--;
        }
        else
        {
            right++;
        }
    }
    
    while(left > 0)
    {
        dp[left][mid] = 2;
        ans = max(ans, dp[left][mid]);
        left--;
    }
}

return ans;
```

---

## Balanced expressions such that given positions have opening brackets
[Link](https://www.geeksforgeeks.org/balanced-expressions-such-that-given-positions-have-opening-brackets/)

**Problem Description** - Given an integer n and positions array where 1<=position[i] <= 2 * n. Find number of proper bracket expression such that given positions have opening bracket. 

**Solution Approach**
* Create a dp[2n][2n], where dp[i][j] is number of bracket expression of length i having difference between open bracket and close brackets == j; j>=0;
* Transition - 
    * dp[0][1] = 1;
    * if j == 0 && i not in positions then dp[i][j] = dp[i-1][j+1], putting a close bracket.
    * else if j == 0 && i in positions then dp[i][j] = 0, cant put a closing bracket.
    * else if i in position then dp[i][j] = dp[i-1][j-1];
    * else dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1];
* Finally ans will be dp[2n][0];

---

## Boolean Parenthesization Problem
[Link](https://www.geeksforgeeks.org/boolean-parenthesization-problem-dp-37/)

**Problem Description** - Given a boolean expression containing T, F, and operator &, |, ^. Find number of ways to parenthesize expression such that it evaluates to true. In other words given an symbol array containing T and F. And operator array containing &,|,^. Where operator[i] is operator between symbol[i] and symbol[i+1];

**Solution Approach** - 
* Create T[n][n] matrix where T[i][j] represents number of ways to parenthesize expression from [i..j] such that it evaluates to True.
* Create F[n][n] matrix where F[i][j] represents number of ways to parenthesize expression from [i..j] such that it evaluates to False.
* Create Total[n][n] matrix where Total[i][j] represents number of ways to parenthesize expression from [i..j].

**Transitions** - 
* T[i][j], for each k in range [i,j-1]
    *  if operator[k] == '&', then T[i][j] += T[i][k] * T[k+1][j];
    *  if operator[k] == '|, then T[i][j] += Total[i][k] * Total[k+1][j] - F[i][k] * F[k+1][j];
    *  if operator[k] == '^' then T[i][j] += T[i][k] * F[k+1][j] + F[i][k] * T[k+1][j];

* F[i][j], for each k in range [i,j-1]
    *  if operator[k] == '&', then F[i][j] += Total[i][k] * Total[k+1][j] - T[i][k] * T[k+1][j];
    *  if operator[k] == '|, then F[i][j] += F[i][k] * F[k+1][j];
    *  if operator[k] == '^' then T[i][j] += T[i][k] * T[k+1][j] + F[i][k] * F[k+1][j];

* Total[i][j], for each k in range[i,j-1]
    * Total[i][j] += (T[i][k] + F[i][k] ) * (T[k+1][j] * F[k+1][j]) 

---
