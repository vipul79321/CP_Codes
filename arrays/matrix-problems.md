### Print Spiral Order of given matrix
[Link](https://www.interviewbit.com/problems/spiral-order-matrix-i/)

```c++
vector<int> spiralOrder(vector<vector<int> > &A) {
    vector<int>ans;
    int n = A.size(), m = A[0].size();
    
    
    int startx = 0, starty = 0;
    int endx = n-1,endy = m-1;
    while(startx<=endx && starty<=endy)
    {
        for(int j=starty;j<=endy;j++)
        {
            ans.push_back(A[startx][j]);
        }
    
        for(int i=startx+1;i<=endx;i++)
        {
            ans.push_back(A[i][endy]);
        }
    
        if(startx!=endx)
        {
            for(int j=endy-1;j>=starty;j--)
            {
                ans.push_back(A[endx][j]);
            }
        }
    
        if(starty!=endy)
        {
            for(int i=endx-1;i>startx;i--)
            {
                ans.push_back(A[i][starty]);
            }
        }
        
        startx++;starty++;
        endx--;endy--;
    }

    return ans; 
}
```

---

### Determinant of a matrix
[Link](https://www.geeksforgeeks.org/determinant-of-a-matrix/)

**Solution Approach using recursion** - 
* Recursion will be as follwos -  Take an element, remove corresponding row and column and obtain determinant of remaining matrix and multiply that value with proper sign with that element

**Solution Approach avoiding recursion** - 
* We can try to make the matrix upper triangular matrix using row transformation. [Transformation Properties](https://cran.r-project.org/web/packages/matlib/vignettes/det-ex1.html)

---

### Find perimeter of shapes formed with 1s in binary matrix
[Link](https://www.geeksforgeeks.org/find-perimeter-shapes-formed-1s-binary-matrix/)

**Solution Approach**-
* For each 1 in the matrix count number of adjacent 1 to it. And update ans as `ans += 4 - countNeighbors(i,j);`

---

### Minimum number of operations to make every row sum and every column sum equal in a square matrix
[Link](https://www.geeksforgeeks.org/minimum-operations-required-make-row-column-matrix-equals/)

**Problem Description** - 
* We need to make each row sum and col sum equal to certain value by using minimum number of operation
* Operation allowed - Increment any element of the matrix by 1.

**Solution Approach** -
* Obtain rowSum[i] and colSum[j] for each row i - [0, n-1] and for all columns j - [0, n-1]
* let maxSum = max(rowSum[i] for all i, colSum[j] for all j)
* now loop as follows - 
```c++
int count = 0;
for (int i = 0, j = 0; i < n && j < n;) {

    // Find minimum increment required in either row or column
    int diff = min(maxSum - sumRow[i],maxSum - sumCol[j]);

    // Add difference in corresponding cell, sumRow[] and sumCol[] array
    matrix[i][j] += diff;
    sumRow[i] += diff;
    sumCol[j] += diff;

    // Update the count variable
    count += diff;

    // If ith row satisfied, increment ith value for next iteration
    if (sumRow[i] == maxSum)
        ++i;

    // If jth column satisfied, increment jth value for next iteration
    if (sumCol[j] == maxSum)
        ++j;
}

for(int i=0;i<n;i++)
{
    if(sumRow[i] != maxSum)
    {
        cout<<"Not Possible\n";
        return INF;
    }
}

for(int i=0;i<n;i++)
{
    if(sumCol[i] != maxSum)
    {
        cout<<"Not Possible\n";
        return INF;
    }
}

return count;
```

---

### Find number of transformation to make two Matrix Equal
[Link]()

**Problem Description** - Given two matrices A and B of order `n * m`. 
The task is to find the required number of transformation steps so that both matrices became equal, print -1 if it is not possible. 
Transformation step is as: 
* Select any one matrix out of two matrices. 
* Choose either row/column of the selected matrix. 
* Increment every element of select row/column by 1.

**Solution Approach** - 
* Replace every element A[i][j] = A[i][j] - B[i][j];
* Now for each element check whether `A[i][j] - A[i][0] - A[j][0] + A[0][0] == 0` or not, if not return -1
* To get count of minimum number of operations - 
  * ans += sum(abs(A[0][j]) ) for all j
  * ans += sum(abs(A[i][0] - A[0][0]) for all i




