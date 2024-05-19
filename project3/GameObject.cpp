//
//  GameObject.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/18/24.
//

#include "GameObject.h"
#include "utilities.h"
 

GameObject::GameObject(string name) : m_name(name) {}

int GameObject::getXPos() {
    return m_x;
}

int GameObject::getYPos() {
    return m_y;
}

void GameObject::setXPos(int n) {
    m_x = n;
}

void GameObject::setYPos(int n) {
    m_y = n;
}

string GameObject::getName() {
    return m_name; 
}

Weapon::Weapon(string name, int dexterityBonus, int damage) : GameObject(name), m_dexterityBonus(dexterityBonus), m_damage(damage) {}

Scroll::Scroll(string name) : GameObject(name) {}


