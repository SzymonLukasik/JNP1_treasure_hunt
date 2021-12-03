#include <utility>
#include "treasure.h"
#include "member.h"

using namespace std;

constexpr int evaluate() {
    Treasure<int, false> t = Treasure<int, false>(1);
    return t.evaluate();
}

constexpr int getLoot() {
    Treasure<int, false> t = Treasure<int, false>(1);
    return t.getLoot();
}

constexpr unsigned long test_adventurer() {
    Adventurer<int, true> a = Adventurer<int, true>(1);
    return a.getStrength();
}


constexpr unsigned long test_veteran() {
    Veteran<int, 1> a = Veteran<int, 1>();
    return a.getStrength();
}

constexpr int test_looting1() {
    Explorer<int> a = Explorer<int>();
    Veteran<int, 1> b = Veteran<int, 1>();

    SafeTreasure<int> t1 = SafeTreasure<int>(1);
    TrappedTreasure<int> t2 = TrappedTreasure<int>(1);

    a.loot(move(t1));
    b.loot(move(t2)); //Działa też b.loot<true>(move(t2));

    return a.pay() + b.pay();
}

constexpr int test_looting2() {
    Adventurer<int, true> a = Adventurer<int, true>(6);

    TrappedTreasure<int> t1 = TrappedTreasure<int>(1);
    
    a.loot(move(t1));
    
    return a.pay() + a.getStrength();
}

/*
    constexpr void loot(Treasure<ValueType, true> &&treasure) {
        valueSum += treasure.getLoot();
    }*/

int main() {
    static_assert(evaluate() == 1);
    static_assert(getLoot() == 1);
    static_assert(test_adventurer() == 1);
    static_assert(test_veteran() == 1);
    static_assert(test_looting2() == 4);
}