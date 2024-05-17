//
//  Player.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#ifndef Player_h
#define Player_h

#include "Actor.h"
#include "Temple.h"

class Player : public Actor {
public:
    Player();
    void move();
    
    virtual void setXPos(Temple board, char c);
    virtual void setYPos(Temple board, char c);
    
    // player actions
    void pickUpObject();
    void swapWeapons();
    void activateScroll();
    void seeInventory();
    
private:
    // vector for the inventory
    
};

#endif /* Player_h */
