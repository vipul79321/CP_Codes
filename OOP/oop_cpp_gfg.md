[Link1](https://www.geeksforgeeks.org/oops-object-oriented-design/) & [Link2](https://www.geeksforgeeks.org/object-oriented-programming-in-cpp/)

Characterisitcs of OOP:
1. **Class** - Building block of OOP. It is a user-defined data type, which holds its own **data members and member functions**, which can be accessed and used by creating an instance of that class.
2. **Object** - Object is an instance of a class.
3. **Inheritance** - It is the ability of one class to inherit capabilities or properties of another class (parent class).
4. **Abstraction** - Abstraction means displaying only essential information and hiding the details. Can be done using class or header files.
5. **Encapsulation** - Encapsulation is defined as binding together the data and the functions that manipulate them.
6. **Polymorphism** - Polymorphism is the ability of data to be processed in more than one form. Compile time(Operator overloading, Function Overloading) & Runtime(Virtual Functions)

Advantages of OOP:
1. Models real world very well.
2. Code Reusability.
3. Easy to understand & maintain.

Disadvantages of OOP:
1. Classes tends to be over-generalized sometimes.
2. Relation between classes become superficial sometimes.
3. Requires proper planning & skills.

---

[Link](https://www.geeksforgeeks.org/c-classes-and-objects/)

1. Everything is **Private** in c++ class, by default.
2. All functions defined inside class are implicitly **inline, except virtual function**. Because inlining is at compile time while virtual is at runtime. If a member function is declared inside class but defined outside the class then it is not inline by default.
3. Friend function **defined** inside class is also inline.
4. In class, all member fucntions and data members are **declared** inside class. But can be **defined** outside class.

---

[Link](https://www.geeksforgeeks.org/access-modifiers-in-c/)

1. **Public** - The data members and member functions declared as public can be accessed by other classes and functions too. 
2. **Private** - The data members and member function declared as private can only be accessed by member function & friend functions of that class or by friend class.
3. **Protected** - The data members and member function declared as protected can only be accessed by member function & friend function of that class or by friend class or derived class of that class.

**Note** - In protected, the access through inheritance can alter the access modifier of the elements of base class in derived class depending on the modes of Inheritance.

---

[Link](https://www.geeksforgeeks.org/inheritance-in-c/)

**Note**: A derived class doesn’t inherit access to private data members. However, it does inherit a full parent object, which contains any private members which that class declares.

Different modes of inheritance in c++ - 
1. **Public** - Public members of base class -> Public in derived class. Protected member of base class -> Protected in derived class.
2. **Protected** - Public members of base class -> Protected in derived class. Protected member of base class -> Protected in derived class.
3. **Private** - Public members of base class -> Private in derived class. Protected member of base class -> Private in derived class.

Different types of inheritance in c++ - 
1. Single inheritance
2. Multiple inheritance
3. Heirarchical inheritance
4. Multilevel inheritance
5. Diamond inheritance (Multi-path inheritance) - E.g. - A -> B; A -> C; B,C -> D; To avoid amibguity to access A in D, use virtual inheritance A (virtual -> ) B, A (virtual ->) C 
6. Hybrid inheritance - More than one type of above mentioned inheritances

---

[Link](https://www.geeksforgeeks.org/structure-vs-class-in-cpp/)

### Difference between struct and class in c++ ###
1. In struct, members are by default public. While in class, members are by default private.
2. In struct, default inheritance mode is public. While in class, default inheritance mode is private.
3. Memory of structure is allocated in the stack while the memory of class is allocated in heap.

---

[Link](https://www.geeksforgeeks.org/can-a-c-class-have-an-object-of-self-type/)

### Can a C++ class have an object of self type? ###
A class declaration can contain static object of self type, it can also have pointer to self type, but it cannot have a non-static object of self type.

Following declaration will work fine - 
```c++
class Test {
  static Test something;  // works fine
  
  /* other stuff in class*/ 
  
};
```

```c++
class Test {
  Test * something; //works fine
  
  /* other stuff in class*/ 
  
};
```

But this will give error - 
```c++
class Test {
  Test something; // Error - Incomplete definition error.
  
  /* other stuff in class*/ 
  
};
```

---

[Link](https://www.geeksforgeeks.org/why-is-the-size-of-an-empty-class-not-zero-in-c/)

1. Size of empty class or struct in c++ is 1 to ensure that each instance of that struct/class will have different address.
2. an empty base class need not be represented by a separate byte in derived class. See this code for e.g - 
```c++
class Empty { };  --> sizeof(Empty) will be 1.
class Derived: Empty { int a; }; -- > sizeof(Derived) will be 4.
```

3. [Link1](https://stackoverflow.com/questions/6497141/how-to-determine-the-size-of-virtual-base-class-and-derived-classes-from-it) For more confusion.
4. In virtual inheritance there is an extra overhead of 4 Bytes / 8 Bytes depending on architecture(32-bit or 64-bit) [See this](https://www.cprogramming.com/tutorial/size_of_class_object.html)
5. See following code & comments - 

```c++
class Empty {};  --> sizeof(Empty) = 1;
 
class Derived1 : public Empty {}; -->sizeof(Derived1) = 1;
 
class Derived2 : virtual public Empty {};  -->sizeof(Derived2) = 8, because it contains VPTR of virtual inheritance.
 
class Derived3 : public Empty {  --> sizeof(Derived3) = 1;
    char c;
};
 
class Derived4 : virtual public Empty { --> sizeof(Derived4) = 16, because it contains VPTR (8 Bytes) + char(1 Bytes) + 7 (padding Bytes)
    char c;
};
 
class Dummy {  -->sizeof(Dummy) = 1;
    char c;
};

```

---

### Static data members in c++ Class ###
[Link](https://www.geeksforgeeks.org/static-data-members-c/)
1. Only one copy of that member is created for the entire class and is shared by all the objects of that class , no matter how many objects are created.
2. Static members are only declared in class declaration, not defined. They must be explicitly defined outside the class using scope resolution operator.
3. It is visible only within the class,but its lifetime is the entire program.

---

### Static member function in c++ Class ###
[Link](https://www.geeksforgeeks.org/some-interesting-facts-about-static-member-functions-in-c/)
1. Static member functions do not have this pointer. As then can be called without object.
2. A static member function cannot be virtual, const, volatile.
3. Static member function can be defined inside the class.
4. A static member function can only access static data member, other static member functions and any other functions from outside the class.
5. Member function declarations with the same name and the name parameter-type-list cannot be overloaded if any of them is a static member function declaration.
```c++
class Test {
   static void fun() {}
   void fun() {} // compiler error
};
```
```c++
class Test {
   static void fun() {}
   void fun() {int x} // will work fine
};
```




