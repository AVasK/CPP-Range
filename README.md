# C++ ranges
## That cool range syntax from Python now in C++
### requires C++11

Remember when you wrote a simple range-for in Python and said:
"Wow, why cannot C++ have this?"
```Python 
  for i in range(start, end, step)
```

Well, now it can!

```C++
  for (auto i : range(start, end, step))
  // and, indeed, it has other forms as well:
  for (auto i : range(start, end)) // <=> range(start, end, step=1)
  for (auto i : range(end) // <=> range(end)
```

# Gets optimized to plain built-in for loop
## tested on:
### > Apple clang version 12.0.0)
### > x86-64 GCC 10.2 (asm in godbolt)

# Link to godbolt to try it yourself:
https://godbolt.org/z/qxssch
