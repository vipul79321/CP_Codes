[Link](https://www.geeksforgeeks.org/constructors-c/)
### Constructors ###
1. A constructor is a member function of a class which initializes objects of a class.
```c++
ClassName(){};
```
2. Constructor has same name as the class itself
3. Constructors don’t have return type
4. A constructor is automatically called when an object is created.
5. Types of constructors - Default Constructor, Parameterized Constructor, Copy Constructor.

**Note** - We can have more than one constructor for class (Constructor Overloading)

---

[Link](https://www.geeksforgeeks.org/copy-constructor-in-cpp/)  See article too.

### Copy Constructor ###
A copy constructor is a member function that initializes an object using another object of the same class.
```c++
ClassName(const ClassName &obj){}    // Syntax for copy constructor.
```
When a copy constructor is called - 
1. When an object of the class is returned by value.
2. When an object of the class is passed (to a function) by value as an argument. 
3. When an object is constructed based on another object of the same class. 
4. When the compiler generates a temporary object.

**Note** - It is, however, not guaranteed that a copy constructor will be called in all these cases, because the C++ Standard allows the compiler to optimize the copy away in certain cases

**When we need to write our own copy constructor**
Ans. When we want to achieve **Deep Copy**. Because compiler made copy constructor will only make **shallow copy**.  [Article Link](https://www.geeksforgeeks.org/g-fact-22/) .

**Note** - Copy constructor is called when a new object is created from an existing object, as a copy of the existing object. Assignment operator is called when an already initialized object is assigned a new value from another existing object.
See this 
 ```c++
MyClass t1, t2;
MyClass t3 = t1;  // Copy constructor called.
t2 = t1;         // Assignment operator called.
 ```
 
 **Can we make copy constructor private?**
 Ans. Yes when we dont object of our class to be copied.
 
 **Why argument to a copy constructor must be passed as a reference?**
 Ans. Because when we call by value, Copy constructor is called. And hence there will be infinite loop.
 
 **Why argument to a copy constructor should be const?** [Link to article](https://www.geeksforgeeks.org/copy-constructor-argument-const/)
 Ans. Not neccessary but it is a good practice. And also see the code below - 
 ```c++
Test fun()
{Test t; return t;}
  
int main()
{
    Test t2 = fun();   // this line will give an error. See explaination below.
    return 0;
}
 ```
 
 Explanation for above error - 
 1. The compiler creates a temporary object which is copied to t2 using copy constructor in the program.
 2. The temporary object is passed as an argument to copy constructor.
 3. The reason for compiler error is, compiler created temporary objects cannot be bound to non-const references and the original program tries to do that. 
 4. It doesn’t make sense to modify compiler created temporary objects as they can die any moment.

---

[Link](https://www.geeksforgeeks.org/destructors-c/)

### Destructor ###
Destructor is a member function which destructs or deletes an object.
```c++
~ClassName(){}
```

Properties of Destructors - 
1. Destructor function is automatically invoked when the objects are destroyed.
2. It cannot be declared static or const. (static function can be called without object. And const function cant modify object).
3. The destructor does not have arguments and return type. (cant be overloaded)
4. An object of a class with a Destructor cannot become a member of the union.
5. A destructor should be declared in the public section of the class.
6. The programmer cannot access the address of destructor.
7. Destructor can be virtual (even its a good practice to declare it virtual).

**Note** - The const member functions are the functions which are declared as constant in the program. The object called by these functions cannot be modified. It is recommended to use const keyword so that accidental changes to object are avoided. A const member function can be called by any type of object.(const or non-const).

**When is destructor called?**
1. the function ends 
2. the program ends 
3. a block containing local variables ends 
4. a delete operator is called 

**When do we need to write a user-defined destructor?**
* The default destructor works fine unless we have dynamically allocated memory or pointer in class. 
* When a class contains a pointer to memory allocated in class, we should write a destructor to release memory before the class instance is destroyed. 
* This must be done to avoid memory leak.

---

[Link](https://www.geeksforgeeks.org/g-fact-93/) 

### Use explicit Keyword ###
1. When a class contains default constructor, then there maybe chance of implicit typecasting of **single parameter** (wont work with multiple parameter implicit typecasting). See this code - 
```c++
class A {
    public:
    int a,b;
    A(int x=0, int y=0) {
        a = x; b = y;
    }
    
    bool operator == (A x) {
        return(a == x.a && b == x.b);
    }
};
int main()
{
	A a(3,0);

	if (a == 3)   // Condition will be true, because 3 will be type casted to A(3,0) and hence equal to a;
	cout << "Same";
 if (a == (3,0))  // condition will be false (3,0) will be implicitly typecasted to A(0,0) and hence not equal to a;
 if (a == (0,3))  // Condition will be true, because (0,3) will be type casted to A(3,0) and hence equal to a;
 
	return 0;
}
```
2. To avoid such typecasting we can use **explicit** keyword with constructor. 

---

[Link](https://www.geeksforgeeks.org/c-internals-default-constructors-set-1/)

### Inside Default constructor during inheritance ###
1. A constructor without any arguments or with default value for every argument, is said to be default constructor.
2. In inherited class, if no call provided then compiler will try to call Default Constructor of base class. See this code - 
```c++
class A {
public:
	// User defined constructor
	A()
	{
		cout << "A Constructor" << endl;
	}
	// uninitialized
	int size;
};

class B : public A {
	// compiler defines default constructor of B, and inserts stub to call A constructor

	// compiler won't initialize any data of A
};

class C : public A {
public:
	C()
	{
		// User defined default constructor of C Compiler inserts stub to call A's construtor
		cout << "C Constructor" << endl;

		// compiler won't initialize any data of A
	}
};

class D {
public:
	D()
	{
		// User defined default constructor of D, a - constructor to be called, compiler inserts stub to call A constructor
		cout << "D Constructor" << endl;

		// compiler won't initialize any data of 'a'
	}

private:
	A a;   // A is declared here. 
};

int main()
{
	B b;	 // output - > A Constructor
	C c;  // output - > A Constructor C Constructor
	D d;  // output - > A Constructor D Constructor
	return 0;
}
```

---

[Link](https://www.geeksforgeeks.org/private-destructor/)

### Private Destructor ###
1. A destructor can be private. 
2. When a Destructor is private only dynamically created object of that class can be made.
3. For deleting dynamic created object of that class, we can make friend function like this - 
```c++
void destructTest(Test* ptr)
{
    delete ptr;   // desctructor will be called.
}
```

---

[Link](https://www.geeksforgeeks.org/playing-with-destructors-in-c/)

```c++
int i;
class A
{
public:
    ~A(){i=10;}
};
  
int foo()
{
    i=3;
    A ob;
    return i;
}
// output of foo() will be 3, because destructor will be called as the last function. So before that return value(3) will already be copied.
```

---

[Link](https://www.geeksforgeeks.org/copy-elision-in-c/)

1. Copy elision (or Copy omission) is a compiler optimization technique that avoids unnecessary copying of objects.
See this code - 
```c++
class B
{
public:	
	B(int x = 0){cout << "Constructor called" << endl;}	
	
	B(const B &b){cout << "Copy constructor called" <<endl;}
};

int main()
{
	B ob = 1;   // constructor called output
	return 0;
}

Normally:
B ob = 1 is equivalent to - B ob = B(1);
But in copy elison it is  - B ob(1);
```

---

[Link](https://www.geeksforgeeks.org/does-compiler-always-create-a-copy-constructor/)

**What happens when we write only a copy constructor – does compiler create default constructor?**
Ans. Compiler doesn’t create a default constructor if we write any constructor even if it is copy constructor.

**What about reverse – what happens when we write a normal constructor and don’t write a copy constructor?**
Ans. Reverse is not true.

---

[Link](https://www.geeksforgeeks.org/static-objects-destroyed/)

### Static Objects ###
1. Static objects are allocated storage in static storage area.
2. Static object is destroyed at the termination of program. 
3. C++ supports both local static object and global static object.

**Note** - To sum up once declared static objects live till the end of the program. But there scope can be restricted.

---

[Link](https://www.geeksforgeeks.org/possible-call-constructor-destructor-explicitly/)
**Is it possible to call constructor and destructor explicitly?**
Ans. Yes
See this code - 
```c++
class Test
{
public:
    int x;
	Test(int x) { this->x = x;cout << "Constructor is executed\n";}
	~Test() { cout<<this->x<<" ";cout << "Destructor is executed\n"; }
};

int main()
{
	Test(3);    // c++ temporary object will be deleted immediately. // constructor called explicitly.
	Test t(4);
	t.~Test();  // Destructor called explicitly.  // Destructor will be called again, because it is automatic object and c++ will also try to delete it.
	return 0;
}

Output will be -
Constructor is executed
3 Destructor is executed
Constructor is executed
4 Destructor is executed
4 Destructor is executed
```
**Note** - Once a destructor is invoked for an object, the object no longer exists; the behavior is undefined if the destructor is invoked for an object whose lifetime has ended 
**Note** - we should never call destructor explicitly on local (automatic) object, because really bad results can be acquired by doing that.
**Note** - For deleting dynamically created object use delete operator.
**Note** -  delete p does two things: it calls the destructor and it deallocates the memory.
