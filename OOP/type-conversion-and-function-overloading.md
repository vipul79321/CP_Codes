> **NOTE** - Brace-initialization disallows conversions that result in data loss. E.g. - `int x { 3.5 };` will throw an error, while `int x = 3.5;` wont.

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
 
