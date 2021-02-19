C++ is middle level language, i.e. you can write normal code as well low level coding. \
Class is blueprint of object.

Steps in Software development, i.e. to make ***.exe*** file: \
 1). **.cpp** file will be converted to **.i** file with help of **preprocessor**,  **.i** file will contain all header files expanded. \
 2). **.i** file will be converted to **.obj** file with help of **compiler**, **.obj** file will be in operating system language. \
 3). **.obj** file will be converted to **.exe** file with help of **linker**, **linker** will provide definition of library files in **.obj** file so that OS can fully understand it.

Different Data type and their size or range -  [Link](https://docs.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-160) \
1). signed char or char  : size = 1 Byte , Range = -128 to 127 \
2). unsigned char : size = 1 Byte, Range = 0 to 255 \
3). short : size = 2 Byte  \
4). int : size = 4 Byte \
5). float : size = 4 Byte , upto 7 digits in decimal \
6). double or long double : size = 8 Byte, upto 15 digits in decimal \
7). long long : size = 8 Byte

**Note : Compiler by default treat them as signed if not mentioned.**
