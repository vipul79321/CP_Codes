### Class Templates
[Link](https://www.learncpp.com/cpp-tutorial/template-classes/) | [Link](https://www.learncpp.com/cpp-tutorial/template-non-type-parameters/) | [Link](https://www.learncpp.com/cpp-tutorial/function-template-specialization/)

* See code below for class-template examples
* Also, see function-template specialization, class-template specialization

```c++
#include <bits/stdc++.h>
using namespace std;

template<typename T>

class BaseType {
    public:
      T x;
    
    BaseType(T x) {
        this->x = x;
    }
    
    void print() {
        cout<<x<<"\n";
    }
    
    void definedOutside();
};

// A function defined outside template class.
// Each function defined outside needs its own template declaration
template<typename T>
void BaseType<T>::definedOutside() {
    cout<<"definedOutside\n";
}

// function template specialization for a int* type
template<>
void BaseType<int*>::print() {
    cout<<*x<<"\n";
}

// class template specialization for char*
// class template specialization can have altogether different definition
template<>
class BaseType<char*> {
    
    public:
      char *x;
     
    BaseType(char* c) {
        x = c;
    }
    
    void print() {
        cout<<"This is specially defined "<<*x<<" \n";
    }
    
    // note we have left out definedOutside function. 
};

int main()
{
    BaseType<int>a(4);
    a.print();  // 4
    a.definedOutside();  // definedOutside
    
    int x = 5;
    BaseType<int*>b(&x);
    b.print();  // 5
    b.definedOutside();  // definedOutside;
    
    char ch = 'A';
    BaseType<char*>c(&ch);
    c.print();  // This is specially defined A
    //c.definedOutside(); -> will give error, as we have left out definedOutside in class-template specialization for char*
    
    return 0;
}
```

---

* See code below for working non-type parameters
```c++
#include <bits/stdc++.h>
using namespace std;

template<typename T, int size>
class BaseType {
    public:
      T x;
      int sz;
    
    BaseType(int x) {
        this->x = x;
        sz = size;
    }
    
    void print() {
        cout<<x<<" "<<sz<<endl;
    }
};

int main()
{
    BaseType<int,5>a(4);
    a.print(); // 4 5
    
    // Below lines will give an error because non-type parameter should be constexpr
    // int sz = 5;
    // BaseType<int,sz>b(3);
    
    constexpr int sz = 5;
    BaseType<int,sz>b(3);
    b.print(); // 3 5
    
    return 0;
}
```

---
