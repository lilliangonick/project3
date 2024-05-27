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

class Temple;

// constructor
Player::Player() : Actor("Player", 0, 0, 20, "short sword", "slashes", 0, 2, 2, 2, 2, false), m_maxHP(20) {}

// destructor
Player::~Player() {}
// set PlayerHP
void Player::setHP(int n) {
    if (getHP() + n <= m_maxHP) {
        Actor::setHP(n);
    }
}

// determine what the max HP is for a player
void Player::playerMaxHP(int n) {
    m_maxHP = getHP() + n;
}

int Player::getMaxHP() {
    return m_maxHP;
}

// cheat by clicking the c command
void Player::cheat() {
    CHANGESTRENGTH(9);
    m_maxHP = 50;
    CHANGEHITPOINT(50);
    
}

void Player::regainHP() {
    if (trueWithProbability(0.1)) {
        Player::setHP(1);
    }
}

bool Actor::shouldDrop() {
    return false;
}

GameObject* Actor::dropNewItem() {
    return nullptr;
}


