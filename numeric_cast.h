#ifndef NUMERIC_CAST_H
#define NUMERIC_CAST_H

#include "compare.h"

template<class Target, class Source, bool>
struct overflow_checker;

template<class Target, class Source>
struct overflow_checker<Target, Source, true>
{
    static void check(const Source &source)
    {
        if(less(std::numeric_limits<Target>::max(), source))
            throw std::overflow_error("overflow_checker");
    }
};

template<class Target, class Source>
struct overflow_checker<Target, Source, false>
{
    static void check(const Source &) {}
};

template<class Target, class Source, bool>
struct underflow_checker;

template<class Target, class Source>
struct underflow_checker<Target, Source, true>
{
    static void check(const Source &source)
    {
        if(greater(std::numeric_limits<Target>::min(), source))
            throw std::underflow_error("underflow_checker");
    }
};

template<class Target, class Source>
struct underflow_checker<Target, Source, false>
{
    static void check(const Source &) {}
};


template<class Target,
         class Source>
Target numeric_cast(const Source &source)
{
    static_assert(std::is_arithmetic<Source>::value && std::is_arithmetic<Target>::value, "Types should be arithmetic");

    overflow_checker<Target, Source, less(std::numeric_limits<Target>::max(), std::numeric_limits<Source>::max())>::check(source);
    underflow_checker<Target,Source, greater(std::numeric_limits<Target>::min(), std::numeric_limits<Source>::min())>::check(source);

    return static_cast<Target>(source);
}

#endif // NUMERIC_CAST_H
