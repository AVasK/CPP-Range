# C++ ranges
## That cool range syntax from Python now in C++
<!> Unfortunately, doesn't fix other bunch of 
C++ syntactic oddities...

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

Or, if you did not... 
Well, there's nothing else here, sorry
