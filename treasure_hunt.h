#ifndef __TREASURE_HUNT_H
#define __TREASURE_HUNT_H

#include "member.h"
#include "treasure.h"
#include <utility>
#include <concepts>

// tmp placeholder concepts
template<typename T>
concept EncounterSide = true;
template<typename T>
concept Member = requires(T x) { x.isArmed; }; 


template<EncounterSide sideA, EncounterSide sideB>
using Encounter = std::pair<sideA&, sideB&>;

// Spotkanie uczestników: dwóch uzbrojonych
template<Member A, Member B>
requires(A::isArmed && B::isArmed)
constexpr void run(Encounter<A, B> e) {
    if (e.first.getStrength() > e.second.getStrength()) {
        e.first.addValue(e.second.pay());
    } else if (e.first.getStrength() < e.second.getStrength()) {
        e.second.addValue(e.first.pay());
    }
}

// Spotkanie uczestników: co najwyżej jeden uzbrojony
template<Member A, Member B>
constexpr void run(Encounter<A, B> e) {
    if (e.first.isArmed) {
        e.first.addValue(e.second.pay());
    } else if (e.second.isArmed) {
        e.second.addValue(e.first.pay());
    }
}

// Uczestnik znajduje skarb
template<Member A, typename ValueType, bool IsTrapped>
constexpr void run(Encounter<A, Treasure<ValueType, IsTrapped>> e) {
    e.first.loot(std::move(e.second));
}

template<Member A, typename ValueType, bool IsTrapped>
constexpr void run(Encounter<Treasure<ValueType, IsTrapped>, A> e) {
    e.second.loot(std::move(e.first));
}

template<EncounterSide A, EncounterSide B>
constexpr void expedition(Encounter<A, B> e) {
    run(e);
}

template<EncounterSide A, EncounterSide B, typename... Args>
constexpr void expedition(Encounter<A, B> e, Args... args) {
    run(e);
    expedition(args...);
}

#endif //__TREASURE_HUNT_H
