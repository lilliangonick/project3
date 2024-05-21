//
//  GameObject.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/18/24.
//

#include "GameObject.h"
#include "utilities.h"
 
// constructor
GameObject::GameObject(string type, string name) : m_type(type), m_name(name) {}

// virtual destructor for base class
GameObject::~GameObject() {}

// getters
int GameObject::getXPos() {
    return m_x;
}

int GameObject::getYPos() {
    return m_y;
}

string GameObject::getName() {
    return m_name;
}

string GameObject::getType() {
    return m_type;
}


// setters
void GameObject::setXPos(int n) {
    m_x = n;
}

void GameObject::setYPos(int n) {
    m_y = n;
}

// weapon definitions
Weapon::Weapon(string name, string actionString, int dexterityBonus, int damage) : GameObject("Weapon", name), m_actionString(actionString), m_dexterityBonus(dexterityBonus), m_damage(damage) {}

// getters
string Weapon::getAction() {
    return m_actionString;
}

int Weapon::getDexterityBonus() {
    return m_dexterityBonus;
}

int Weapon::getDamage() {
    return m_damage; 
}

// scroll definitions 
Scroll::Scroll(string name) : GameObject("Scroll", name) {}



