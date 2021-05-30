---
C++ is middle level language, i.e. you can write normal code as well low level coding. \
Class is blueprint of object.

---

Steps in Software development, i.e. to make ***.exe*** file: \
 1. **.cpp** file will be converted to **.i** file with help of **preprocessor**,  **.i** file will contain all header files expanded. \
 2. **.i** file will be converted to **.obj** file with help of **compiler**, **.obj** file will be in operating system language. \
 3. **.obj** file will be converted to **.exe** file with help of **linker**, **linker** will provide definition of library files in **.obj** file so that OS can fully understand it.
 
---

Different Data type and their size or range -  [Link](https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-160) \
1. signed char or char  : size = 1 Byte , Range = -128 to 127 \
2. unsigned char : size = 1 Byte, Range = 0 to 255 \
3. short : size = 2 Byte  \
4. int : size = 4 Byte \
5. float : size = 4 Byte , upto 7 digits in decimal \
6. double or long double : size = 8 Byte, upto 15 digits in decimal \
7. long long : size = 8 Byte

**Note : Compiler by default treat them as signed if not mentioned.**

---

1). cout, cin is an object while printf(), scanf() is a function. Function is always accompanied with parenthesis. \
2). cout is accompanied by insertion operator <<. \
3). cin is accompanied by extraction operator >>. \
4). endl is manipulator which puts cursor in the next line. endl flush the output buffer everytime it is called. \
5). iostream.h contains declaration of cin, cout, >>, <<, endl.

**Note : Predefined function are declared in header file, but there coding is in library file.**

---

1. int &y = x; , Here y is reference variable to x. So whenever we will use y, x will be used automatically.  \
2. Reference variable is an internal pointer.  \
3. Reference variable should be intialized at the time declaration with help of already declared variable only. .i.e. int &y = 6; will be invalid statement. \
4. Reference variable once intialized cannot be updated. \
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

1. Function can be called by value, by reference , by address. And it can be identified by seeing functions declaration. \
2. inline is request to compiler not a command. Inline function is a function that is expanded in line when it is called. When the inline function is called whole code of the inline function gets inserted or substituted at the point of inline function call. This substitution is performed by the C++ compiler at **compile time**. Inline function may increase efficiency if it is small. See following link for more information on inline functions [Link](https://www.geeksforgeeks.org/inline-functions-cpp/) \
3. All functions inside class are implicitly inline, except virtual function. Because inlining is at compile time while virtual is at runtime. If a member function of is declared inside class but defined outside the class then it is not inline by default.

**Rules of resolving Function overloading -** \
1. Firstly, c++ tries to find the exact match. This is the case where actual arguments exactly matches the parameter type of one of the overloaded function. \
2. If no match is found then integral conversion is performed i.e char, unsigned char, short are converted to int and float is converted to double. \
3. If nothing works then standard conversion/ user defined conversion are tried. (i.e. int to long, int to unsigned long etc.)

---

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

Three difference between struct in c and c++ - \
1. In c++, no need for struct keyword whenever creating variable of that struct type. \
2. Encapsulation possible in c++, i.e. inside struct we can define functions. \
3. Access specifier in c++ (private, protected, public). By default everything is public in struct.

---

1. In class everything is private by default. \
2. Instance member function can access any instance member variable. \
See the code below, which runs perfectly fine - \
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
