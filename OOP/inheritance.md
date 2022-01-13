
### Inheritance properties in c++ ###
[Link](https://www.geeksforgeeks.org/g-fact-4/)

**Following are the things which a derived class inherits from its parent** -
1. Every data member defined in the parent class (although such members may not always be accessible in the derived class!)
2. Every ordinary member function of the parent class (although such members may not always be accessible in the derived class!)
3. The same initial data layout as the base class.

**Following are the things which a derived class does not inherits from its parent** - 
1. The base class’s constructors and destructor.
2. The base class’s friends

---
> **Note** - In multiple inheritance, constructors are called in the order they are inherited and reverse is true for destructors. | [Link](https://www.geeksforgeeks.org/multiple-inheritance-in-c/)
---

### Diamond Inheritance ###
[Link](https://www.geeksforgeeks.org/multiple-inheritance-in-c/)

---

Q. **What happens when more restrictive access is given to a derived class method in C++?** | [Link](https://www.geeksforgeeks.org/what-happens-when-more-restrictive-access-is-given-in-a-derived-class-method-in-c/)

Ans. C++ allows this. By this we can even access private method of derived class, which is public in parent class. Using concept of virtual functions.
```c++
class Base {
public:
    virtual int fun(int i) { cout << "Base::fun(int i) called"; }
};
 
class Derived: public Base {
private:
    int fun(int x)   { cout << "Derived::fun(int x) called"; }
};
 
int main()
{
    Base *ptr = new Derived;
    ptr->fun(10);
    return 0;
}
```
---

### Object Slicing ###
[Link](https://www.geeksforgeeks.org/object-slicing-in-c/)

1. In C++, a derived class object can be assigned to a base class object, but the other way is not possible.
2. We can avoid object slicing with the use of pointers or references. 
3. Object slicing doesn’t occur when pointers or references to objects are passed as function arguments since a pointer or reference of any type takes same amount of memory.

See this code below - 
```c++
class A{
    public:
    virtual void fun(){cout<<"nothing\n";}
};

class B: public A {
    public:
    virtual void fun(){cout<<"something\n";}
};

// object slicing, will call A::fun()
void temp1(A a){a.fun();}

// No object slicing and due to virtual function will call B::fun()
void temp2(A &a){a.fun();}
void temp3(A *a){a->fun();}
```

---

### Hiding of all overloaded methods with same name in base class ###
[Link](https://www.geeksforgeeks.org/g-fact-89/)

1. In C++, if a derived class redefines base class member method then all the base class methods with same name become hidden in derived class.
```c++
class A{
    public:
    void fun(){cout<<"nothing\n";}
    void fun(int i){cout<<"everything\n";}
};

class B: public A {
    public:
    void fun(int i, int j){cout<<"something\n";}
};

Both fun(), fun(int i) are hidden in B
```
2. This method hiding is true for all methods (static, non-static, virtual etc).
3. We can workaround this method hiding with the help of **using** keyword as follows-  
```c++
class A{
    public:
    void fun(){cout<<"nothing\n";}
    void fun(int i){cout<<"everything\n";}
};

class B: public A {
    public:
    using A::fun;                      ----> Now both fun(), fun(int i) are unhidden in B.
    void fun(int i, int j){cout<<"something\n";}
};
```

---

> **Note** - Friendship is not inherited although see this code, we are able to access private method of derived class through friend function using virtual functions. | [Link](https://www.geeksforgeeks.org/g-fact-34/)
```c++
class A{
    friend void frnd(A *a);
    virtual void display(){cout<<"everything\n";}
};

void frnd(A *a) {
    a->display();
}

class B: public A {
    void display(){cout<<"something\n";}
};

int main()
{
   B b;
   frnd(&b);
   return 0;
}
```
