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
Player::Player() : Actor("Player", 0, 0, 20, "short sword", "slashes", 0, 2, 2, 2, 2, false), m_maxHP(20) {
    GameObject* initialWeapon = new Weapon("short sword", "slashes", 0, 2);
    inventory.push_back(initialWeapon);
}

// destructor
Player::~Player() {
    for (vector<GameObject*>::iterator it = inventory.begin(); it != inventory.end(); it++) {
        delete *it; 
    }
//    for (size_t i = 0; i < inventory.size(); i++) {
//        delete inventory[i];
//    }
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

// apply the effect of using the scrolls
void Player::applyScroll(GameObject* scroll) {
    // teleportation object
    if (scroll->getName() == "scroll of teleportation") {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
//        while (!validMove(x, y)) {
//            x = randInt(1,69);
//            y = randInt(1, 17);
//        }
        setXPos(x);
        setYPos(y);
    } else if (scroll->getName() == "scroll of armor") {
        setArmor(randInt(1, 3));
    } else if (scroll->getName() == "scroll of strength") {
        setStrength(randInt(1, 3));
        cout << m_maxHP;
    } else if (scroll->getName() == "croll of enhance health") {
        playerMaxHP(randInt(3, 8));
    } else if (scroll->getName() == "scroll of enhance dexterity") {
        setDexterity(1);
    }
}

// cheat by clicking the c command
void Player::cheat() {
    CHANGESTRENGTH(9);
    m_maxHP = 50;
    cout << "max HP: " << m_maxHP << endl;
}

void Player::weildWeapon() {
    cout << "Inventory: " << endl;
    char firstChar = 'a';
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << firstChar << ". " << inventory[i]->getName() << endl;
        firstChar++;
    }

    cout << "Enter your choice: ";
    char c = getCharacter();
    cout << "Character entered: " << c << endl;

    int index = c - 'a';
    if (index >= 0 && index < inventory.size()) {
        GameObject* selectedItem = inventory[index];

        // check if the selected item is a weapon
        Weapon* weapon = dynamic_cast<Weapon*>(selectedItem);
        if (weapon != nullptr) {
            setWeapon(*weapon);
            inventoryResult.push_back("You are wielding " + getWeapon().getName());
        } else {
        // if not, you can not weild a scroll
            Scroll* scroll = dynamic_cast<Scroll*>(selectedItem);
            if (scroll != nullptr) {
                inventoryResult.push_back("You can't wield " + scroll->getName());
            }
        }
    }
}

// apply the effects of reading a scroll
void Player::readScroll() {
    cout << "Inventory: " << endl;
    char firstChar = 'a';
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << firstChar << ". " << inventory[i]->getName() << endl;
        firstChar++;
    }

    cout << "Enter your choice: ";
    char c = getCharacter();
    cout << "Character entered: " << c << endl;

    int index = c - 'a';
    if (index >= 0 && index < inventory.size()) {
        GameObject* selectedItem = inventory[index];

        // check if the selected item is a weapon (you can not read a weapon)
        Weapon* weapon = dynamic_cast<Weapon*>(selectedItem);
        if (weapon != nullptr) {
            inventoryResult.push_back("You can't read a " + getWeapon().getName());
        } else {
        // you can read a scroll
            Scroll* scroll = dynamic_cast<Scroll*>(selectedItem);
            if (scroll != nullptr) {
                applyScroll(scroll);
                string result;
                if (scroll->getName() == "scroll of teleportation") {
                    result = "\n";
                } else if (scroll->getName() == "scroll of improve armor") {
                    result = "\nYour armor glows blue.";
                } else if (scroll->getName() == "scroll of strength") {
                    result = "\nYour muscles bulge.";
                } else if (scroll->getName() == "scroll of enhance health") {
                    result = "\nYou feel your heart beating stronger.";
                } else if (scroll->getName() == "scroll of enhance dexterity") {
                    result = "\nYou feel like less of a klutz.";
                }
                inventoryResult.push_back("You read the scroll called " + scroll->getName() + result);
            }
        }
    }
}

void Player::printInventoryResult() {
    cout << inventoryResult[0] << endl;
    inventoryResult.erase(inventoryResult.begin());
}

vector<string> Player::getInventoryResults() {
    return inventoryResult;
}

void Player::regainHP() {
    if (trueWithProbability(0.1)) {
        setHP(1);
    } 
}
