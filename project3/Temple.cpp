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

// create temple
Temple::Temple(Player* pointer) : player(pointer), m_level(0) {
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

// see if the move is valid
bool Temple::validMove(int xPos, int yPos) {
    if (m_map[yPos][xPos] == '#') {
        return false;
    }
    if ( m_map[yPos][xPos] == '@' || m_map[yPos][xPos] == 'B' || m_map[yPos][xPos] == 'D' || m_map[yPos][xPos] == 'G' || m_map[yPos][xPos] == 'S') {
        return false;
    }
    return true;
}

// move the player based on a command
void Temple::movePlayer(char c) {
    m_map[player->getYPos()][player->getXPos()] = ' ';
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
    cout << player->getXPos() << " " << player->getYPos() << endl;
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
    for (int i = 0; i < monsters.size(); i++) {
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

void Temple::setGameObject() {
    int num = randInt(2, 3);
    vector<string> objectTypes = {
            "mace", "short sword", "long sword",
            "armor", "strength",
            "health", "dexterity"
        };

    for (int i = 0; i < num; i++) {
        int randIndex = randInt(0, 7);
        string objectType = objectTypes[randIndex];
        
        GameObject* object = nullptr;
        if (objectType == "mace") {
            object = new Weapon("mace", 0, 2);
            objects.push_back(object);
        } else if (objectType == "short sword") {
            object = new Weapon("short sword", 0, 2);
            objects.push_back(object);
        } else if (objectType == "long sword") {
            object = new Weapon("long sword", 2, 4);
            objects.push_back(object);
        } else if (objectType == "armor") {
            object = new Scroll("armor");
            objects.push_back(object);
        } else if (objectType == "strength") {
            object = new Scroll("strength");
            objects.push_back(object);
        } else if (objectType == "health") {
            object = new Scroll("health");
            objects.push_back(object);
        } else if (objectType == "dexterity") {
            object = new Scroll("dexterity");
            objects.push_back(object);
        }
    }
}

void Temple::setGameObjectSpawn() {
    for (int i = 0; i < objects.size(); i++) {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!validMove(x, y)) {
            x = randInt(1,69);
            y = randInt(1, 17);
        }
        objects[i]->setXPos(x);
        objects[i]->setYPos(y);
        m_map[objects[i]->getYPos()][objects[i]->getXPos()] = '(';
    }
}
// sometimes do not have any objects

// apply scroll effect
void Temple::applyScroll(GameObject* scroll) {
    // teleportation object
    if (scroll->getName() == "teleportation") {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!validMove(x, y)) {
            x = randInt(1,69);
            y = randInt(1, 17);
        }
        player->setXPos(x);
        player->setYPos(y);
    } else if (scroll->getName() == "armor") {
        player->setArmor(randInt(1, 3));
    } else if (scroll->getName() == "strength") {
        player->setStrength(randInt(1, 3));
    } else if (scroll->getName() == "health") {
        player->playerMaxHP(randInt(3, 8));
    } else if (scroll->getName() == "dexterity") {
        player->setDexterity(1); 
    }
}
