
## To get the rightmost set bit  =   x&(-x);

---

## Gosper's Hack - To generate all the subsets of size k from set of n, i.e nCk
Idea is to find the rightmost bit that can be shifted to left, shift it and rightshift all the bits to its right completely.

```c++
set = (1<<k)- 1;   //  set = 0011001110
limit = (1<<n);  //  limit = 1000000000

while(set<limit)
{
   int c = set&(-set);  //c = 0000000010                       // get rightmost set bit
   int r = set + c;     //r = 0011010000                      // unset rightmost cluster of set bits and set next bit to 1  
   int x = r^set;       //x = 0000011110                     // To get back all the set bits + 1 extra bits created in previous step
   x = x/c;             //x = 0000001111                    // To bring all the set bits to the rightmost
   x = x>>2;            //x = 0000000011                   // To restore count of bits
   set = x|r;           //set = 0011001011                // Finally
}
```

---

## To check if the given string is made up of repeated chunks and find out smallest such chunk

For e.g - abababab - > is made of [ab, abab] as chunks and shortest chunk is ab
```c++
string temp = str + str;
int id = temp.find(str,1)  // check if str exist in temp[1..temp.length()-1]
if(id != str.length())
   smallest_chunk = str.substr(0,i); // str[0...i-1]
else
   no_chunk_found
```

---
