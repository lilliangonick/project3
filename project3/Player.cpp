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

class Temple;

// constructor
Player::Player() : Actor("Player", 0, 0, 20, "short sword", "slashes", 0, 2, 2, 2, 2, false), m_maxHP(20) {
    GameObject* initialWeapon = new Weapon("short sword", "slashes", 0, 2);
    inventory.push_back(initialWeapon);
}

// destructor
Player::~Player() {
    // delete inventory vector
    for (vector<GameObject*>::iterator it = inventory.begin(); it != inventory.end(); it++) {
        delete *it;
    }
    inventory.clear();
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

int Player::getMaxHP() {
    return m_maxHP;
}

// cheat by clicking the c command
void Player::cheat() {
    CHANGESTRENGTH(9);
    m_maxHP = 50;
    CHANGEHITPOINT(50);
    
}

void Player::regainHP() {
    if (trueWithProbability(0.1)) {
        Player::setHP(1);
    }
}

bool Actor::shouldDrop() {
    return false;
}

GameObject* Actor::dropNewItem() {
    return nullptr;
}

// player inventory functions:

// player can pick up objects into its inventory
void Player::pickUpObject(GameObject* object) {
    if (inventory.size() > 25) {
        cout << "Your knapsack is full; you can't pick that up." << endl;
        return;
    }
    if (object->getName() == "stairs") {
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
void Player::applyScroll(GameObject* scroll, Temple* board) {
    // teleportation object
    if (scroll->getName() == "scroll of teleportation") {
        char (*map)[18][70] = board->getMap();
        
        // if there is an object where the player is, do not overwrite it
        (*map)[getYPos()][getXPos()] = ' ';
        if (getXPos() == board->getStairs()->getXPos() && getYPos() == board->getStairs()->getXPos()) {
            board->setStairsSpawn(getXPos(), getYPos());
        }
        if (getXPos() == board->getIdol()->getXPos() && getYPos() == board->getIdol()->getYPos()) {
            board->setIdolSpawn(getXPos(), getYPos());
        }
        
        if (board->isObjectAt(getXPos(), getYPos())) {
            vector<GameObject*> objects = board->getObjects();
            for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
                if ((*it)->getXPos() == getXPos() && (*it)->getYPos() == getYPos()) {
                    if ((*it)->getType() == "Scroll") {
                        (*map)[(*it)->getYPos()][(*it)->getXPos()] = '?';
                    } else {
                        (*map)[(*it)->getYPos()][(*it)->getXPos()] = '(';
                    }
                }
            }
        }
        
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!board->validMove(x, y)) {
            x = randInt(1,69);
            y = randInt(1, 17);
        }
        setXPos(x);
        setYPos(y);
        board->setPlayer(getXPos(),getYPos());
        
    } else if (scroll->getName() == "scroll of enhance armor") {
        setArmor(randInt(1, 3));
    } else if (scroll->getName() == "scroll of strength") {
        setStrength(randInt(1, 3));
    } else if (scroll->getName() == "scroll of enhance health") {
        playerMaxHP(randInt(3, 8));
    } else if (scroll->getName() == "scroll of enhance dexterity") {
        setDexterity(1);
    }
}

// wield a weapon from inventory
void Player::weildWeapon() {
    cout << "Inventory: " << endl;
    char firstChar = 'a';
    for (vector<GameObject*>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
        cout << firstChar << ". " << (*it)->getName() << endl;
        firstChar++;
    }

    char c = getCharacter();


    int index = c - 'a';
    
    if (index < 0 || index > inventory.size() - 1) {
        return;
    }
    
    if (index >= 0 && index < inventory.size()) {
        GameObject* selectedItem = inventory[index];
        
        // check if the selected item is a weapon
        Weapon* weapon = dynamic_cast<Weapon*>(selectedItem);
        if (weapon != nullptr) {
            setWeapon(*weapon);
            inventoryResult.push_back("You are wielding " + selectedItem->getName());
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
void Player::readScroll(Temple* board) {
    cout << "Inventory: " << endl;
    char firstChar = 'a';
    for (vector<GameObject*>::iterator it = inventory.begin(); it != inventory.end(); ++it) {
           cout << firstChar << ". " << (*it)->getName() << endl;
           firstChar++;
       }

    char c = getCharacter();

    int index = c - 'a';
    if (index >= 0 && index < inventory.size()) {
        GameObject* selectedItem = inventory[index];

        // check if the selected item is a weapon (you can not read a weapon)
        Weapon* weapon = dynamic_cast<Weapon*>(selectedItem);
        if (weapon != nullptr) {
            inventoryResult.push_back("You can't read a " + selectedItem->getName());
        } else {
        // you can read a scroll
            Scroll* scroll = dynamic_cast<Scroll*>(selectedItem);
            if (scroll != nullptr) {
                applyScroll(scroll, board);
                string result;
                if (scroll->getName() == "scroll of teleportation") {
                    result = "\nYou feel your body wrenched in space and time.";
                } else if (scroll->getName() == "scroll of enhance armor") {
                    result = "\nYour armor glows blue.";
                } else if (scroll->getName() == "scroll of strength") {
                    result = "\nYour muscles bulge.";
                } else if (scroll->getName() == "scroll of enhance health") {
                    result = "\nYou feel your heart beating stronger.";
                } else if (scroll->getName() == "scroll of enhance dexterity") {
                    result = "\nYou feel like less of a klutz.";
                }
                inventoryResult.push_back("You read the scroll called " + scroll->getName() + result);
                delete selectedItem;
                inventory.erase(inventory.begin() + index);
            }
        }
    }
}

// print what player is using from the inventory
void Player::printInventoryResult() {
    if (inventoryResult.size() != 0) {
        cout << inventoryResult[0] << endl;
        inventoryResult.erase(inventoryResult.begin());
    }
}

vector<string> Player::getInventoryResults() {
    return inventoryResult;
}
