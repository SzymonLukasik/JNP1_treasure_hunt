#ifndef __TREASURE_HUNT_H
#define __TREASURE_HUNT_H

#include "member.h"
#include "treasure.h"
#include <utility>
#include <concepts>

template<typename T>
concept EncounterSide = IsTreasure<T> || IsMember<T>;

template<EncounterSide T, EncounterSide U>
using Encounter = std::pair<T&, U&>;

// Spotkanie uczestników: dwóch uzbrojonych
template<IsMember T, IsMember U>
requires (T::isArmed && U::isArmed)
constexpr void run(Encounter<T, U> e) {
    if (e.first.getStrength() > e.second.getStrength()) {
        e.first.addValue(e.second.pay());
    } else if (e.first.getStrength() < e.second.getStrength()) {
        e.second.addValue(e.first.pay());
    }
}

// Spotkanie uczestników: co najwyżej jeden uzbrojony
template<IsMember T, IsMember U>
constexpr void run(Encounter<T, U> e) {
    if (e.first.isArmed) {
        e.first.addValue(e.second.pay());
    } else if (e.second.isArmed) {
        e.second.addValue(e.first.pay());
    }
}

// Uczestnik znajduje skarb
template<IsMember T, IsTreasure U>
constexpr void run(Encounter<T, U> e) {
    e.first.loot(std::move(e.second));
}

template<IsTreasure T, IsMember U>
constexpr void run(Encounter<T, U> e) {
    e.second.loot(std::move(e.first));
}

template<EncounterSide T, EncounterSide U>
constexpr void expedition(Encounter<T, U> e) {run(e);}

template<EncounterSide T, EncounterSide U, typename... Args>
constexpr void expedition(Encounter<T, U> e, Args... args) {
    run(e);
    expedition(args...);
}

#endif //__TREASURE_HUNT_H
