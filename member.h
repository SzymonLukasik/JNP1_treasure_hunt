#ifndef __MEMBER_H
#define __MEMBER_H

#include "treasure.h"
#include <cstddef>
#include <concepts>
#include <cstdint>

template<std::integral ValueType, bool IsArmed>
class Adventurer {
public:
    using strength_t = uint32_t;

    static constexpr bool isArmed = IsArmed;

    constexpr Adventurer() requires (!IsArmed) {}

    constexpr Adventurer(strength_t s) requires (IsArmed) : strength(s) {}

    constexpr strength_t getStrength() requires (IsArmed) { return strength; }

    constexpr void loot(SafeTreasure<ValueType>&& treasure) {
        valueSum += treasure.getLoot();
    }

    constexpr
        void loot(TrappedTreasure<ValueType>&& treasure) requires(IsArmed) {
        if (strength > 0) {
            strength /= 2;
            valueSum += treasure.getLoot();
        }
    }

    constexpr ValueType pay() {
        ValueType res = valueSum;
        valueSum = 0;
        return res;
    }

protected:
    ValueType valueSum = 0;

    strength_t strength = 0;
};

template<typename ValueType>
using Explorer = Adventurer<ValueType, false>;

template <std::integral ValueType, std::size_t CompletedExpeditions>
requires (CompletedExpeditions < 25)
class Veteran {
public:
    using strength_t = uint32_t;

    static constexpr bool isArmed = true;

    constexpr Veteran() : strength(getFib(CompletedExpeditions)) {}

    template <bool IsArmed>
    constexpr void loot(Treasure<ValueType, IsArmed> &&treasure) {
        valueSum += treasure.getLoot();
    }

    constexpr strength_t getStrength() {return strength;}

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
        strength_t prev = 0;
        strength_t cur = 1;
        for (size_t i = 2; i <= n; i++) {
            strength_t next = prev + cur;
            prev = cur;
            cur = next;
        }
        return cur;
    }
};

#endif //__MEMBER_H