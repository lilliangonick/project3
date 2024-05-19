//
//  Player.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Player.h"
#include "Temple.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// constructor
Player::Player() : Actor("Player", 0, 0, 20, "short sword", "slashes", 0, 2, 2, 2, 2) {
    Weapon* initialWeapon = new Weapon("short sword", "slashes", 0, 2);
    inventory.push_back(initialWeapon);
}

// destructor
Player::~Player() {
    for (size_t i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
}
// set PlayerHP
void Player::setHP(int n) {
    if (getHP() + n <= m_maxHP) {
        Actor::setHP(n);
    }
}

// determine what the max HP is for a player
void Player::playerMaxHP(int n) {
    m_maxHP = getHP() + n;
}

// player can pick up objects into its inventory
void Player::pickUpObject(GameObject* object) {
    if (inventory.size() > 25) {
        return;
    }
    inventory.push_back(object);
    if (object->getType() == "Scroll") {
        cout << "You pick up a " << object->getType() << " called " << object->getName() << endl;
    } else {
        cout << "You pick up " << object->getName() << endl;
    }
}

// print the objects stored in inventory, with letters a - z
void Player::printInventory() {
    cout << "Inventory: " << endl;
    char firstChar = 'a';
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << firstChar << ". " << inventory[i]->getName() << endl;
        firstChar++;
    }
}
