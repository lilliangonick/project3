//
//  Monster.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/18/24.
//

#include "Monster.h"
#include "Temple.h"
#include "utilities.h"
#include <cmath>
#include <vector>

using namespace std;

Monster::Monster(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity, int smellRange) : Actor(name, xPos, yPos, hit, weaponName, actionString, dexterityBonus, damage, armor, strength, dexterity, true), m_smellRange(smellRange), m_isDead(false) {}

// virtual destructor for Monster base class
Monster::~Monster() {}

bool Monster::shouldDrop() {
    return false;
}

GameObject* Monster::dropNewItem() {
    return nullptr; 
}

// get the smell range
int Monster::getSmellRange() {
    return m_smellRange;
}


bool Monster::smell(Player* player) {
    int playerXPos = player->getXPos();
    int playerYPos = player->getYPos();
    int monsterXPos = getXPos();
    int monsterYPos = getYPos();
    
    int distanceFromPlayer = abs(playerXPos - monsterXPos) + abs(playerYPos - monsterYPos);
    
    return distanceFromPlayer <= getSmellRange();
}

Bogeyman::Bogeyman(int smellRange) : Monster("the Bogeyman", 0, 0, randInt(5, 10), "short sword", "slashes", 0, 2, randInt(2, 3), randInt(2, 3), 2, smellRange) {}

bool Bogeyman::shouldDrop() {
    if (trueWithProbability(0.1)) {
        return true;
    } else {
        return false;
    }
}

GameObject* Bogeyman::dropNewItem() {
    return new Weapon("magic axe", "chops", 5, 5);
}

Snakewoman::Snakewoman(int smellRange) : Monster("the Snakewoman", 0, 0, randInt(3, 6), "magic fangs", "strikes", 3, 2, 3, 2, 3, smellRange) {}

bool Snakewoman::shouldDrop() {
    if (trueWithProbability(1.0/3.0)) {
        return true;
    } else {
        return false;
    }
}

GameObject* Snakewoman::dropNewItem() {
    return new Weapon("magic fangs", "strikes", 3, 2);
}

Dragon::Dragon(int smellRange) : Monster("the Dragon", 0, 0, randInt(20, 25), "long sword", "swings", 2, 4, 4, 4, 4, smellRange) {}

bool Dragon::shouldDrop() {
    return true;
}

GameObject* Dragon::dropNewItem() {
    int randomScroll = randInt(1, 5);
    if (randomScroll == 1) {
        return new Scroll("scroll of teleportation");
    } else if (randomScroll == 2) {
        return new Scroll("scroll of enhance armor");
    } else if (randomScroll == 3) {
        return new Scroll("scroll of strength");
    } else if (randomScroll == 4) {
        return new Scroll("scroll of enhance health");
    } else {
        return new Scroll("scroll of enhance dexterity");
    }
}

Goblin::Goblin(int smellRange) : Monster("the Goblin", 0, 0, randInt(15, 20), "short sword", "slashes", 0, 2, 1, 3, 1, smellRange) {}

bool Goblin::shouldDrop() {
    if (trueWithProbability(1.0/3.0)) {
        return true;
    } else {
        return false; 
    }
}

GameObject* Goblin::dropNewItem() {
    int randomObject = randInt(1, 2);
    if (randomObject == 1) {
        return new Weapon("magic axe", "chops", 5, 5);
    } else {
        return new Weapon("magic fangs", "strikes", 3, 2);
    }
}

//bool Goblin::smell(Player* player, int smellRange) {
//    int playerXPos = player->getXPos();
//    int playerYPos = player->getYPos();
//    int goblinXPos = getXPos();
//    int goblinYPos = getYPos();
//    
//    int distanceFromPlayer = abs(playerXPos - goblinXPos) + abs(playerYPos - goblinYPos);
//    
//    // if goblin is right next to (base case)
//    if (distanceFromPlayer <= getSmellRange()) {
//        if (goblinXPos + 1 == playerXPos && goblinYPos == playerYPos) {
//            return true;
//        } else if (goblinXPos - 1 == playerXPos && goblinYPos == playerYPos) {
//            return true;
//        } else if (goblinXPos == playerXPos && goblinYPos + 1 == playerYPos) {
//            return true;
//        } else if (goblinXPos == playerXPos && goblinYPos - 1== playerYPos) {
//            return true;
//        }
//        
//        // recursive step
//        if (goblinXPos + 1 != playerXPos && smell(player, smellRange - 1)) {
//            return true;
//        }
//        if (goblinXPos - 1 != playerXPos && smell(player, smellRange - 1)) {
//            return true;
//        }
//        if (goblinYPos + 1 != playerYPos && smell(player, smellRange - 1)) {
//            return true;
//        }
//        if (goblinYPos - 1 != playerYPos && smell(player, smellRange - 1)) {
//            return true;
//        }
//    }
//    return false; 
//}

bool Goblin::smell(Player* player, int smellRange) {
    int playerXPos = player->getXPos();
    int playerYPos = player->getYPos();
    int goblinXPos = getXPos();
    int goblinYPos = getYPos();

    int distanceFromPlayer = abs(playerXPos - goblinXPos) + abs(playerYPos - goblinYPos);

    // if goblin is right next to (base case)
    if (distanceFromPlayer <= getSmellRange()) {
        if (goblinXPos + 1 == playerXPos && goblinYPos == playerYPos) {
            return true;
        } else if (goblinXPos - 1 == playerXPos && goblinYPos == playerYPos) {
            return true;
        } else if (goblinXPos == playerXPos && goblinYPos + 1 == playerYPos) {
            return true;
        } else if (goblinXPos == playerXPos && goblinYPos - 1 == playerYPos) {
            return true;
        }

        // recursive step
        if (goblinXPos + 1 != playerXPos && smell(player, smellRange - 1)) {
            return true;
        }
        if (goblinXPos - 1 != playerXPos && smell(player, smellRange - 1)) {
            return true;
        }
        if (goblinYPos + 1 != playerYPos && smell(player, smellRange - 1)) {
            return true;
        }
        if (goblinYPos - 1 != playerYPos && smell(player, smellRange - 1)) {
            return true;
        }
    }
    return false;
}
