## Reverse a stack using recursion
[Link](https://www.geeksforgeeks.org/reverse-a-stack-using-recursion/)

**Solution Approach** - 
* Recursion will be as follow, first pop and store the top of stack. 
* Now reverse the remaining stack. 
* And finally insert stored value at the bottom of the stack.

```c++
void insertAtBottom(stack<int>&st, int x)
{
    if(st.size() == 0)
    {
        st.push(x);
        return;
    }
    
    int a = st.top(); st.pop();  //store top
    insertAtBottom(st,x); // insert at the bottom of remaining stack.
    
    st.push(a); // push top back again
}

void reverse(stack<int>&st)
{
    if(st.size() > 1)
    {
        int x = st.top(); st.pop();  //store the top in x
        reverse(st);  // reverse remaining stack
        
        insertAtBottom(st,x); // insert x at the bottom of stack.
    }
}

```
---

## Sort a stack only using recursion
[Link](https://www.geeksforgeeks.org/sort-a-stack-using-recursion/)

```c++
void sortedInsert(stack<int>&st, int x)
{
    if(st.size() == 0 || st.top() > x)
    {
        st.push(x);
        return;
    }
    
    int a = st.top();st.pop();
    sortedInsert(st,x);
    
    st.push(a);
}

void sortStack(stack<int>&st)
{
    if(st.size() < 2)return;
    
    int a = st.top(); st.pop();
    sortStack(st);
    
    sortedInsert(st,a);
}
```

---

## Sort a stack using a temporary stack | Sort an array using stack | Worst Case - O(n^2) | Based on idea of insertion sort
[Link](https://www.geeksforgeeks.org/sort-stack-using-temporary-stack/) | [Link](https://www.geeksforgeeks.org/sorting-array-using-stacks/)

**Solution Approach | Similar to Insertion Sort** - 
* While given stack is not empty
  * `a = st.top(); st.pop();`.
  * `while(!temp_st.empty() && temp_st.top() > a)` push `temp_st.top()` to `st` and `pop temp_st`.
  * Then push a to temp_st
* Finally temp_st will contain main stack in sorted order.

---

## Reverse a stack without using extra space in O(n)
[Link](https://www.geeksforgeeks.org/reverse-stack-without-using-extra-space/)

**Solution Approach** - Use linked list implementation of stack. And Reversing a linked list only take O(n) time.

---

## Check if we can convert one queue into another queue using stack | Check if array is stack sortable
[Link](https://www.geeksforgeeks.org/check-queue-can-sorted-another-queue-using-stack/) | [Link](https://www.geeksforgeeks.org/check-array-stack-sortable/)

This Question can be rephrased as follows - 
* Check if we can scan an array from left to right and obtain the given array using stack, Only operation allowed on the other array is append an element to its end.
* Sometimes second array can be sorted one, so it can be asked as **check if given array is stack sortable.**

**Solution Approach** - 
* Intialize current_required = q2.front();
* Take an element from q1, if it is the required item then continue else push it in the stack.
* Finally if our stack is not empty at the end then its not possible.

```c++
bool check(queue<int>&q1, queue<int>&q2)
{
    stack<int>st;
    while(!q1.empty())
    {
        while(!st.empty() && st.top() == q2.front())  // check if we st.top work as required.
        {
            st.pop();
            q2.pop();
        }
        
        st.push(q1.front());  // otherwise we have no option other than push q1.front() to stack.
        q1.pop();
    }
    
    while(!st.empty() && st.top() == q2.front())
    {
        st.pop();
        q2.pop();
    }
    
    if(!st.empty())return 0;
    else
    return 1;
}
```
---

## Tower of Hanoi

**Recursive Solution** - 

```c++
void towerOfHanoi(int n, int from_rod, int auxilary_rod, int to_rod)
{
    if(n==1)
    {
        cout<<"Move disk 1 from: "<<from_rod<<" to "<<to_rod<<endl;
        return;
    }
    
    towerOfHanoi(n-1,from_rod, to_rod, auxilary_rod);
    
    cout<<"Move disk "<<n<<" from: "<<from_rod<<" to "<<to_rod<<endl;
    
    towerOfHanoi(n-1,auxilary_rod,from_rod,to_rod);
}
```

**Iterative Solution**
**Steps** - 
* Calculate the total number of moves required i.e. "pow(2, n) - 1" here n is number of disks.
* If number of disks (i.e. n) is even then interchange destination pole and auxiliary pole.
* Loop i from i==1 to i==total_num_moves: 
  * If i%3==1 : Legal movement between Source and Destination Pole
  * If i%3==2: Legal movement between Source and Auxiliary Pole
  * If i%3==0: Legal movement between Auxiliary and Destination Pole
* Legal Movement means `to_rod.top() > from_rod.top()` and intially from_rod should be non-empty.

---

## Remove brackets from given algebraic expression
[Link](https://www.geeksforgeeks.org/remove-brackets-algebraic-string-containing-operators/)

**Problem Description** - Given an algebraic expression with +,-, (, ) -> simplify it by opening(removing) brackets

**Solution Approach** -
* We will maintain an stack containing global sign and flip the local signs accordingly.

```c++
string simplifyExpression(string expr)
{
    stack<int>global_sign;
    global_sign.push(0); // symbolising + sign.
    
    string ans = "";
    
    for(int i=0;i<expr.length();i++)
    {
        if(i==0 && expr[i] == '(')
        continue;
        
        if(expr[i] == '(')
        {
            if(expr[i-1] == '+')
            global_sign.push(global_sign.top());
            else
            global_sign.push(1 - global_sign.top());
        }
        else if(expr[i] == '+')
        {
            if(global_sign.top())ans = ans + "-";
            else
              ans = ans + "+";
        }
        else if(expr[i] == '-')
        {
            if(global_sign.top())ans = ans + "+";
            else
              ans = ans + "-";
        }
        else if(expr[i] == ')')
        {
            global_sign.pop();
        }
        else
        {
            ans = ans + expr[i];
        }
    }
    return ans;
}
```

---

## Range Queries for Longest Balanced Bracket Subsequences
[Link](https://www.geeksforgeeks.org/range-queries-longest-correct-bracket-subsequence/) | [Link](https://codeforces.com/contest/380/problem/C)

**Problem Description** - Given a string containing '(' and ')'. And Q queries of type [l,r]. We need to ans length of longest balanced paranthesis subsequence in range [l,r]

**Solution Description** - 
* Make segment tree, where
  * st[id][0] - > length of longest balanced paranthesis subsequence in interval represented by id
  * st[id][1] - > Count of invalid open paranthesis in interval represented by id
  * st[id][2] - > Count of invalid close paranthesis in interval represented by id
* Merging segment tree nodes - 
  * st[id][0] = st[left][0] + st[right][0] + 2 * min(st[left][1], st[right][2]);
  * st[id][1] = st[left][1] + st[right][1] - min(st[left][1], st[right][2]);
  * st[id][2] = st[left][2] + st[right][2] - min(st[left][1], st[right][2]);

---

## Find maximum of minimums for all window size for a given array
[Link](https://www.hackerrank.com/challenges/min-max-riddle/problem) | [Link](https://www.geeksforgeeks.org/find-the-maximum-of-minimums-for-every-window-size-in-a-given-array/)

**Solution Approach** - 
* For each element find its next smaller element to the right and next smaller element to the left
* Now iterate over each element, that element will be a minimum for `len = right[i] - left[i] - 1;window_size = [1,len]`, so update `ans[len] = max(ans[len],arr[i]);`
* Now iterate from len = n-1 to len = 1: 
  * ans[len] = max(ans[len],ans[len+1]);


