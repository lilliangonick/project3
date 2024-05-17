//
//  Temple.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Temple.h"
#include "Player.h"
#include <iostream>

Temple::Temple(Player* pointer) : player(pointer) {
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

void Temple::setPlayer(int x, int y) {
    m_map[x][y] = '@';
}

void Temple::printMap() {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            std::cout << m_map[i][j];
        }
        std::cout << std::endl;
    }
}

bool Temple::validMove(int xPos, int yPos) {
    if (m_map[xPos][yPos] == '#') {
        return false;
    }
    return true;
}
