//
//  Actor.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Actor.h"
#include "utilities.h"
#include <string>
#include <iostream>

using namespace std;

// construct info
Actor::Actor(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity, bool isMonster) : m_name(name), m_x(xPos), m_y(yPos), m_hit(hit), m_weapon(weaponName, actionString, dexterityBonus, damage), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_sleepTime(0), m_isMonster(isMonster){}

Actor::~Actor() {}

// get actor attributes
int Actor::getXPos() {
    return m_x;
}

int Actor::getYPos() {
    return m_y;
}

int Actor::getHP() {
    return m_hit;
}

int Actor::getArmor() {
    return m_armor;
}

int Actor::getStrength() {
    return m_strength;
}

int Actor::getDexterity() {
    return m_dexterity;
}

string Actor::getName() {
    return m_name;
}

int Actor::getSleepTime() {
    return m_sleepTime;
}

Weapon Actor::getWeapon() {
    return m_weapon;
}

// set actor attributes
void Actor::setXPos(int n) {
    m_x = n;
}

void Actor::setYPos(int n) {
    m_y = n;
}

void Actor::setHP(int n) {
    if (m_hit + n <= 99) {
        m_hit = m_hit + n;
    } else {
        m_hit = 99; 
    }
}

void Actor::setArmor(int n) {
    if (m_armor + n <= 99) {
        m_armor = m_armor + n;;
    } else {
        m_armor = 99;
    }
}

void Actor::setStrength(int n) {
    if (m_strength + n <= 99) {
        m_strength = m_strength + n;
    } else {
        m_strength = 99;
    }
}

void Actor::setDexterity(int n) {
    if (m_dexterity + n <= 99) {
        m_dexterity = m_dexterity + n;
    } else {
        m_dexterity = 99;
    }
}

void Actor::setSleepTime(int n) {
    if (m_sleepTime + n <= 9) {
        m_sleepTime = m_sleepTime + n;
    } else {
        m_sleepTime = 9;
    }
}

void Actor::setWeapon(Weapon weapon) {
    m_weapon = weapon;
}

void Actor::CHANGESTRENGTH(int n) {
    m_strength = n;
}

void Actor::CHANGEHITPOINT(int n) {
    m_hit = n;
}

bool Actor::isMonster() {
    return m_isMonster;
}

// sleeping functionality
bool Actor::isSleeping() {
    if (m_sleepTime > 0) {
        return true;
    } else {
        return false; 
    }
}

void Actor::magicFangsEffect() {
    if (trueWithProbability(0.2)) {
        int sleepLength = randInt(2, 6);
        if (m_sleepTime < sleepLength) {
            m_sleepTime = sleepLength;
        }
    }
}

void Actor::decreaseSleepTime() {
    m_sleepTime--; 
}
// TODO ideas
// inventory class with a inventory pointer to the player
// in board class put a vector that contains all mosnters so you know wehre they are 
