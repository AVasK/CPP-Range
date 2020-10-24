#include <type_traits> // enable_if, is_integral

template <bool Cond, typename Type>
using Enable_if = typename std::enable_if<Cond,Type>::type;

#define func auto
// ^ Just my preference in style.
// Easy fix of macro redef warning should one happen is to
// replace 'func' with 'auto' and delete this macro

// Range
// a class for range-iterators
template <typename T>
class Range;

template <typename T>
class SimpleRange;

// RangeIterator
// a thin proxy, returned by begin() and end()
template <typename T>
class RangeIterator;

// SimpleRangeIterator
// overall the same, should be faster(?)
template <typename T>
class SimpleRangeIterator;


// Type autoinference via functions
// cases with step == ++ are handled more effectively by SimpleRange
template <typename T>
inline func range(T end) -> Enable_if<!std::is_floating_point<T>::value, SimpleRange<T>>
{
    return SimpleRange<T>(end);
}

template <typename T>
inline func range(T end) -> Enable_if<std::is_floating_point<T>::value, Range<T>>
{
    return Range<T>(end);
}

template <typename T>
inline func range(T start, T end) -> Enable_if<!std::is_floating_point<T>::value, SimpleRange<T>>
{
    return SimpleRange<T>(start, end);
}


template <typename T>
inline func range(T start, T end) -> Enable_if<std::is_floating_point<T>::value, Range<T>>
{
    return Range<T>(start, end);
}

// A more complex case is handled by a more complex range type
template <typename T>
inline func range(T start, T end, T step) -> Range<T>
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
        return (step > 0) ? (current < other.current) : (current > other.current);
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



// In hope of optimizing away the step==1 case
// IntegralRange class
template <typename T>
class SimpleRange {
public:
    SimpleRange(T _end)
        : r_start{}
        , r_end{_end} {}
    
    SimpleRange(T _start, T _end)
        : r_start{_start}
        , r_end{_end} {}
    
    // range-based for support:
    // begin() & end():
    inline func begin() -> SimpleRangeIterator<T>
    {
        return SimpleRangeIterator<T>( r_start );
    }
    
    inline func end() -> SimpleRangeIterator<T>
    {
        return SimpleRangeIterator<T>( r_end );
    }
    
private:
    const T r_start;
    const T r_end;
};


// Proxy
template <typename T>
class SimpleRangeIterator {
public:
    SimpleRangeIterator(T _value) : current{_value} {}
    
    // operators to support range-based for:
    // 1. operator++()
    inline func operator++() -> SimpleRangeIterator&
    {
        ++current;
        return *this;
    }
    
    // 1+. postfix is given for the sake of completeness
    // (but as usual is slightly less effective)
    inline func operator++(int) -> SimpleRangeIterator
    {
        auto temp = current;
        ++current;
        return temp;
    }
    
    // 2. operator!=(other)
    inline func operator!=(const SimpleRangeIterator& other) -> bool
    {
        return (current != other.current);
    }
    
    // 3. operator*()
    inline func operator*() -> T&
    {
        return this->current;
    }
    
private:
    T current;
};

#undef func
