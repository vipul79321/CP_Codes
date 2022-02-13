> #### Infix =  Expression of form a operator b
> #### Postfix = Expression of form a b operator
> #### Prefix = Expression of form operator a b

## Why postfix representation of expression is better than infix | [Link](https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/)
* The compiler scans the expression either from left to right or from right to left. 
* Consider the below expression: `a op1 b op2 c op3 d` where `op1 = +, op2 = * , op3 = +`
* The compiler first scans the expression to evaluate the expression `b * c`, then again scans the expression to add `a` to it. The result is then added to `d` after another scan.
* The repeated scanning makes it very in-efficient. It is better to convert the expression to postfix(or prefix) form before evaluation.

## Precedence order of operators
```c++
int precedence(char c) {
    if(c == '^')
        return 3;
    else if(c == '/' || c=='*')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}
```

## Infix to Postfix conversion
[Link](https://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/)

**Steps**
* Scan infix expression from left to right
* If scanned character is not an operator, append it in ans or print it.
* If scanned character is an '(' push it in the stack.
* If scanned character is an ')' pop till we encounter '('
* If scanned character is an operator - 
    * while precedence(st.top()) >= precendence(s[i]), pop and append them in result. That is pop all the characters in the stack which have **equal or greater precedence than current operator**.
    * Push current operator into stack
* Finally after scanning is done, pop the stack and append them in result.

See code below for more details - 
```c++
string infixToPostfix(string infix)
{
    string postfix = "";
    stack<char>st;
    
    for(auto c:infix)
    {
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
        {
            postfix += c;
            continue;
        }
        else if(c == '(')
        {
            st.push('(');
        }
        else if(c == ')')
        {
            while(!st.empty() && st.top() != '(')
            {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // pop '('
        }
        else
        {
            while(!st.empty() && precedence(st.top()) >= precedence(c))
            {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    
    while(!st.empty())
    {
        postfix += st.top();
        st.pop();
    }
    
    return postfix;
}
```

---

## Postfix to Infix conversion
[Link](https://www.geeksforgeeks.org/postfix-to-infix/)

**Steps** - 
* Scan the given postfix expression
    * If scanned character is operand, push in stack
    * If scanner character is operator, pop A then B from stack and push `(B operator A)` into stack
* Finally return stack.top() as answer

```c++
string postfixToInfix(string postfix)
{
    stack<string>st;
    
    for(auto c:postfix)
    {
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
        {
            st.push(string(1,c));
        }
        else
        {
            string A = st.top(); st.pop();
            string B = st.top(); st.pop();
            string op = string(1,c);
            
            st.push("(" + B + op + A + ")");
        }
    }
    return st.top();
}
```
---

## Infix to Prefix Conversion
[Link](https://www.geeksforgeeks.org/convert-infix-prefix-notation/)

**Steps** - 
* Reverse the given infix expression. And **change '(' to ')' and vice-versa**
* Obtain the postfix conversion of reversed infix exrpession with slight modification as follows - 
    * When we scan an operator
       * If operator == '^', pop all the characters which have equal precedence than '^'
       * else, pop all the characters which have **greater precedence than current operator**. 
* Reverse the obtained postfix expression and return it as ans.

```c++
string infixToPrefix(string infix)
{
    reverse(infix.begin(),infix.end());  //reverse and switch paranthesis types
    for(int i=0;i<infix.size();i++)
    {
        if(infix[i] == '(')infix[i] = ')';
        else if(infix[i] == ')')infix[i] = '(';
    }
    
    string postfix = ""; // simply obtain postfix of reversed infix expression
    stack<char>st;
    
    for(auto c: infix)
    {
        if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
        {
            postfix += c;
            continue;
        }
        else if(c == '(')
        {
            st.push('(');
        }
        else if(c == ')')
        {
            while(!st.empty() && st.top() != '(')
            {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // pop '('
        }
        else
        {
            if(c == '^')   // ******************Modification part*****************
            {
                while(!st.empty() && precedence(st.top()) == precedence(c))
                {
                    postfix += st.top();
                    st.pop();
                }
                st.push(c);
            }
            else
            {
                while(!st.empty() && precedence(st.top()) > precedence(c))
                {
                    postfix += st.top();
                    st.pop();
                }
                st.push(c);
            }
        }
    }
    
    while(!st.empty())
    {
        postfix += st.top();
        st.pop();
    }

    reverse(postfix.begin(),postfix.end());  // Make it prefix expression
    return postfix;
}
```
---

## Prefix to Infix Conversion
[Link](https://www.geeksforgeeks.org/prefix-infix-conversion/)

**Steps**
* Scan the prefix expression **from right to left**
    * If the scanned character is operand push it in the stack.
    * If the scanned character is operator, pop A then B from stack and push `( A  op B)` into stack.
* Finally return stack.top() as ans.
* Code is similar to Postfix to Infix conversion.

---

## Prefix to Postfix Conversion
[Link](https://www.geeksforgeeks.org/prefix-postfix-conversion/)

**Steps** - 
* Scan the prefix expression **from right to left.**
    * If the scanned character is operand simply push it in stack.
    * If the scanned character is an operator, pop A then B from stack and push `A B op` to the stack.
* Finally return stack.top() as ans.

```c++
string prefixToPostfix(string prefix)
{
    stack<string>st;
    for(int i=prefix.size()-1;i>=0;i--)
    {
        if(isOperator(prefix[i]))
        {
            string A = st.top(); st.pop();
            string B = st.top(); st.pop();
            string op = string(1,prefix[i]);
            
            st.push(A + B + op);
        }
        else
        {
            st.push(string(1,prefix[i]));
        }
    }

    return st.top();
}
```
---

## Postfix to Prefix conversion
[Link](https://www.geeksforgeeks.org/postfix-prefix-conversion/)

**Steps** - 
* Scan the prefix expression **from left to right.**
    * If the scanned character is operand simply push it in stack.
    * If the scanned character is an operator, pop A then B from stack and push `op B A` to the stack.
* Finally return stack.top() as ans.

```c++
string postfixToPrefix(string postfix)
{
    stack<string>st;
    for(auto c:postfix)
    {
        if(isOperator(c))
        {
            string A = st.top(); st.pop();
            string B = st.top(); st.pop();
            string op = string(1,c);
            
            st.push(op + B + A);
        }
        else
        {
            st.push(string(1,c));
        }
    }
    return st.top();
}
```
---


## Notes
[Link](https://www.geeksforgeeks.org/stack-set-4-evaluation-postfix-expression/) | [Link](https://www.geeksforgeeks.org/expression-evaluation/)
* For evaluating a postfix expression follow below steps - 
  * Scan the expression from left to right.
    * If the scanned character is an operand, push it in the stack.
    * else pop A then B from stack and push `B operator A` into the stack.
  * Finally stack.top() will contain the value of the expression

* For evaluating an infix expression follow below steps - 
  * Procedure is completely similar to conversion to postfix with following modification - 
    * Instead of printing operand, push them in value stack.
    * Whenever performing pop operation, pop operator from operator-stack and pop A then B from value stack and push `A operator B` into value stack.



  





