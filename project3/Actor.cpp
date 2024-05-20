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

Actor::Actor(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity) : m_name(name), m_x(xPos), m_y(yPos), m_hit(hit), m_weapon(weaponName, actionString, dexterityBonus, damage), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_sleepTime(0) {}

Actor::~Actor() {}

// get and set actors attributes
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

Weapon Actor::getWeapon() {
    return m_weapon;
}

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
    m_sleepTime = m_sleepTime + n;
}

void Actor::setWeapon(Weapon weapon) {
    m_weapon = weapon;
}

void Actor::CHANGESTRENGTH(int n) {
    m_strength = n;
}



// TODO ideas
// inventory class with a inventory pointer to the player
// in board class put a vector that contains all mosnters so you know wehre they are 
