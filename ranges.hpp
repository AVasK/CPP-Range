#define func auto
// ^ Just my preference in style.
// Easy fix of macro redef warning should one happen is to
// replace 'func' with 'auto' and delete this macro

// Range
// a class for range-iterators
template <typename T>
class Range;

// RangeIterator
// a thin proxy, returned by begin() and end()
template <typename T>
class RangeIterator;


// Type autoinference via functions
template <typename T>
func range(T end) -> Range<T>
{
    return Range<T>(end);
}

template <typename T>
func range(T start, T end, T step =T{1}) -> Range<T>
{
    return Range<T>(start, end, step);
}

    
// Range class
template <typename T>
class Range {
public:
    Range(T _end)
        : r_start{}
        , r_end{_end} {}
    
    Range(T _start, T _end)
        : r_start{_start}
        , r_end{_end} {}
    
    Range(T _start, T _end, T _step)
        : r_start{_start}
        , r_end{_end}
        , r_step{_step} {}
    
    // range-based for support:
    // begin() & end():
    func begin() -> RangeIterator<T>
    {
        return RangeIterator<T>( r_start, r_step );
    }
    
    func end() -> RangeIterator<T>
    {
        return RangeIterator<T>( r_end, 0 );
    }
    
private:
    T r_start;
    T r_end;
    T r_step {1};
};


// Proxy
template <typename T>
class RangeIterator {
public:
    RangeIterator(T _value, T _step)
        : current{_value}
        , step{_step} {}
    
    
    // operators to support range-based for:
    // 1. operator++()
    inline func operator++() -> RangeIterator&
    {
        current += step;
        return *this;
    }
    
    // 1+. postfix is given for the sake of completeness
    // (but as usual is slightly less effective)
    inline func operator++(int) -> RangeIterator
    {
        auto temp = current;
        current += step;
        return temp;
    }
    
    // 2. operator!=(other)
    inline func operator!=(const RangeIterator& other) -> bool
    {
        return (current < other.current);
    }
    
    // 3. operator*()
    inline func operator*() -> T&
    {
        return this->current;
    }
    
private:
    T current;
    T step;
};

#undef func
