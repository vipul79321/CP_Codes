## Counting Labeled graph
[Link](https://cp-algorithms.com/combinatorics/counting_labeled_graphs.html)

Considering only following types of graph - 
* Let n be number of vertices labeled from 1 to n.
* Graph doesnt contain any self-loop or multiple edges.

---

* G(n) be total number of such graphs
* C(n) be total number of such graphs which are connected
* D(n) be total number of such graphs which are disconnected

**G(n) == D(n) + C(n)**

### Total number of labeled graphs - G(n)
* Number of undirected edges in above graph such that they dont form self-loop, multiple edges = n*(n-1)/2;
* Therefore total number of labeled graphs will be `G(n) = pow(2, n*(n-1)/2)`;


### Total number of disconnected labeled graphs - D(n)
* D(n) can be written as - **1/n * Summation( k * Binomial(n,k) * C(k) * G(n-k) for k in range 1 to n-1)**
* Breaking down the above formula - 
  * We consider each possible connected component size from 1 to n-1. 
  * For each connected size, we will consider each subset of vertices of that size using Binomial(n,k)
  * For each subset, we will try to make each node as root of that connected component, by multiplying by k
  * For remaining n-k vertices, we dont care how they get connected so G(n-k)
  * Now since we tried making each node as root, there will be equal amount of repetition and hence divide by n. 

### Total number of disconnected labeled graphs - C(n)
* Return G(n) - D(n);


## Number of labeled graphs with n vertices and k connected components

* D[n][k] = Summation ( Binomial(n-1,s-1) * C(s) * D[n-s][k-1] for s in range 1 to n);
* Breaking down the above formula - 
  * We try to put nth vertex in every possible connected component size, hence loop from 1 to n
  * To make connected component of size s, we need to select s-1 vertices from n-1 vertices hence binomial(n-1,s-1)
  * C(s) will be number of ways to make that component connected
  * And for remaining vertices D[n-s][k-1]

