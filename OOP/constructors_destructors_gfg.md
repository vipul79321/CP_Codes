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

