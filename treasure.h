#ifndef __TREASURE_H
#define __TREASURE_H

#include<concepts>

template<typename T>
concept IsValueType = std::integral<T>;

template<IsValueType ValueType, bool IsTrapped>
class Treasure {
public:
    static constexpr bool isTrapped = IsTrapped;

    constexpr Treasure(ValueType value) : value(value) {};

    constexpr ValueType evaluate() const {return value;};

    constexpr ValueType getLoot() {
        ValueType res = value;
        value = 0;
        return res;
    } 

private:
    ValueType value;
};

template<typename ValueType>
using SafeTreasure = Treasure<ValueType, false>;

template<typename ValueType>
using TrappedTreasure = Treasure<ValueType, true>;

template<typename T>
concept IsTreasure = requires (T x) {
    {Treasure(x)} -> std::same_as<T>;
};

#endif //__TREASURE_H