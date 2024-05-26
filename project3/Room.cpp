//
//  Room.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/25/24.
//

#include "Room.h"

Room::Room(int xPos, int yPos, int width, int height) : m_x(xPos), m_y(yPos), m_width(width), m_height(height) {}

// getters
int Room::getX() {
    return m_x;
}

int Room::getY() {
    return m_y;
}

int Room::getWidth() {
    return m_width;
}

int Room::getHeight() {
    return m_height; 
}

