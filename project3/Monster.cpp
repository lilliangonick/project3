//
//  Monster.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/18/24.
//

#include "Monster.h"
#include "Temple.h"
#include "utilities.h"

Monster::Monster(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity) : Actor(name, 0, 0, hit, weaponName, actionString, dexterityBonus, damage, armor, strength, dexterity) {}

// virtual destructor for Monster base class
Monster::~Monster() {}

Bogeyman::Bogeyman() : Monster("the Bogeyman", 0, 0, randInt(5, 10), "short sword", "slashes", 0, 2, randInt(2, 3), randInt(2, 3), 2) {}

Snakewoman::Snakewoman() : Monster("the Snakewoman", 0, 0, randInt(3, 6), "magic fangs of sleep", "strikes", 3, 2, 3, 2, 3) {}

Dragon::Dragon() : Monster("the Dragon", 0, 0, randInt(20, 25), "long sword", "swings", 2, 4, 4, 4, 4) {}

Goblin::Goblin() : Monster("the Goblin", 0, 0, randInt(15, 20), "short sword", "slashes", 0, 2, 1, 3, 1) {}
