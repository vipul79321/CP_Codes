### Virtual Functions
[Link](https://www.learncpp.com/cpp-tutorial/virtual-functions/)

**Virtual functions and polymorphism**
* A virtual function is a special type of function that, when called, resolves to the `most-derived version` of the function that exists between the base and derived class. 
* This capability is known as polymorphism. 
* A derived function is considered a match if it has the `same signature (name, parameter types, and whether it is const) and return type as the base version of the function`. Such functions are called **overrides**.

>**NOTE** - If a function is marked as virtual, all matching overrides are also considered virtual, even if they are not explicitly marked as such.
> **NOTE** - If we call a virtual function in constructor of base class, it wont resolve to any existing virtual function in derived class, as derived part of the object has not formed yet.

**Covariant Return Types** | [Link](https://www.learncpp.com/cpp-tutorial/the-override-and-final-specifiers-and-covariant-return-types/)
* It is an execption, where virtual function overrides can have different return types. Strictly speaking, If the return type of a virtual function is a pointer or a reference to a base class, override functions can return a pointer or a reference to a derived class.

```c++
#include <iostream>
#include <string_view>

class Base
{
public:
	// This version of getThis() returns a pointer to a Base class
	virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
	void printType() { std::cout << "returned a Base\n"; }
};

class Derived : public Base
{
public:
	// Normally override functions have to return objects of the same type as the base function
	// However, because Derived is derived from Base, it's okay to return Derived* instead of Base*
	Derived* getThis() override { std::cout << "called Derived::getThis()\n";  return this; }
	void printType() { std::cout << "returned a Derived\n"; }
};

int main()
{
	Derived d{};
	Base* b{ &d };
	d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
	b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType

	return 0;
}
```
>**NOTE** - C++ can’t dynamically select types, so you’ll always get the type that matches the actual version of the function being called
>* In the above example, we first call d.getThis(). Since d is a Derived, this calls Derived::getThis(), which returns a Derived*. This Derived* is then used to call non-virtual function Derived::printType().
>* Now the interesting case. We then call b->getThis(). Variable b is a Base pointer to a Derived object. Base::getThis() is a virtual function, so this calls Derived::getThis(). Although Derived::getThis() returns a Derived*, because Base version of the function returns a Base*, the returned Derived* is upcast to a Base*. Because Base::printType() is non-virtual, Base::printType() is called.
>* In other words, in the above example, you only get a Derived* if you call getThis() with an object that is typed as a Derived object in the first place.
>* Note that if printType() were virtual instead of non-virtual, the result of b->getThis() (an object of type Base*) would have undergone virtual function resolution, and Derived::printType() would have been called.

---

### Virtual functions and Default Arguments ###
[Link](https://www.geeksforgeeks.org/output-of-c-program-set-12-2/)

Consider following code - 
```c++
class Base
{
public:
	virtual void fun ( int x = 10 ){cout << "Base::fun(), x = " << x << endl;}
};

class Derived : public Base
{
public:
	virtual void fun ( int x ){cout << "Derived::fun(), x = " << x << endl;}
};

int main()
{
	Derived d1;
	Base *bp = &d1;
	bp->fun();
	return 0;
}

Output will be Derived::fun(), x = 10   <------------------------- Default value of x is substituted at compile time.
```

**Explaination for above output** -
* Default arguments do not participate in signature of functions. 
* So signatures of fun() in base class and derived class are considered same, hence the fun() of base class is overridden. 
* **Also, the default value is used at compile time.** 
* When compiler sees that an argument is missing in a function call, it substitutes the default value given. 
* Therefore, in the above program, value of x is substituted at compile time, and at run time derived class’s fun() is called.

---

[Link](https://www.geeksforgeeks.org/g-fact-36/)

### Virtual functions in derived classes ###
1. In C++, once a member function is declared as a virtual function in a base class, it becomes virtual in every class derived from that base class. 
2. In other words, it is not necessary to use the keyword virtual in the derived class while declaring redefined versions of the virtual base class function.
3. **Given that the function signature remains same in derived class **

```c++
class A {
public:
	virtual void fun(){ cout<<"\n A::fun() called ";}
};

class B: public A {
public:
	void fun(int x){ cout<<"\n B::fun() called "; }	   -----------> non - virtual and virtual method was hidden due to this.
};

class C: public B {
public:
	void fun(int x){ cout<<"\n C::fun() called "; }	 -------------> non-virtual
};

int main()
{
C c; // An object of class C
B *b = &c; // A pointer of type B* pointing to c
b->fun(); // this line prints "B::fun() called"  as it is not virtual because function signature was changed in derived class.
getchar();
return 0;
}
```

---

[Link](https://www.geeksforgeeks.org/virtual-destructor/)

### Virtual Destructor ###
```c++
class base {
public:
	base(){ cout<<"Constructing base \n"; }
	~base(){ cout<<"Destructing base \n"; }	
};

class derived: public base {
public:
	derived(){ cout<<"Constructing derived \n"; }
	~derived(){ cout<<"Destructing derived \n"; }
};

int main(void)
{
    derived *d = new derived();
    base *b = d;
    delete b;
    getchar();
return 0;
}

Ouput will be - 
Constructing base 
Constructing derived 
Destructing base 
```

To avoid this undefined behavior, making destructor virtual is considered a good practice.
**Once a base class destructor becomes virtual, destructor of all the class inheriting it also becomes virtual**

---

[Link](https://www.geeksforgeeks.org/advanced-c-virtual-constructor/)

**Constructors cant be virtual, even constructor can only be inline and nothing else.**

**Also, Do Read the blog really good article.**

---

[Link](https://www.geeksforgeeks.org/advanced-c-virtual-copy-constructor/)

**Copy Constructors cant be virtual, even constructor can only be inline and nothing else.**

**Also, Do Read the blog really good article.**

---

[Link](https://www.geeksforgeeks.org/inline-virtual-function/)

By default, virtual functions are not inlined, as they are generally resolved at runtime.
Whenever virtual function is called using base class reference or pointer it cannot be inlined (because call is resolved at runtime), 
but whenever called using the object (without reference or pointer) of that class, can be inlined because compiler knows the exact class of the object at compile time.

---

[Link](https://www.geeksforgeeks.org/pure-virtual-functions-and-abstract-classes/)

### Pure virtual function and Abstract class ###

```c++
// An abstract class with constructor
class Base
{
protected:
int x;
public:
virtual void fun() = 0;     //---> pure virtual function
virtual void fun(int t){ cout<<"something\n";}  // Normal function, no need to be defined in derived class.
Base(int i) {x = i;cout<<"Constructor of base called\n";}
};

void Base::fun() {cout<<"everything\n";} // Pure Virtual functions can be defined too.
 
class Derived: public Base
{
	int y;
public:
	Derived(int i, int j):Base(i) { y = j; }
	void fun() { cout << "x = " << x << ", y = " << y<<'\n'; Base::fun();}--> pure virtual function, overriden otherwise will become an abstract class, also we are calling pure virtual function.
};

int main(void)
{
	Derived d(4, 5);
	d.fun();

    //object creation using pointer of base class
	Base *ptr=new Derived(6,7);
	ptr->fun();
  ptr->fun(5); //  fun(int) of Base will be executed.
	return 0;
}
```

Important points about pure virtual function and abstract classes- 
1. Any class containing pure virtual function is abstract class.
2. We cant create object of abstract class.
3. Although we can create pointer or references of abstract class.
4. If we do not override the pure virtual function in derived class, then derived class also becomes abstract class. 
5. An abstract class can have constructor, as seen in above code.

**Note** - [See this stackoverflow answer link](https://stackoverflow.com/a/2089176/14137254). It shows why can Pure virtual functions can have definition.

---

[Link](https://www.geeksforgeeks.org/pure-virtual-destructor-c/)

### Pure Virtual Destructor ###

1. Yes, destructor can be pure virtual. Such class becomes abstract class.
2. Pure virtual destructor needs to have a function body outside that class. 
3. Reason for point 2 - 
    * The reason is because destructors (unlike other functions) are not actually ‘overridden’, rather they are always called in the reverse order of the class derivation. 
    * This means that a derived class’ destructor will be invoked first, then base class destructor will be called. 
    * If the definition of the pure virtual destructor is not provided, then what function body will be called during object destruction? 
    * Therefore the compiler and linker enforce the existence of a function body for pure virtual destructors.

see this code - 
```c++
#include <iostream>
class Base
{
public:
	virtual ~Base()=0; // Pure virtual destructor
};
Base::~Base()                 // -----> neccessary to provide definition outside class, otherwise compiler will give error.
{
	std::cout << "Pure virtual destructor is called";
}

class Derived : public Base
{
public:
	~Derived()
	{
		std::cout << "~Derived() is executed\n";
	}
};

int main()
{
	Base *b = new Derived();
	delete b;
	return 0;
}
```

---

### RTTI (Run-time type Information) in C++ ###
[Link](https://www.learncpp.com/cpp-tutorial/dynamic-casting/) | [Link](https://www.geeksforgeeks.org/g-fact-33/)

In C++, RTTI (Run-time type information) is a mechanism that exposes information about an object’s data type at runtime and is available only for the classes which have at least one virtual function. 
It allows the type of an object to be determined during program execution

See this code - 
```c++
// CPP program to illustrate
// Run Time Type Identification
#include<iostream>
using namespace std;
class B { virtual void fun() {} };
class D: public B { };

int main()
{
	B *b = new D;
	D *d = dynamic_cast<D*>(b);   // -> wont work if B doesnt contain a virtual table.
	if(d != NULL)
		cout << "works";
	else
		cout << "cannot cast B* to D*";
	getchar();
	return 0;
}

```

See this code too - 

```c++
#include <iostream>
#include <string>

class Base
{
protected:
	int m_value{};

public:
	Base(int value)
		: m_value{value}
	{
	}

	virtual ~Base() = default;
};

class Derived : public Base
{
protected:
	std::string m_name{};

public:
	Derived(int value, const std::string& name)
		: Base{value}, m_name{name}
	{
	}

	const std::string& getName() const { return m_name; }
};

Base* getObject(bool returnDerived)
{
	if (returnDerived)
		return new Derived{1, "Apple"};
	else
		return new Base{2};
}

int main()
{
	Base* b{ getObject(true) };

	// how do we print the Derived object's name here, having only a Base pointer? Since getName() functionality doesnt exist in Base class
	Derived* d{ dynamic_cast<Derived*>(b) }; // use dynamic cast to convert Base pointer into Derived pointer

        if(d) // making sure dynamic cast didnt failed.
	std::cout << "The name of the Derived is: " << d->getName() << '\n';

	delete b;

	return 0;
}
```
