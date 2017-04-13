#ifndef FLOATING_POINT_COMPARE_H
#define FLOATING_POINT_COMPARE_H

#include <math.h>

namespace detail
{
template<class T, int precission>
struct delimiter
{
    static constexpr T value = std::pow<T>(static_cast<T>(0.1), precission);
};
}

template<int precission = 8, class Left, class Right>
constexpr bool floating_point_compare(const Left &left, const Right &right)
{
    return std::abs(left - right) < detail::delimiter<Left, precission>::value;
}

#endif // FLOATING_POINT_COMPARE_H
