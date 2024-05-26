//
//  Room.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/25/24.
//

#ifndef Room_h
#define Room_h

class Room {
public:
    Room(int xPos, int yPos, int width, int height);
    
    // getters
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    
private:
    int m_width;
    int m_height;
    // (m_x, m_y) represents the top left corner of the room
    int m_x;
    int m_y;
};

#endif /* Room_h */
