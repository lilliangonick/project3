//
//  Temple.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Temple.h"
#include "Player.h"
#include "Monster.h"
#include "utilities.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace std;

// create temple (constructor)
Temple::Temple(Player* pointer) : player(pointer), m_level(0), m_justAttacked(false) {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            if (i == 0 || j == 0|| j == 69 || i == 17) {
                m_map[i][j] = '#';
            } else {
                m_map[i][j] = ' ';
            }
        }
    }
 }

// destructor (deallocate memory)
Temple::~Temple() {
    for (size_t i = 0; i < monsters.size(); i++) {
        delete monsters[i];
    }
    for (size_t i = 0; i < objects.size(); i++) {
        delete objects[i];
    }
}

// display map
void Temple::printMap() {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            std::cout << m_map[i][j];
        }
        cout << endl;
    }
}

// display player stats
void Temple::printStats() {
    cout << "Level: " << m_level << ", Hit points: " << player->getHP() << ", Armor: " << player->getArmor() << ", Strength: " << player->getStrength() << ", Dexterity: " << player->getDexterity() << endl << endl; 
}

// set player icon
void Temple::setPlayer(int x, int y) {
    m_map[y][x] = '@';
}

bool Temple::justAttacked() {
    return m_justAttacked;
}

// see if the move is valid
bool Temple::validMove(int xPos, int yPos) {
    if (m_map[yPos][xPos] == '#') {
        return false;
    }
//    if ( m_map[yPos][xPos] == '@' || m_map[yPos][xPos] == 'B' || m_map[yPos][xPos] == 'D' || m_map[yPos][xPos] == 'G' || m_map[yPos][xPos] == 'S') {
//        return false;
//    }
    return true;
}

// move the player based on a command
void Temple::movePlayer(char c) {
    m_justAttacked = false;
    int newX = player->getXPos();
    int newY = player->getYPos();

    // Determine the new position based on the direction
    if (c == ARROW_LEFT) {
        newX -= 1;
    } else if (c == ARROW_RIGHT) {
        newX += 1;
    } else if (c == ARROW_UP) {
        newY -= 1;
    } else if (c == ARROW_DOWN) {
        newY += 1;
    }
    
    // Check if there is a monster at the new position
    if (isMonsterAt(newX, newY)) {
        Monster* monster = getMonsterAt(newX, newY);
        cout << "monster HP before: " << monster->getHP() << endl;
        attack(player, monster, player->getWeapon());
        cout << "monster HP: " << monster->getHP() << endl;
        // If the monster is dead, remove it from the map and the monsters list
        if (monster->getHP() <= 0) {
            m_map[monster->getYPos()][monster->getXPos()] = ' ';
            monsters.erase(std::remove(monsters.begin(), monsters.end(), monster), monsters.end());
            delete monster; // Free the memory
        }
        m_justAttacked = true;
        return; // Do not move the player
    }

    
    m_map[player->getYPos()][player->getXPos()] = ' ';
    // make sure player movement does not overwrite the objects
    if (isObjectAt(player->getXPos(), player->getYPos())) {
        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i]->getXPos() == player->getXPos() && objects[i]->getYPos() == player->getYPos()) {
                if (objects[i]->getType() == "Scroll") {
                    m_map[objects[i]->getYPos()][objects[i]->getXPos()] = '?';
                } else {
                    m_map[objects[i]->getYPos()][objects[i]->getXPos()] = '(';
                }
            }
        }
    }
    if (c == ARROW_LEFT) {
        player->Actor::setXPos(player->getXPos() - 1);
    } else if (c == ARROW_RIGHT) {
        player->Actor::setXPos(player->getXPos() + 1);
    } else if (c == ARROW_UP) {
        player->Actor::setYPos(player->getYPos() - 1);
    } else if (c == ARROW_DOWN){
        player->Actor::setYPos(player->getYPos() + 1);
    } else {
        cout << "BAD";  // REMOVE BEFORE SUBMIT
    }
    setPlayer(player->getXPos(), player->getYPos());
}

// set spawn of the player 
void Temple::setPlayerSpawn() {
    int x = randInt(1, 69);
    int y = randInt(1, 17);
    while (!validMove(x, y)) {
        x = randInt(1,69);
        y = randInt(1, 17);
    }
    player->setXPos(x);
    player->setYPos(y);
}

// set spawn of the monsters
void Temple::setMonsterSpawn() {
    for (size_t i = 0; i < monsters.size(); i++) {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!validMove(x, y)) {
            x = randInt(1,69);
            y = randInt(1, 17);
        }
        monsters[i]->setXPos(x);
        monsters[i]->setYPos(y);
        Monster& monster = *monsters[i];  // Dereference the pointer once
        if (typeid(monster) == typeid(Snakewoman)) {
            m_map[monsters[i]->getYPos()][monsters[i]->getXPos()] = 'S';
        } else if (typeid(monster) == typeid(Goblin)) {
            m_map[monsters[i]->getYPos()][monsters[i]->getXPos()] = 'G';
        } else if (typeid(monster) == typeid(Bogeyman)) {
            m_map[monsters[i]->getYPos()][monsters[i]->getXPos()] = 'B';
        } else if (typeid(monster) == typeid(Dragon)) {
            m_map[monsters[i]->getYPos()][monsters[i]->getXPos()] = 'D';
        }
    }
}

// create new monsters at the spawn of a new level
void Temple::setMonster() {
    int m;
    if (m_level == 0) {
        m = randInt(2, 5*(0+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 1);
                if (rand == 0) {
                    monster = new Snakewoman();
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin();
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 1) {
        m = randInt(2, 5*(0+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 1);
                if (rand == 0) {
                    monster = new Snakewoman();
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin();
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 2) {
        m = randInt(2, 5*(2+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 2);
                if (rand == 0) {
                    monster = new Snakewoman();
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin();
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman();
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 3) {
        m = randInt(2, 5*(3+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 3);
                if (rand == 0) {
                    monster = new Snakewoman();
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin();
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman();
                    monsters.push_back(monster);
                } else if (rand == 3) {
                    monster = new Dragon();
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 4) {
        m = randInt(2, 5*(4+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 3);
                if (rand == 0) {
                    monster = new Snakewoman();
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin();
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman();
                    monsters.push_back(monster);
                } else if (rand == 3) {
                    monster = new Dragon();
                    monsters.push_back(monster);
                }
        }
    }
}

// spawn 2 -3 GameObjects at the start of a new level
void Temple::setGameObject() {
    int num = randInt(2, 3);
    vector<string> objectTypes = {
            "mace", "short sword", "long sword",
            "scroll of enhance armor", "scroll of strength",
            "scroll of enhance health", "scroll of enhance dexterity"
        };

    for (int i = 0; i < num; i++) {
        int randIndex = randInt(0, 6);
        string objectType = objectTypes[randIndex];
        
        GameObject* object = nullptr;
        if (objectType == "mace") {
            object = new Weapon("mace", "swings", 0, 2);
            objects.push_back(object);
        } else if (objectType == "short sword") {
            object = new Weapon("short sword", "slashes", 0, 2);
            objects.push_back(object);
        } else if (objectType == "long sword") {
            object = new Weapon("long sword", "swings", 2, 4);
            objects.push_back(object);
        } else if (objectType == "scroll of enhance armor") {
            object = new Scroll("scroll of enhance armor");
            objects.push_back(object);
        } else if (objectType == "scroll of strength") {
            object = new Scroll("scroll of strength");
            objects.push_back(object);
        } else if (objectType == "scroll of enhance health") {
            object = new Scroll("scroll of enhance health");
            objects.push_back(object);
        } else if (objectType == "scroll of enhance dexterity") {
            object = new Scroll("scroll of enhance dexterity");
            objects.push_back(object);
        }
    }
}

// set the positions of the GameObjects (at the start of the level)
void Temple::setGameObjectSpawn() {
    for (size_t i = 0; i < objects.size(); i++) {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!validMove(x, y)) {
            x = randInt(1,69);
            y = randInt(1, 17);
        }
        objects[i]->setXPos(x);
        objects[i]->setYPos(y);
        
        if (objects[i]->getName() == "scroll of teleportation" || objects[i]->getName() == "scroll of armor" || objects[i]->getName() == "scroll of strength" || objects[i]->getName() == "scroll of enhance health" || objects[i]->getName() == "scroll of enhance dexterity") {
            m_map[objects[i]->getYPos()][objects[i]->getXPos()] = '?';
        } else {
            m_map[objects[i]->getYPos()][objects[i]->getXPos()] = '(';
        }
    }
}


// check if there is an object on the same position of an actor (to be able to 'g' command it into the inventory) 
bool Temple::checkForObjects() {
    for (size_t i = 0; i < objects.size(); i++) {
        if (player->getXPos() == objects[i]->getXPos() && player->getYPos() == objects[i]->getYPos()) {
            player->pickUpObject(objects[i]);
            objects.erase(objects.begin() + i);
            return true; 
        }
    }
    return false; 
}

// check the position of each object in the inventory
bool Temple::isObjectAt(int x, int y) {
    for (size_t i = 0; i < objects.size(); i++) {
        if (objects[i]->getXPos() == x && objects[i]->getYPos() == y) {
            return true;
        }
    }
    return false;
}



bool Temple::isMonsterAt(int x, int y) {
    for (size_t i = 0; i < monsters.size(); i++) {
        if (monsters[i]->getXPos() == x && monsters[i]->getYPos() == y) {
            return true;
        }
    }
    return false;
}

Monster* Temple::getMonsterAt(int x, int y) {
    for (size_t i = 0; i < monsters.size(); i++) {
        if (monsters[i]->getXPos() == x && monsters[i]->getYPos() == y) {
            return monsters[i];
        }
    }
    return nullptr;
}

void Temple::attack(Actor* attacker, Actor* defender, Weapon weapon) {
    int attackerPoints = attacker->getDexterity() + weapon.getDexterityBonus();
    int defenderPoints = defender->getDexterity() + defender->getArmor();
    cout << "attackerPoints: " << attackerPoints << endl;
    cout << "defenderPoints: " << defenderPoints << endl;
 
    bool hit = false;
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damageAmount = randInt(0, attacker->getStrength() + weapon.getDamage() - 1);
        cout << "damage amount: " << damageAmount << endl;
        defender->setHP(-damageAmount);
        hit = true;
    }
    
    string result;
    string attackerName = attacker->getName();
    string weaponAction = weapon.getAction();
    string weaponName = weapon.getName();
    string defenderName = defender->getName();
    if (hit) {
        if (defender->getHP() <= 0) {
            attacks.push_back(attackerName + " " + weaponAction + " " + weaponName + " at " + defenderName + "dealing a final blow.");
            return;
        } else {
            result = "hits";
        }
    } else {
        result = "misses";
    }
    attacks.push_back(attackerName +  " " + weaponAction + " " + weaponName + " at " + defenderName + " and " + result);
}

void Temple::printActions() {
    for (size_t i = 0; i < attacks.size(); i++) {
        cout << attacks[i] << endl;
        attacks.erase(attacks.begin());
    }
}

