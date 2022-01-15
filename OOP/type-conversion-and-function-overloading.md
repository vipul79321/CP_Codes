> **NOTE** - Brace-initialization disallows conversions that result in data loss. E.g. - `int x { 3.5 };` will throw an error, while `int x = 3.5;` wont.

---

### Numeric Promotion
[Link](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)

* **Floating Point Promotions**
  * `float` to `double`
* **Integral Promotions**
  * `signed char` or `signed short` can be converted to `int`. 
  * `unsigned char`, `char8_t`, and `unsigned short` can be converted to `int` if int can hold the entire range of the type, or `unsigned int` otherwise.
  * If char is signed by default, it follows the signed char conversion rules above. If it is unsigned by default, it follows the unsigned char conversion rules above.
  * `bool` can be converted to `int`

---

### Numeric Conversions
[Link](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)
* Converting an integral type to any other integral type (excluding integral promotions)
* Converting a floating point type to any other floating point type (excluding floating point promotions)
* Converting a floating point type to any integral type
* Converting an integral type to any floating point type
* Converting an integral type or a floating point type to a bool
* Compiler will generally issue warning for narrowing conversion resulting in loss of data

---

### Airthmetic Conversion
[Link](https://www.learncpp.com/cpp-tutorial/arithmetic-conversions/)

**Operators that require operands to be of the same type** - 
* The binary arithmetic operators: `+, -, *, /, %`
* The binary relational operators: `<, >, <=, >=, ==, !=`
* The binary bitwise arithmetic operators: `&, ^, |`

**Airthmetic conversion priority list**
* long double (highest)
* double
* float
* unsigned long long
* long long
* unsigned long
* long
* unsigned int
* int (lowest)

**Airthmetic conversion rules** - 
* If the type of `at least one` of the operands is on the priority list, the operand with lower priority is converted to the type of the operand with higher priority.
* Otherwise (the type of neither operand is on the list), both operands are numerically promoted.

---

>**NOTE** - Syntax of static cast - `static_cast < new-type > ( expression )`

---

### Differentiation basis for overloaded functions
[Link](https://www.learncpp.com/cpp-tutorial/function-overload-differentiation/)

| Function property |	Used for overloading | Notes |
| ----------------- | -------------------- | ----- |
| Number of parameters	| Yes	| |
| Type of parameters | Yes	| Excludes typedefs, type aliases, and `const qualifier on value parameters`. Includes ellipses. |
| Return type	| No | |

> **NOTE** - For member functions, additional function-level qualifiers(qualifiers applied to whole function) are also used for overloading differentiation
> | Function - level qualifier | Used for overloading | 
> | -------------------------- | -------------------- | 
> | const or volatile | Yes |
> | Ref-qualifiers | Yes |

---

### Resolving overloaded functions
[Link](https://docs.microsoft.com/en-us/cpp/cpp/function-overloading?view=msvc-160) | [Link](https://www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches/) 

**Steps involved in resolving function call** - 
1. An exact match was found or a trivial conversion was performed  - [Trivial Conversions](https://docs.microsoft.com/en-us/cpp/cpp/function-overloading?view=msvc-160#trivial-conversions)
2. Numeric Promotion
3. Numeric conversion
4. A user-defined conversion (either conversion operator or constructor) to the desired argument type exists.
5. Arguments represented by an ellipsis were found. (ellipsis signifies undefined number of parameters represented by ... )
6. Finally no match found compiler error is issued

> **NOTE** - 
> * If at any step, there is more than one candidate match for function call then ambiguous call error is thrown
> * For resolving overloaded function with multiple arguments
>   * The compiler applies the matching rules to each argument in turn
>   * In other words, the function chosen must provide a better match than all the other candidate functions for at least one parameter, and no worse for all of the other parameters.
 
---

### Function Templates
[Link](https://www.learncpp.com/cpp-tutorial/function-templates/) | [Link](https://www.learncpp.com/cpp-tutorial/function-template-instantiation/) | [Link](https://www.learncpp.com/cpp-tutorial/function-templates-with-multiple-template-types/)

```c++
#include <bits/stdc++.h>
using namespace std;

template<typename T, typename U>

auto maximum(T x, U y)  // auto - helps deciding return type accordingly
{
    auto temp =  x > y ? x : y;
    cout<<typeid(x).name()<<" "<<typeid(y).name()<<" "<<typeid(temp).name()<<endl;
    return temp;
}

template<typename T>
void fun(T x)
{
    cout<<typeid(x).name()<<endl;
}

int main()
{
    fun<double>(2);  // will call fun(double), as we are specifically mentioning that
    fun<int>(2);  // will call fun(int), as we are specifically mentioning that
    fun<>(3);  // will use template type deduction, wont consider non-template functions
    fun(3);  // will consider non-template functions as well, and may use template-type deduction if neccessary
    
    maximum<int,int>(1,2);  // will call maximum(int, int)
    maximum<int,double>(1,2);  // will call maximum(int, double)
    maximum<double,double>(1,2);  // will call maximum(double, double)
    maximum<>(1,2);  // will use template type deduction and will call maximum(int, int)
    maximum(1,2.2);  // will use template type deduction and will call maximum(int, double)
   
    return 0;
}
/*
output produced from above code will be
d
i
i
i
i i i
i d d
d d d
i i i
i d d
*/
```

---

>**NOTE** -  Limitation of pass by reference in function in c++
> * Non-const references can only reference non-const l-values (e.g. non-const variables), so a reference parameter cannot accept an argument that is a const l-value or an r-value (e.g. literals and the results of expressions).
> * We have to use const reference to work with const l-values or an r-value

---

> **NOTE** - We can also pass pointer by reference
> ```c++
> void foo(int*& ptr) // pass pointer by reference
> {
> 	ptr = nullptr; // this changes the actual ptr argument passed in, not a copy
> }
> ```

---

> **NOTE** - Addresses are actually passed by value. See code below for explanation - 
> ```c++
> #include <iostream>
> void setToNull(int* tempPtr)
> {
>    // we're making tempPtr point at something else, not changing the value that tempPtr points to.
>    tempPtr = nullptr; // use 0 instead if not C++11
> }
>
> int main()
> {
>    // First we set ptr to the address of five, which means *ptr = 5
>    int five{ 5 };
>    int* ptr{ &five };
>
>    // This will print 5
>    std::cout << *ptr;
>
>    // tempPtr will receive a copy of ptr
>    setToNull(ptr);
>
>    // ptr is still set to the address of five!
>    // If we really want to change value of ptr, then we have to pass ptr by reference
>
>    // This will print 5
>    if (ptr)
>        std::cout << *ptr;
>    else
>        std::cout << " ptr is null";
>
>    return 0;
> }
> ```

---
 
> **NOTE** - See code below on how to extend life-time / scope of a variable
> ```c++
> int returnByValue()
> {
>     return 5;
> }
>
> int& returnByReference()
> {
>      static int x{ 5 }; // static ensures x isn't destroyed when the function ends
>      return x;
> }
>
> int main()
> {
>     int giana{ returnByReference() }; // case A -- ok, treated as return by value
>     int& staticX { returnByReference() } ; // Case B -- ok, now we can access and modify static int x outside returnByReference();
>     int& ref{ returnByValue() }; // case C -- compile error since the value is an r-value, and an r-value can't bind to a non-const reference
>     const int& cref{ returnByValue() }; // case D -- ok, the lifetime of the return value is extended to the lifetime of cref
> 
>     return 0;
> }
>```
 
---

### Function Pointers
[Link](https://www.learncpp.com/cpp-tutorial/function-pointers/)

**Syntax to make pointer to function** - 
* `return_type (*pointer_name)(function parameters)`
* `function< return_type(paramters) >pointer_name`
* Or by using `auto` keyword, if we are intializing when declaring.

```c++
#include <iostream>
#include<functional>
int foo(int x)
{
	return x;
}

int main()
{
 int (*fcnPtr1)(int) = &foo;
 std::function<int(int)>fcnPtr2 = &foo;
 auto fcnPtr3{ &foo };
	
 std::cout<<fcnPtr1(3)<<"\n";
 std::cout<<fcnPtr2(3)<<"\n";
 std::cout<<fcnPtr3(3)<<"\n";

	return 0;
}
/*
Output
3
3
3
*/
```

---

>**NOTE** - Command Line arguments
>* To invoke a c++ program with command line input
>```c++
>int main(int argc, char* argv[])
>```
>* **argc** is an integer parameter containing a count of the number of arguments passed to the program (think: argc = argument count). argc will always be at least 1, because the first argument is always the name of the program itself. Each command line argument the user provides will cause argc to increase by 1.
>* **argv** is where the actual argument values are stored (think: argv = argument values, though the proper name is “argument vectors”). Although the declaration of argv looks intimidating, argv is really just an array of C-style strings. The length of this array is argc.

---

### Lambda functors in c++
[Link](https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/) | [Link](https://www.learncpp.com/cpp-tutorial/lambda-captures/)

**Syntax for lambda** - 
```c++
[capture clause] (parameters) -> return_type
{
 body;
}
```

* Lambdas are not functions, they are functor object, which have overloaded `operator()`
* return_type can be ommited, if not provided `auto` is use instead to infer return-type
* Ways of storing lambdas - 
  * Regular function pointer - Only works with an empty capture clause
  * Using std::function
  * auto - Stores lambda with its real type. But we cant use auto when we need to pass our lambda to a function

```c++
#include <functional>

int main()
{
  // A regular function pointer. Only works with an empty capture clause.
  double (*addNumbers1)(double, double){
    [](double a, double b) {
      return (a + b);
    }
  };

  addNumbers1(1, 2);

  // Using std::function. The lambda could have a non-empty capture clause (Next lesson).
  std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
    [](double a, double b) {
      return (a + b);
    }
  };

  addNumbers2(3, 4);

  // Using auto. Stores the lambda with its real type.
  auto addNumbers3{
    [](double a, double b) {
      return (a + b);
    }
  };

  addNumbers3(5, 6);

  return 0;
}
```

**Generic Lambdas** -
* Lambdas with one or more auto parameters are called generic lambdas
```c++
#include<bits/stdc++.h>
using namespace std;

int main()
{
   auto ptr{
       [](auto x) -> void {
           static int y = 1;
           cout<<y<<" "<<x<<endl;
           y++;
       }
   };
   
   ptr(4);  // 1 4
   ptr("hello"); // 1 hello
   ptr(3);  // 2 3

	return 0;
}
```

> **NOTE** - Lambdas can only access specific kinds of identifiers: `global identifiers`, `entities that are known at compile time`, and `entities with static storage duration`

**Capture Clause** - 
* The capture clause is used to (indirectly) give a lambda access to variables available in the surrounding scope that it normally would not have access to.
* Captures default to `const` value. If we want to modify captured value we need to use `mutable` keyword. Also captures by value result in lambda recieving clone of captured variable not the original variable.
```c++
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int x = 5;
    auto decrementAndPrint{
        [x]() mutable
        {
            x--; // without mutable this line will give an error because x captured by lambda is clone of x and constant
            cout<<x<<endl;
        }
    };
    
    decrementAndPrint(); // will print 4
    cout<<x<<endl;  // value of x wont change as lambda recieved the clone of x. Will print 5

	return 0;
}
```

* Capturing by reference
```c++
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int x = 5;
    auto decrementAndPrint{
        [&x]() // captured by reference
        {
            x--; 
            cout<<x<<endl;
        }
    };
    
    decrementAndPrint();
    cout<<x<<endl;

	return 0;
}
```
