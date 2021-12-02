#ifndef __MEMBER_H
#define __MEMBER_H

#include "treasure.h"
#include <cstddef>
#include <concepts>

template<typename ValueType, bool IsArmed>
class Adventurer;

template<typename ValueType>
class Adventurer<ValueType, false> {
public:
    using strength_t = unsigned long;
    static constexpr bool isArmed = false;

    constexpr Adventurer() = default;

    //todo: to powinno być w jednej funkcji raczej
    constexpr void loot(Treasure<ValueType, false> &&treasure) {
         valueSum += treasure.getLoot();
    }
    constexpr void loot(Treasure<ValueType, true> &&treasure) {}

    constexpr ValueType pay() {
        ValueType res = valueSum;
        valueSum = 0;
        return res;
    }
private:
    ValueType valueSum = 0;
};

template<typename ValueType>
class Adventurer<ValueType, true> {

public:
    using strength_t = unsigned long;
    static constexpr bool isArmed = true;

    constexpr Adventurer(strength_t s) : strength(s) {}

    constexpr strength_t getStrength() {
        return strength;
    }

    constexpr void loot (Treasure<ValueType, true> &&treasure) {
        strength /= 2;
        valueSum += treasure.getLoot();
    }

    constexpr void loot(Treasure<ValueType, false> &&treasure) {
        valueSum += treasure.getLoot();
    }

    constexpr ValueType pay() {
        ValueType res = valueSum;
        valueSum = 0;
        return res;
    }
private:
    ValueType valueSum = 0;
    strength_t strength;
};

template<typename ValueType>
using Explorer = Adventurer<ValueType, false>;

template <typename ValueType, std::size_t CompletedExpeditions>
    requires (CompletedExpeditions < 25)
class Veteran {
public:
    using strength_t = unsigned long;
    static constexpr bool isArmed = true;

    constexpr Veteran() {
        strength = getFib(CompletedExpeditions);
    }

    constexpr void loot(Treasure<ValueType, false> &&treasure) {
        valueSum += treasure.getLoot();
    }
    constexpr void loot(Treasure<ValueType, true> &&treasure) {
        valueSum += treasure.getLoot();
    }

    constexpr strength_t getStrength() {
        return strength;
    }

    constexpr ValueType pay() {
        ValueType res = valueSum;
        valueSum = 0;
        return res;
    }

private:
    ValueType valueSum = 0;
    strength_t strength;

    constexpr strength_t getFib(std::size_t n) {
        if (n == 0) return 0;
        size_t prev = 0;
        size_t cur = 1;
        for (int i = 2; i <= n; i++) {
            size_t next = prev + cur;
            prev = cur;
            cur = next;
        }
        return cur;
    }
};

#endif //__MEMBER_H
