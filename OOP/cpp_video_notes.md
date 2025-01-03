---

### Lecture - 1 ###

C++ is middle level language, i.e. you can write normal code as well low level coding. \
Class is blueprint of object.

---

### Lecture - 1 contd. ###

Steps in Software development, i.e. to make ***.exe*** file:
 1. **.cpp** file will be converted to **.i** file with help of **preprocessor**,  **.i** file will contain all header files expanded.
 2. **.i** file will be converted to **.obj** file with help of **compiler**, **.obj** file will be in operating system language.
 3. **.obj** file will be converted to **.exe** file with help of **linker**, **linker** will provide definition of library files in **.obj** file so that OS can fully understand it.
 
---

Different Data type and their size or range -  [Link](https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-160)
1. signed char or char  : size = 1 Byte , Range = -128 to 127
2. unsigned char : size = 1 Byte, Range = 0 to 255
3. short : size = 2 Byte
4. int : size = 4 Byte
5. float : size = 4 Byte , upto 7 digits in decimal
6. double or long double : size = 8 Byte, upto 15 digits in decimal
7. long long : size = 8 Byte

**Note : Compiler by default treat them as signed if not mentioned.**

---

### Lecture - 3 ###

1. cout, cin is an object while printf(), scanf() is a function. Function is always accompanied with parenthesis.
2. cout is accompanied by insertion operator <<.
3. cin is accompanied by extraction operator >>.
4. endl is manipulator which puts cursor in the next line. endl flush the output buffer everytime it is called.
5. iostream.h contains declaration of cin, cout, >>, <<, endl.

**Note : Predefined function are declared in header file, but there coding is in library file.**

---

### Lecture - 4 ###

1. int &y = x; , Here y is reference variable to x. So whenever we will use y, x will be used automatically.
2. Reference variable is an internal pointer.
3. Reference variable should be intialized at the time declaration with help of already declared variable only. .i.e. int &y = 6; will be invalid statement.
4. Reference variable once intialized cannot be updated.
5. There is no difference in  `int*p and int *p`.


**Note: See following lines of code**
```c++
int x = 5;
int *p = &x;
int *t;
*t = x;   // t doesnt point to x, its dereferenced position will contain value equal to x. 
*t = *t + 1;
*p = 10;

cout<<*t<<endl;
cout<<*p<<endl;
cout<<x<<endl;

output will be = 6, 10, 10
```
---

### Lecture - 5 ###

1. Function can be called by value, by reference , by address. And it can be identified by seeing functions declaration.
2. inline is request to compiler not a command. Inline function is a function that is expanded in line when it is called. When the inline function is called whole code of the inline function gets inserted or substituted at the point of inline function call. This substitution is performed by the C++ compiler at **compile time**. Inline function may increase efficiency if it is small. See following link for more information on inline functions [Link](https://www.geeksforgeeks.org/inline-functions-cpp/)
3. All functions inside class are implicitly inline, except virtual function. Because inlining is at compile time while virtual is at runtime. If a member function of is declared inside class but defined outside the class then it is not inline by default.

**Rules of resolving Function overloading -**
1. Firstly, c++ tries to find the exact match. This is the case where actual arguments exactly matches the parameter type of one of the overloaded function.
2. If no match is found then integral conversion is performed i.e char, unsigned char, short are converted to int and float is converted to double.
3. If nothing works then standard conversion/ user defined conversion are tried. (i.e. int to long, int to unsigned long etc.)

---

### Lecture - 6 ###

```c++
struct temp
{ 
   int a,b;
};

int main()
{
 temp t1 = {1,2};   // Works fine
 temp t2 = {};   // works fine with t.a = 0, t.b = 0;
 temp t3;   // works fine with t.a, t.b are garbage values
 temp t4 = {1};  // works fine t.a = 1, t.b =0
 return 0;
}
```

Three difference between struct in c and c++ -
1. In c++, no need for struct keyword whenever creating variable of that struct type.
2. Encapsulation possible in c++, i.e. inside struct we can define functions.
3. Access specifier in c++ (private, protected, public). By default everything is public in struct.

---

### Lecture - 7 ###

1. In class everything is private by default.
2. Instance member function can access any instance member variable.
See the code below, which runs perfectly fine -
```c++
class temp
{ 
   private:
   int a,b;
   public:
   void set_data(int x,int y)
   {a=x,b=y;}
   void display()
   {cout<<a<<" "<<b<<endl;}
   
   temp add(temp &c)
   {
	   temp t;
	   c.a = c.a - 1;   // We can change value of argument object also. 
	   t.a = a + c.a;
	   t.b = a + c.b;
	   return t;
   }
};
```

---

## Lecture - 14 ###

#### Constructor in inheritance - ####
1. If we dont call the constructor parent class in our derived class constructor, then compiler will automatically add code for calling zero-arg default constructor of parent class.
2. Call to constructor order -> Child to Parent.
3. Execution of constructor order - > Parent to Child.

#### Destructor in inheritance - ####
1. We cant call the destructor of parent class, from destructor of child class. Compiler will automatically add code for that. And also destructors doesnt recieve any arguments so it wont be an issue.
2. Call to Destructor order - > Child to Parent.
3. Execution of Destructor order - > Child to Parent.

---

## Lecture - 15 ##

1. **this** is a keyword.
2. **this** is a local object pointer in every instance member function containing address of the caller object.
3. **this** pointer can not be modified.

---

## Lecture - 16 ##

1. int * p = new int;  // here lhs(p) has static memory allocation, while rhs has dynamic memory allocation. 
2. new will return address of the created memory block.

1. delete p; // delete wont delete p, but it will delete the memory block pointed by p.
2. delete only works for dynamically created memory block.

---

## Lecture - 17 ##

```c++
class A{
  public:
  int a;
  void f1(){cout<<"f1 of A\n";}
  void f2(){cout<<"f2 of A\n";}
};

class B: public A{
  public:
  int a;         // Member hiding, a of A wont be available for member functions of B. If member of function of A are called from object of B then a of A will be used.
  void f1(){cout<<"f1 of B\n";}  // Method overloading
  void f2(int x){cout<<"f2 of B\n";}   // Method hiding, as f2() wont be available for object of B.
};
```

---

## Lecture - 18 ##

1. Base class pointer can point to object of any of its descendant class (even if that class has mutliple parents). But converse is not true.

## Lecture - 19 ##

**Note** - In method hiding, method does exist in that class, but compiler doesnt bother to look for that, as it finds already defined version of it in that class.

1. In C++, once a member function is declared as a virtual function in a base class, it becomes virtual in every class derived from that base class.
2. Any class which contains a virtual function, compiler will declare an **instance** member named **vptr**.
3. **vptr** will point to a **static** array **vtable** containing address of the virtual functions.
4. How compiler resolves Late Binding -
    * Late Binding happens in the case of Virtual Functions.
    * So compiler will firstly check that caller object( not where the caller object is pointing) has that function as virtual or not.
    * If that's virtual then late binding will happen.
    * In late binding, compiler will go to the vptr of the object where its pointing and then to the vtable, and then make appropriate call.

See this code for getting idea of how whether the called function is virtual or not is decided - 
```c++
class A{
    public:
    void fun(){cout<<"A's fun called\n";}
};

class B : public A{
    public:
    virtual void fun(){cout<<"B's fun called\n";}
};

int main()
{
   A *a;
   B b;
   a = &b;
   a->fun();   // will call fun of A, as fun is non-virtual in A.
   
   return 0;
}
```

**Note** - We can also call private function of derived class from a base class pointer by declaring that function in the base class as virtual. Because access specifier are checked at the compile time and virtual functions are resolved at runtime. [Link](https://www.codesdope.com/cpp-virtual-and-abstract/)

**Note** - If a virtual function in base class is made hidden in child class, then that new definition will not be virtual.

**How to make vtable** - 
1. Go through all the functions in that class (whether they are hidden, overriden, private, public or anything) and put address of all virtual functions in vtable and map them.(in case of overriden it will map to latest definition, in hidden it will map to old definition(hidden one).)

**Note** - Consider following code - 
```c++
lass A{
    protected:
    virtual void fun(){cout<<"A's fun called\n";}
};

class B : public A{
    public:
    void fun(){cout<<"B's fun called\n";}
};

int main()
{
   A *a;
   B b;
   a = &b;
   a->fun();               ------------> This will give error that fun is private in A
   return 0;
}
```
[Link to stackoverflow answer for above scenario](https://stackoverflow.com/a/3786209/14137254)
```
Explaination for above error - 
If name lookup determines a viable function to be a virtual function, the access specifier of the virtual function is checked in the scope of the static type of the object expression used to name the function.
At run time, the actual function to be called could be defined in the derived class with a completely different access specifier. This is because 'access specifiers' are a compile time phenomonon.
```
see this code from video - 
```c++
class A{
    public:
    void f1(){cout<<"A::f1\n";}
    virtual void f2(){cout<<"A::f2\n";}
    virtual void f3(){cout<<"A::f3\n";}
    virtual void f4(){cout<<"A::f4\n";}
};

class B : public A{
    public:
    void f1(){cout<<"B::f1\n";}
    virtual void f2(){cout<<"B::f2\n";}
    virtual void f3(int x){cout<<"B::f3\n";}
};

void testA(){
    A a;
    A *ptr;
    ptr = &a;
    ptr->f1();   // Early binding, will call A::f1();
    ptr->f2();   // Late binding, will call A::f2();
    ptr->f3();   // Late binding will call A::f3();
    ptr->f4();   // Late binding will call A::f4();
    ptr->f3(5);   // Error, no such function in A;
    
    //vtable - A::f2, A::f3, A::f4
}

void testB(){
    B b;
    A *ptr;
    ptr = &b;
    
    ptr->f1();   // Early binding, will call A::f1();
    ptr->f2();   // Late binding, will call B::f2();
    ptr->f3();   // Late binding will call A::f3();, as no f3() in B
    ptr->f4();   // Late binding will call A::f4(), because no f4 in B;
    ptr->f3(5);   // Error, will look into A class couldnt find any such function
    
    B *bptr;
    bptr = &b;
    bptr->f3(5);  // will work fine.
    
    // vtable - B::f2(), A::f3(), B::f3(int), A::f4()
    
}

int main()
{
   testA();
   testB();
   return 0;
}
```



