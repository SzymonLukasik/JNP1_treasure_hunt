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
class SafeTreasure : Treasure<ValueType, false> {
public:
    constexpr
    SafeTreasure(ValueType value) : Treasure<ValueType, false>(value) {};
};

template <typename ValueType>
class TrappedTreasure : Treasure<ValueType, true> {
public:
    constexpr
    TrappedTreasure(ValueType value) : Treasure<ValueType, true>(value) {};
};

#endif