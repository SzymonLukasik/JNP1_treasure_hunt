#ifndef __TREASURE_H
#define __TREASURE_H

#include<concepts>

template <std::integral ValueType, bool IsTrapped>
class Treasure {
public:
    static constexpr bool isTrapped = IsTrapped;

    constexpr Treasure(ValueType value) : value(value) {};

    constexpr ValueType evaluate() const {return value;};

    constexpr ValueType getLoot() {
        ValueType temp = value;
        value = 0;
        return temp;
    } 

private:
    ValueType value;
};

template <typename ValueType>
using SafeTreasure = Treasure<ValueType, false>;

template <typename ValueType>
using TrappedTreasure = Treasure<ValueType, true>;

#endif //__TREASURE_H