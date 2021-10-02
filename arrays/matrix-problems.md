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



