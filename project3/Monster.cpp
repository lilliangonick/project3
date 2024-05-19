//
//  Monster.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/18/24.
//

#include "Monster.h"
#include "Temple.h"
#include "utilities.h"

Monster::Monster(int xPos, int yPos, int hit, int armor, int strength, int dexterity) : Actor(0, 0, hit, armor, strength, dexterity) {}

//spawning on border
void Monster::setMonsterSpawn(Temple board) {
    int x = randInt(1, 69);
    int y = randInt(1, 17);
    while (!board.validMove(x, y)) {
        x = randInt(1,69);
        y = randInt(1, 17);
    }
    Actor::setXPos(x);
    Actor::setYPos(y);
}

Bogeyman::Bogeyman() : Monster(0, 0, randInt(5, 11), randInt(2, 4), randInt(2, 4), 2) {}

Snakewoman::Snakewoman() : Monster(0, 0, randInt(3, 7), 3, 2, 3) {}

Dragon::Dragon() : Monster(0, 0, randInt(20, 26), 4, 4, 4) {}

Goblin::Goblin() : Monster(0, 0, randInt(15, 21), 1, 3, 1) {}
