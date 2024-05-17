//
//  Player.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#ifndef Player_h
#define Player_h

#include "Actor.h"
 

class Player : public Actor {
public:
    Player();
    void move();
    
    // player actions
    void pickUpObject();
    void swapWeapons();
    void activateScroll();
    void seeInventory();
    
private:
    // vector for the inventory
    
};

#endif /* Player_h */
