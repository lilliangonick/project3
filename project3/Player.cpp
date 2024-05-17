//
//  Player.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Player.h"
#include "Temple.h"
#include "utilities.h"

Player::Player() : Actor(0, 0, 20, 2, 2, 2) {}
//spawning on border
void Player::setSpawn(Temple board) {
    int x = randInt(1, 69);
    int y = randInt(1, 17);
    while (!board.validMove(x, y)) {
        x = randInt(1,69);
        y = randInt(1, 17);
    }
    Actor::setXPos(x);
    Actor::setYPos(y); 
}
