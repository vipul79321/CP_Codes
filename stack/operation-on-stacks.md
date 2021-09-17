## Reverse a stack using recursion
[Link](https://www.geeksforgeeks.org/reverse-a-stack-using-recursion/)

**Solution Approach** - 
* Recursion will be as follow, first pop and store the top of stack. Now reverse the remaining stack. And finally insert stored value at the bottom of the stack.

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

## Sort a stack using a temporary stack | Sort an array using stack
[Link](https://www.geeksforgeeks.org/sort-stack-using-temporary-stack/) | [Link](https://www.geeksforgeeks.org/sorting-array-using-stacks/)

**Solution Approach** - 
* While given stack is not empty
  * `a = st.top(); st.pop();`.
  * `while(!temp_st.empty() && temp_st.top() > a)` push temp_st.top() to main stack and pop temp_st.
  * Then push a to temp_st
* Finally temp_st will contain main stack in sorted order.

---

## Reverse a stack without using extra space in O(n)
[Link](https://www.geeksforgeeks.org/reverse-stack-without-using-extra-space/)

**Solution Approach** - Use linked list implementation of stack. And Reversing a linked list only take O(n) time.

---

## Check if we can convert one queue into another queue using stack | 
This Question can be rephrased as follows - 
* Check if we can scan an array from left to right and obtain the given array using stack, Only operation allowed on the other array is append an element to its end.
* Sometimes second array can be sorted one, so it can be asked as check if given array is stack sortable.

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
