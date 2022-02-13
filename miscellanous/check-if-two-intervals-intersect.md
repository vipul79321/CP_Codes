
### Standard Implementation
```c++
bool intersect(pair<ll,ll>&a, pair<ll,ll>&b)
{
    if(a.first <= b.second && a.second >= b.first)return 1;
    if(b.first <= a.second && b.second >= a.first)return 1;
    return 0;
}
```

---
    
### Better Implementation
```c++
bool intersect(pair<ll,ll>&a, pair<ll,ll>&b)
{
    if(max(a.first,b.first) <= min(a.second,b.second)) return 1;
    return 0;
}
```

