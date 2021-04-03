## nth - Catalan Number

Following are the recursion for nth catalan number:

```c++
Catalan[0] = 1, Catalan[n] = summation of (Catalan[i]*Catalan[n-i-1]) for i in range (0,n-1);
```
```c++
Catalan(n) = Binomial(2n,n)/(n+1);
```

Applications of Catalan Number -  \
1). Number of binary search tree with n nodes = Catalan[n]. \
2). Number of expressions having n pairs of correctly matched paranthesis = Catalan[n]. \
3). Given a number n, return the number of ways you can draw n chords in a circle with 2 x n points such that no 2 chords intersect = Catalan[n]. \
4). The number of paths with 2n steps on a rectangular grid from bottom left, i.e., (n-1, 0) to top right (0, n-1) that do not cross above the main diagonal = Catalan[n]. - Interpret it as Dyck word sequence here number of up moves should be less than number of right moves in any prefix. \
5). Number of ways to make a Dyck string with **n Xs and n Ys such that no prefix of that string has more number of Ys than number of Xs = Catalan[n].** - See it as follows any dyck word can be written as W = XwYw where w are Dyck words. \
6). Number of permutations of n numbers such that no three terms are increasing = Catalan[n].

---

## Stirling number of 2nd form

```c++
S[n][k] = S[n-1][k]*k + S[n-1][k-1]
S[n][k] represents the number of partition of n numbers into k sets.
```
---

## Bell number

```c++
Bell[n] = summation of S[n][i] for i in range 0 to n
```

```c++
Bell_triangle[i][j] = Bell_triangle[i-1][j-1] + Bell_triangle[i][j-1]

Bell_triangle[i][0] = Bell_triangle[i-1][i-1]

Bell_triangle[n][k] = number of partitions of n+1 elements where k+1 is the largest element which can be alone in its set.
  
Bell[n] = Bell_triangle[n][0] or Bell_triangle[n-1][n-1]
```

---

## Binomial Coefficient 

```c++
C[i][j] = C[i-1][j-1] + C[i-1][j]
```

```c++
Space efficient computation - 
C[0] = 1;
for(i=1;i<n;i++)
{
  for(j=i;j>0;j--)
  {
    C[j] = C[j] + C[j-1];
  }
}
```

---

## Permutation Coefficient

```c++
P[n][k] = P[n-1][k] + k*P[n-1][k-1]
```
