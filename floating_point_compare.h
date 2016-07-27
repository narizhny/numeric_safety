#ifndef FLOATING_POINT_COMPARE_H
#define FLOATING_POINT_COMPARE_H

#include <math.h>

template<int precission = 8, class Left, class Right>
constexpr bool floating_point_compare(const Left &left, const Right &right)
{
    return std::abs(left - right) < (std::pow(0.1, precission) / 2);
}

#endif // FLOATING_POINT_COMPARE_H
