//
//  Player.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Player.h"
#include "Temple.h"
#include "utilities.h"

Player::Player() : Actor(randInt(1, 17), randInt(1, 69), 20, 2, 2, 2) {}

void Player::setXPos(Temple board, char c) {
    if (board.validMove(getXPos(), getYPos())) {
        switch (c) {
            case ARROW_RIGHT:
                Actor::setXPos(1);
            case ARROW_LEFT:
                Actor::setXPos(-1);
        }
    }
}

void Player::setYPos(Temple board, char c) {
    if (board.validMove(getXPos(), getYPos())) {
        switch (c) {
            case ARROW_UP:
                Actor::setYPos(1);
            case ARROW_RIGHT:
                Actor::setYPos(-1);
        }
    }
}
