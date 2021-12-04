#ifndef __TREASURE_HUNT_H
#define __TREASURE_HUNT_H

#include "member.h"
#include "treasure.h"
#include <utility>
#include <concepts>

template<typename T>
concept EncounterSide = IsTreasure<T> || IsMember<T>;

template<EncounterSide sideA, EncounterSide sideB>
using Encounter = std::pair<sideA&, sideB&>;

// Spotkanie uczestników: dwóch uzbrojonych
template<IsMember A, IsMember B>
requires (A::isArmed && B::isArmed)
constexpr void run(Encounter<A, B> e) {
    if (e.first.getStrength() > e.second.getStrength()) {
        e.first.addValue(e.second.pay());
    } else if (e.first.getStrength() < e.second.getStrength()) {
        e.second.addValue(e.first.pay());
    }
}

// Spotkanie uczestników: co najwyżej jeden uzbrojony
template<IsMember A, IsMember B>
constexpr void run(Encounter<A, B> e) {
    if (e.first.isArmed) {
        e.first.addValue(e.second.pay());
    } else if (e.second.isArmed) {
        e.second.addValue(e.first.pay());
    }
}

// Uczestnik znajduje skarb
template<IsMember A, IsTreasure B>
constexpr void run(Encounter<A, B> e) {
    e.first.loot(std::move(e.second));
}

template<IsTreasure A, IsMember B>
constexpr void run(Encounter<A, B> e) {
    e.second.loot(std::move(e.first));
}

template<EncounterSide A, EncounterSide B>
constexpr void expedition(Encounter<A, B> e) {run(e);}

template<EncounterSide A, EncounterSide B, typename... Args>
constexpr void expedition(Encounter<A, B> e, Args... args) {
    run(e);
    expedition(args...);
}

#endif //__TREASURE_HUNT_H
