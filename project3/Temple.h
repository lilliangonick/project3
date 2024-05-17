//
//  Temple.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#ifndef Temple_h
#define Temple_h

class Temple {
public:
    Temple();
    void printMap();
    void move();
    bool validMove(int xPos, int yPos); 
private:
    char m_map[18][70];
    int m_level;
};

#endif /* Temple_h */
