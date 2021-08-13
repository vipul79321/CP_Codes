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

---

## Lobb Number
Lobb number `L(m,n)` counts the number of ways that `n + m open parentheses and n − m close parentheses` can be arranged to form the start of a valid sequence of balanced parentheses.
```c++
L[m][n] = (2m+1) * Binomial(2n,m+n) / (m+n+1)

L[0][n] = Catalan[n]
```

---

## Eulerian Number
In combinatorics, the Eulerian Number `A(n, m)` is the number of permutations of the numbers 1 to n in which exactly m elements are greater than previous element.

```c++
A[n][m] = ((n-1) - (m-1))*A[n-1][m-1] + (m+1)*A[n-1][m]
```

---

## Entringer Number
The Entringer Number `E(n, k)` are the number of permutations of {1, 2, …, n + 1}, starting with k + 1, which, after initially falling, alternatively fall then rise.
```c++
E[n][k] = E[n][k-1] + E[n-1][n-k]

E[0][0] = 1;
E[i][0] = 0 otherwise
```

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

## Calculate nth Row of Pascal Triangle

```c++
vector<int>row;
row.pb(1);
for(i=1;i<=n-1;i++)
{
    int val = row[i-1]*(n-i+1)/i;
    row.pb(val);
}
row.pb(1);
```
