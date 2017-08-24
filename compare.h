#ifndef COMPARE_H
#define COMPARE_H

#include <type_traits>

struct LeftSigned;
struct RightSigned;
struct EqualSigned;

template<class Left, class Right, class Type> struct LessOperator;

template<class Left, class Right>
struct LessOperator<Left, Right, EqualSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return left < right;
    }
};

template<class Left, class Right>
struct LessOperator<Left, Right, LeftSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return left < 0
                || static_cast<Right>(left) < right;
    }
};

template<class Left, class Right>
struct LessOperator<Left, Right, RightSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return right > 0
                && left < static_cast<Left>(right);
    }
};

template<class Left, class Right, class Type> struct GreaterOperator;

template<class Left, class Right>
struct GreaterOperator<Left, Right, EqualSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return left > right;
    }
};

template<class Left, class Right>
struct GreaterOperator<Left, Right, LeftSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return left > 0
                && static_cast<Right>(left) > right;
    }
};

template<class Left, class Right>
struct GreaterOperator<Left, Right, RightSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return right < 0
                || left > static_cast<Left>(right);
    }
};

template<class Left, class Right, class Type> struct EqualOperator;

template<class Left, class Right>
struct EqualOperator<Left, Right, EqualSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return left == right;
    }
};

template<class Left, class Right>
struct EqualOperator<Left, Right, LeftSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return left > 0
                && static_cast<Right>(left) == right;
    }
};

template<class Left, class Right>
struct EqualOperator<Left, Right, RightSigned>
{
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return right > 0
                && left == static_cast<Left>(right);
    }
};

template<bool leftSigned, bool rightSigned>
struct CompareTypeChecker;

template<> struct CompareTypeChecker<true, true> {typedef EqualSigned CompareType;};
template<> struct CompareTypeChecker<false, false> {typedef EqualSigned CompareType;};
template<> struct CompareTypeChecker<true, false> {typedef LeftSigned CompareType;};
template<> struct CompareTypeChecker<false, true> {typedef RightSigned CompareType;};

template<class Left,
         class Right,
         template<class Left, class Right, class Type> class Operator>
struct Comparer
{
    static_assert(std::is_arithmetic<Left>::value && std::is_arithmetic<Right>::value, "Types should be arithmetic");
public:
    constexpr static bool compare(const Left &left, const Right &right)
    {
        return Operator<
                Left,
                Right,
                typename CompareTypeChecker<std::is_signed<Left>::value, std::is_signed<Right>::value>::CompareType>
                ::compare(left, right);
    }
};

template<class Left, class Right>
constexpr bool less(const Left &left, const Right &right)
{
    return Comparer<Left, Right, LessOperator>::compare(left, right);
}

template<class Left, class Right>
constexpr bool greater(const Left &left, const Right &right)
{
    return Comparer<Left, Right, GreaterOperator>::compare(left, right);
}

template<class Left, class Right>
constexpr bool equal(const Left &left, const Right &right)
{
    return Comparer<Left, Right, EqualOperator>::compare(left, right);
}

#endif // COMPARE_H
