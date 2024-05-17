//
//  Temple.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#ifndef Temple_h
#define Temple_h

class Player;

class Temple {
public:
    Temple(Player* pointer);
    void printMap();
    void move();
    bool validMove(int xPos, int yPos);
    void setPlayer(int x, int y); 
private:
    char m_map[18][70];
    int m_level;
    Player* player;
};

#endif /* Temple_h */
