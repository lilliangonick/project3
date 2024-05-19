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

class Temple;

class Player : public Actor {
public:
    Player();
    
    virtual void setHP(int n); 
    void playerMaxHP(int n);
    
    // player actions
    void pickUpObject();
    void swapWeapons();
    void activateScroll();
    void seeInventory();
    
private:
    int m_maxHP; 
    // vector for the inventory
    
};

#endif /* Player_h */
