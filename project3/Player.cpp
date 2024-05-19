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

Player::Player() : Actor(0, 0, 20, 2, 2, 2) {}

void Player::setHP(int n) {
    if (getHP() + n <= m_maxHP) {
        Actor::setHP(n);
    }
}

void Player::playerMaxHP(int n) {
    m_maxHP = getHP() + n;
}
