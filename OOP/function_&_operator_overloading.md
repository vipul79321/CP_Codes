[Link](https://www.geeksforgeeks.org/function-overloading-c/)

### Function Overloading ###
Function overloading is a feature in C++ where two or more functions can have the same name but different parameters.

See this link for exact working of overloading, how decision is made which function is to be executed - https://docs.microsoft.com/en-us/cpp/cpp/function-overloading?view=msvc-160
1. An exact match was found.
2. A trivial conversion was performed  - [Trivial Conversions](https://docs.microsoft.com/en-us/cpp/cpp/function-overloading?view=msvc-160#trivial-conversions)
3. An integral promotion was performed. (Char, Unsigned char, and short are promoted to an int. Float is promoted to double) [Integral promotion](https://en.cppreference.com/w/cpp/language/implicit_conversion)
4. A standard conversion to the desired argument type exists.
5. A user-defined conversion (either conversion operator or constructor) to the desired argument type exists.
6. Arguments represented by an ellipsis were found. (ellipsis signifies undefined number of parameters represented by ... )

---

[Link](https://www.geeksforgeeks.org/function-overloading-in-c/)

See this table - [Overloading consideration](https://docs.microsoft.com/en-us/cpp/cpp/function-overloading?view=msvc-160#overloading-considerations)

###  Functions that cant be overloaded ###
1. Differ only in return type.
2. Member function declarations with the same name and the name parameter-type-list cannot be overloaded if any of them is a static member function declaration. 
3. Declaration differ only in pointer (*) or array ([]) . Example - int *ptr is equivalent to int ptr[]
4. Parameter declarations that differ only in that one is a function type and the other is a pointer to the same function type are equivalent.
5.  Two parameter declarations that differ only in their default arguments are equivalent.

---

[Link](https://www.geeksforgeeks.org/function-overloading-and-const-functions/)

### Function overloading and const keyword ###
1. const plays a role in overloading when applied to whole function.
**Note** - const function are only allowed for member functions.
```c++
class Test
{
public:
	void fun() const {cout << "fun() const called " <<endl;}
	void fun(){cout << "fun() called " << endl;}
};

void something() const {cout<<"something";}  // will throw an error, in c++ only member functions can be const.

int main()
{
	Test t1;
	const Test t2;
	t1.fun();  // will call non-const fun.
	t2.fun();  // call const fun.
	return 0;
}
```

2. const keyword also plays a role in overloading when parameter is passed with reference or pointer.
```c++
void fun(const int &i)
{
    cout << "fun(const int &) called ";
}
void fun(int &i)
{
    cout << "fun(int &) called " ;
}
int main()
{
    const int i = 10;
    fun(i);    // will call fun(const &i)
    return 0;
}
```

Explaination - This rule actually makes sense. So, if the parameter ‘i’ is passed by value, so ‘i’ in fun() is a copy of ‘i’ in main(). Hence fun() cannot modify ‘i’ of main(). Therefore, it doesn’t matter whether ‘i’ is received as a const parameter or normal parameter. When we pass by reference or pointer, we can modify the value referred or pointed, so we can have two versions of a function, one which can modify the referred or pointed value, other which can not.

---

[Link](https://www.geeksforgeeks.org/does-overloading-work-with-inheritance/)

Overloading doesnt work with inheritance. for e.g. see this code - 
```c++
class Base
{
public:
	void f(int i){cout << "f(int): ";}
};
class Derived : public Base
{
public:
	void f(char c){cout << "f(char): ";}
};
int main()
{
    Derived d;
    d.f('a');
    d.f(1234567);   // will throw overflow error, as it will try to convert it to char only. It wont concern with int definition as it is overridden
	return 0;
}
```

---

[Link](https://www.geeksforgeeks.org/can-main-overloaded-c/)

1. main can be overloaded only as a member function. 
```c++
class Test
{
public:
	void main(int s){cout<<s<<endl;}
};
int main()
{
	Test obj;
	obj.main(3);
	return 0;
}
```
**Note** - Main is not a reserved keyword in c++, c, java. there can be variable named main too.

---

[Link](https://www.geeksforgeeks.org/g-fact-30-function-overloading-and-float-in-c/)

### Problem with float in overloading ###

```c++
void test(float s){cout << "Function with float called ";}
void test(int s){cout << "Function with int called ";}
int main()
{
	test(3.5f); // Added suffix "f" to tell compiler its float value
	test(3.5); // will treat as double and will give error of ambiguity
	return 0;
}
```

