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
#include <algorithm>

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
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        delete *it;
    }
    for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        delete *it;
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

void Temple::printActions() {
    vector<string>::iterator it = attacks.begin();
    for (; it != attacks.end(); ++it) {
        cout << *it << endl;
    }
    // erase all attacks up to the last index printed
    attacks.erase(attacks.begin(), it);
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
    return true;
}

// see if the move is valid
bool Temple::validMonsterMove(int xPos, int yPos) {
    if (m_map[yPos][xPos] == '#' || m_map[yPos][xPos] == 'B' || m_map[yPos][xPos] == 'S' || m_map[yPos][xPos] == 'D' || m_map[yPos][xPos] == 'G') {
        return false;
    }
    return true;
}

// move the player based on a command
void Temple::movePlayer(char c) {
    m_justAttacked = false;
    int newX = player->getXPos();
    int newY = player->getYPos();

    // determine the new position based on the direction
    if (c == ARROW_LEFT) {
        newX -= 1;
    } else if (c == ARROW_RIGHT) {
        newX += 1;
    } else if (c == ARROW_UP) {
        newY -= 1;
    } else if (c == ARROW_DOWN) {
        newY += 1;
    }
    
    // check if there is a monster at the new position
    if (isMonsterAt(newX, newY)) {
        Monster* monster = getMonsterAt(newX, newY);
        attack(player, monster, player->getWeapon());
        // If the monster is dead, remove it from the map and the monsters list
        if (monster->getHP() <= 0) {
            m_map[monster->getYPos()][monster->getXPos()] = ' ';
        }
        m_justAttacked = true;
        return; // do not move the player
    }
    
    m_map[player->getYPos()][player->getXPos()] = ' ';
    if (isObjectAt(player->getXPos(), player->getYPos())) {
        for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            if ((*it)->getXPos() == player->getXPos() && (*it)->getYPos() == player->getYPos()) {
                if ((*it)->getType() == "Scroll") {
                    m_map[(*it)->getYPos()][(*it)->getXPos()] = '?';
                } else {
                    m_map[(*it)->getYPos()][(*it)->getXPos()] = '(';
                }
            }
        }
    }
    
    // Move the player to the new position
    player->Actor::setXPos(newX);
    player->Actor::setYPos(newY);
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
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!validMove(x, y)) {
            x = randInt(1, 69);
            y = randInt(1, 17);
        }
        (*it)->setXPos(x);
        (*it)->setYPos(y);
        Monster& monster = **it;  // Dereference the iterator and the pointer
        if (typeid(monster) == typeid(Snakewoman)) {
            m_map[monster.getYPos()][monster.getXPos()] = 'S';
        } else if (typeid(monster) == typeid(Goblin)) {
            m_map[monster.getYPos()][monster.getXPos()] = 'G';
        } else if (typeid(monster) == typeid(Bogeyman)) {
            m_map[monster.getYPos()][monster.getXPos()] = 'B';
        } else if (typeid(monster) == typeid(Dragon)) {
            m_map[monster.getYPos()][monster.getXPos()] = 'D';
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
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(15);
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 1) {
        m = randInt(2, 5*(0+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 1);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(15);
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 2) {
        m = randInt(2, 5*(2+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 2);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(15);
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman(5);
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 3) {
        m = randInt(2, 5*(3+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 3);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(15);
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman(5);
                    monsters.push_back(monster);
                } else if (rand == 3) {
                    monster = new Dragon(0);
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 4) {
        m = randInt(2, 5*(4+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 3);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(15);
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman(5);
                    monsters.push_back(monster);
                } else if (rand == 3) {
                    monster = new Dragon(0);
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
    for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!validMove(x, y)) {
            x = randInt(1, 69);
            y = randInt(1, 17);
        }
        (*it)->setXPos(x);
        (*it)->setYPos(y);

        if ((*it)->getName() == "scroll of teleportation" || (*it)->getName() == "scroll of armor" || (*it)->getName() == "scroll of strength" || (*it)->getName() == "scroll of enhance health" || (*it)->getName() == "scroll of enhance dexterity") {
            m_map[(*it)->getYPos()][(*it)->getXPos()] = '?';
        } else {
            m_map[(*it)->getYPos()][(*it)->getXPos()] = '(';
        }
    }
}


// check if there is an object on the same position of an actor (to be able to 'g' command it into the inventory) 
bool Temple::checkForObjects() {
    for (auto it = objects.begin(); it != objects.end(); ++it) {
        if (player->getXPos() == (*it)->getXPos() && player->getYPos() == (*it)->getYPos()) {
            player->pickUpObject(*it);
            objects.erase(it);
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


// check if there is monster where the player wants to go
bool Temple::isMonsterAt(int x, int y) {
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        if ((*it)->getXPos() == x && (*it)->getYPos() == y) {
            return true;
        }
    }
    return false;
}

// if there is a monster where the player wants to move, return a pointer to that monster
Monster* Temple::getMonsterAt(int x, int y) {
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        if ((*it)->getXPos() == x && (*it)->getYPos() == y) {
            return *it;
        }
    }
    return nullptr;
}

// let one actor attack another
void Temple::attack(Actor* attacker, Actor* defender, Weapon weapon) {
    int attackerPoints = attacker->getDexterity() + weapon.getDexterityBonus();
    int defenderPoints = defender->getDexterity() + defender->getArmor();
 
    bool hit = false;
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damageAmount = randInt(0, attacker->getStrength() + weapon.getDamage() - 1);
        defender->setHP(-damageAmount);
        hit = true;
    }
    
    string result;
    string attackerName = attacker->getName();
    string weaponAction = weapon.getAction();
    string weaponName = weapon.getName();
    string defenderName = defender->getName();
    
    if (defender->getHP() <= 0) {
        attacks.push_back(attackerName + " " + weaponAction + " " + weaponName + " at " + defenderName + " dealing a final blow.");
        if (defender->isMonster()) {
            vector<Monster*>::iterator it = find(monsters.begin(), monsters.end(), defender);
            if (it != monsters.end()) {
                delete *it;
                monsters.erase(it);
            }
        }
        return;
    }
    
    if (hit) {
        result = "hits";
    } else {
        result = "misses";
    }
    attacks.push_back(attackerName +  " " + weaponAction + " " + weaponName + " at " + defenderName + " and " + result);
}

// move the monsters based on the position of the player
void Temple::moveMonsters() {
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        // move the bogeyman
        if ((*it)->getName() == "the Bogeyman") {
            if ((*it)->smell(player)) {
                moveTowardsPlayer(*it, 'B');
            }
        } else if ((*it)->getName() == "the Snakewoman") {
            if ((*it)->smell(player)) {
                moveTowardsPlayer(*it, 'S');
            }
        } else if ((*it)->getName() == "the Dragon") {
            // dragos have a 1/10 chance of healing
            if (trueWithProbability(0.1)) {
                cout << "dragaon healed" << endl;
                ((*it))->setHP(1);
            }
            
            // if the monster is already next to the player, attack directly
            if ((*it)->getXPos() + 1 == player->getXPos() && (*it)->getYPos() == player->getYPos()) {
                attack((*it), player, (*it)->getWeapon());
                m_justAttacked = true;
                return;
            } else if ((*it)->getXPos() - 1 == player->getXPos() && (*it)->getYPos() == player->getYPos()) {
                attack((*it), player, (*it)->getWeapon());
                m_justAttacked = true;
                return;
            } else if ((*it)->getXPos() == player->getXPos() && (*it)->getYPos() + 1 == player->getYPos()) {
                attack((*it), player, (*it)->getWeapon());
                m_justAttacked = true;
                return;
            } else if ((*it)->getXPos() == player->getXPos() && (*it)->getYPos() - 1 == player->getYPos()) {
                attack((*it), player, (*it)->getWeapon());
                m_justAttacked = true;
                return;
            }
        } else if ((*it)->getName() == "the Goblin") {
            if ((*it)->smell(player)) {
                moveTowardsPlayer(*it, 'G');
            }
        }
    }
}

// calculate which step to move towars the player
void Temple::moveTowardsPlayer(Monster* monster, char monsterChar) {
    m_justAttacked = false;
    int playerXPos = player->getXPos();
    int playerYPos = player->getYPos();
    int monsterXPos = monster->getXPos();
    int monsterYPos = monster->getYPos();
    
    // if the monster is already next to the player, attack directly
    if (monsterXPos + 1 == playerXPos && monsterYPos == playerYPos) {
        attack(monster, player, monster->getWeapon());
        m_justAttacked = true;
        return;
    } else if (monsterXPos - 1 == playerXPos && monsterYPos == playerYPos) {
        attack(monster, player, monster->getWeapon());
        m_justAttacked = true;
        return;
    } else if (monsterXPos == playerXPos && monsterYPos + 1 == playerYPos) {
        attack(monster, player, monster->getWeapon());
        m_justAttacked = true;
        return;
    } else if (monsterXPos == playerXPos && monsterYPos - 1 == playerYPos) {
        attack(monster, player, monster->getWeapon());
        m_justAttacked = true;
        return;
    }
    

    // variables to store new position
    int newMonsterXPos = monsterXPos;
    int newMonsterYPos = monsterYPos;

    if (playerXPos > monsterXPos && validMonsterMove(monsterXPos + 1, monsterYPos)) {
        newMonsterXPos = monsterXPos + 1;
    } else if (playerXPos < monsterXPos && validMonsterMove(monsterXPos - 1, monsterYPos)) {
        newMonsterXPos = monsterXPos - 1;
    } else if (playerYPos > monsterYPos && validMonsterMove(monsterXPos, monsterYPos + 1)) {
        newMonsterYPos = monsterYPos + 1;
    } else if (playerYPos < monsterYPos && validMonsterMove(monsterXPos, monsterYPos - 1)) {
        newMonsterYPos = monsterYPos - 1;
    }
 
    m_map[monsterYPos][monsterXPos] = ' '; // clear the old position
    
    // make sure player movement does not overwrite the objects
    if (isObjectAt(monster->getXPos(), monster->getYPos())) {
        for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            if ((*it)->getXPos() == monster->getXPos() && (*it)->getYPos() == monster->getYPos()) {
                if ((*it)->getType() == "Scroll") {
                    m_map[(*it)->getYPos()][(*it)->getXPos()] = '?';
                } else {
                    m_map[(*it)->getYPos()][(*it)->getXPos()] = '(';
                }
            }
        }
    }
    m_map[newMonsterYPos][newMonsterXPos] = monsterChar; // set the new position
    monster->setXPos(newMonsterXPos);
    monster->setYPos(newMonsterYPos);
    
    
}

