[Link](https://www.geeksforgeeks.org/function-overloading-c/)

## Function Overloading ##
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

---

## Operator Overloading ##

[Link](https://www.geeksforgeeks.org/operator-overloading-c/)

In C++, we can change the way operators work for user-defined types like objects and structures. This is known as operator overloading. 
```c++
return-type operator symbol (parameters)
```

Example of binary operator overloading - 
```c++
class C {
private:
	int a;
public:
	C(int x = 0) {a = x;}
	C operator + (C const &obj) {
		C res;
		res.a = a + obj.a;
		return res;
	}
	void print() { cout << a << endl; }
};
int main()
{
	C c1(10), c2(2);
	C c3 = c1 + c2; // An example call to "operator+"   // imagine it as c1.operator+(c2);
	c3.print();
}
```

Example of unary operator overloading - 
```c++
class Check
{
  private:
    int i;
  public:
    Check(): i(0) {  }
    Check operator ++ ()                             // ++obj
    {
        Check temp;
        temp.i = ++i;
        return temp;
    }

    // Notice int inside barcket which indicates postfix increment.  obj++;
    Check operator ++ (int)
    {
        Check temp;
        temp.i = i++;
        return temp;
    }
 
    void Display()
    { cout << "i = "<< i <<endl; }
};
```

**NOTE** - Following operators cannot be overloaded :
1. .(dot)   -->  Fundamentally possible, but will raise questions whether an operation is meant for the object overloading . or an object referred to by.
2. ::    --> its scope resolution, not expression evaluation.
3. ?:    --> never felt the need.
4. sizeof   --> will give fundamental error, as sizeof should represent address difference between two consecutive elements of array, not some user-defined value.

**NOTE** - Any constructor that can be called with a single argument works as a conversion constructor, means it can also be used for implicit conversion to the class being constructed.

---

[Link](https://www.geeksforgeeks.org/assignment-operator-overloading-in-c/)

**When should we write our own assignment operator?** \
Ans. When there is memory allocation at runtime.

---

[Link](https://www.geeksforgeeks.org/advanced-c-conversion-operators/)

### conversion operator ###

```c++
class Fraction
{
    int num, den;
public:
    Fraction(int n, int d) { num = n; den = d; }
    // conversion operator: return float value of fraction
    operator float() const {return float(num) / float(den);}
};

int main() {
    Fraction f(2, 5);
    float val = f;
    cout << val<<endl;
    cout<<f<<endl;    // f converted to float.
    return 0;
}
```

---

[Link](https://www.geeksforgeeks.org/default-assignment-operator-and-references/)

### Assignment Operator and Reference variables ###

Compiler doesn’t creates default assignment operator in following cases:
1. Class has a nonstatic data member of a const type or a reference type
2. Class has a nonstatic data member of a type which has an inaccessible copy assignment operator
3. Class is derived from a base class with an inaccessible copy assignment operator

```c++
class Test
{
	int x;
	int &ref;
public:
	Test (int i):x(i), ref(x) {}
};
int main()
{
	Test t1(10);
	Test t2(20);
	t2 = t1;                   // this line will give error, as default assignment operator is not made by compiler.
	return 0; 
}
```

---

[Link](https://www.geeksforgeeks.org/overloading-stream-insertion-operators-c/)

### Overloading stream insertion (<< or >>) operators in C++ ###

1. cout is an object of ostream class and cin is an object istream class
2. These operators must be overloaded as a global function. And if we want to allow them to access private data members of class, we must make them friend.

**Why these operators must be overloaded as global?** \
**Ans**. In operator overloading, if an operator is overloaded as member, then it must be a member of the object on left side of the operator. The operators ‘<<' and '>>' are called like 'cout << ob1' and 'cin >> ob1'. So if we want to make them a member method, then they must be made members of ostream and istream classes, which is not a good option most of the time. Therefore they are overloaded as global function.

```c++
class Complex
{
private:
	int real, imag;
public:
	Complex(int r = 0, int i =0){ real = r; imag = i; }
	friend ostream & operator << (ostream &out, const Complex &c);
	friend istream & operator >> (istream &in, Complex &c);
};

ostream & operator << (ostream &out, const Complex &c)   --->// Note that this definition is receiving two parameters as input, as its is declared friend(not member function). 
                                                         --->// But function calling is still the same
{
	out << c.real<<"+i" << c.imag << endl;
	return out;
}

istream & operator >> (istream &in, Complex &c)
{    
    in >> c.real >> c.imag;
    return in;
}
```

---

[Link](https://www.geeksforgeeks.org/overloading-subscript-or-array-index-operator-in-c/)

```c++
//sample codeblock from above link 
int& Array::operator[](int index)
{
    if (index >= size) {
        cout << "Array index out of bound, exiting";
        exit(0);
    }
    return ptr[index];
}
```
