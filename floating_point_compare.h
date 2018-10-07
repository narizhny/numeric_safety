#ifndef FLOATING_POINT_COMPARE_H
#define FLOATING_POINT_COMPARE_H

#include <cmath>
#include <type_traits>
#include <limits>

namespace detail
{
template<class T, int precission>
struct delimiter
{
    static constexpr T value = std::pow<T>(static_cast<T>(0.1), precission);
};
}

template<int precission, class Left, class Right>
constexpr bool floating_point_compare(const Left &left, const Right &right)
{
	using common_type = typename std::common_type<Left, Right>::type;
	static_assert(std::is_floating_point<common_type>::value, "Only floating point types");
	
    return std::abs(left - right) < detail::delimiter<common_type, precission>::value;
}

template<class Left, class Right>
constexpr bool floating_point_compare(const Left &left, const Right &right)
{
	using common_type = typename std::common_type<Left, Right>::type;
	static_assert(std::is_floating_point<common_type>::value, "Only floating point types");
	
    return std::abs(left - right) < std::numeric_limits<common_type>::epsilon();
}

#endif // FLOATING_POINT_COMPARE_H
