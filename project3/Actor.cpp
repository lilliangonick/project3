//
//  Actor.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Actor.h"
#include "utilities.h"
#include <string>

Actor::Actor(int xPos, int yPos, int hit, int armor, int strength, int dexterity) : m_x(xPos), m_y(yPos), m_hit(hit), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_sleepTime(0) {}

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

void Actor::setXPos(int n) {
    m_x = n;
}

void Actor::setYPos(int n) {
    m_y = n;
}

void Actor::setHP(int n) {
    m_hit = m_hit + n;
}

void Actor::setArmor(int n) {
    m_armor = m_armor + n;
}

void Actor::setStrength(int n) {
    m_strength = m_strength + n;
}

void Actor::setDexterity(int n) {
    m_dexterity = m_dexterity + n;
}

void Actor::setSleepTime(int n) {
    m_sleepTime = m_sleepTime + n;
}

// inventory class with a inventory pointer to the player



// in board class put a vector that contains all mosnters so you know wehre they are 
