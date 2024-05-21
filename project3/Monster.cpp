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

using namespace std;

Monster::Monster(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity, int smellRange) : Actor(name, 0, 0, hit, weaponName, actionString, dexterityBonus, damage, armor, strength, dexterity, true), m_smellRange(smellRange), m_isDead(false) {}

// virtual destructor for Monster base class
Monster::~Monster() {}

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

Snakewoman::Snakewoman(int smellRange) : Monster("the Snakewoman", 0, 0, randInt(3, 6), "magic fangs of sleep", "strikes", 3, 2, 3, 2, 3, smellRange) {}

Dragon::Dragon(int smellRange) : Monster("the Dragon", 0, 0, randInt(20, 25), "long sword", "swings", 2, 4, 4, 4, 4, smellRange) {}

Goblin::Goblin(int smellRange) : Monster("the Goblin", 0, 0, randInt(15, 20), "short sword", "slashes", 0, 2, 1, 3, 1, smellRange) {}
