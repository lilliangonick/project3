//
//  Temple.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Temple.h"
#include "Player.h"
#include "utilities.h"
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
    m_map[y][x] = '@';
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
    if (m_map[yPos][xPos] == '#') {
        return false;
    }
    return true;
}

//bool Temple::validMoveChar(char c) {
//    switch (c) {
//        case ARROW_LEFT:
//            if (validMove(player->getXPos() - 1, player->getYPos())) return true;
//            else {
//                
//                cout << player->getXPos() - 1 << " " << player->getYPos();
//                return false;
//            };
//        case ARROW_RIGHT:
//            if (validMove(player->getXPos() + 1, player->getYPos())) return true;
//            else {
//                
//                cout << player->getXPos() + 1 << " " << player->getYPos();
//                return false;
//            };
//        case ARROW_UP:
//            if (validMove(player->getXPos(), player->getYPos()) - 1) return true;
//            else {
//                
//                cout << player->getXPos() << " " << player->getYPos() - 1;
//                return false;
//            };
//        case ARROW_DOWN:
//            if (validMove(player->getXPos(), player->getYPos()) + 1) return true;
//            else {
//                
//                cout << player->getXPos() << " " << player->getYPos() + 1;
//                return false;
//            };
//        default:
//            cout << "WHY ARE U HERE";
//            return false;
//    }
//}

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
