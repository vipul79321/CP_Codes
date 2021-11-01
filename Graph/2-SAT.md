### 2-SAT
[Link](https://cp-algorithms.com/graph/2SAT.html)

* 2-SAT(Boolean satisfiability problem) is the problem of assigning Boolean values to variables to satisfy a given Boolean formula.
* Usually boolean formula will be **conjuction( ^, and)** of multiple clauses, where each clause will have two terms in form of or(v) , implication(->)

E.g. of formula -  `(a v ~b) ^ (~a ∨ b) ^ (~a v ~b) ^ (a v ~c)` , problem is to assign value to a,b,c so that boolean formula evaluates to true

**IMP identities** - 
* `(a v b) == (~a -> b) ^ (~b -> a)`
* `a <-> b == (a -> b) ^ (b -> a)`
* `~(p->q) == (~p v p)`

**Solution Approach** - 
* Convert the expression into **conjuction of implication clauses**
* If in expression there is clause `a -> b` then add a `directed edge from a to b`
* Now, solution to above expression exist `if and only if x and ~x` doesnt lie in same SCC
* Also, if we `sort SCC in topological order` then valid assignment to x will be:
  * **if SCC[x] < SCC[~x] then x will take false value**
  * **else x will take true value**
