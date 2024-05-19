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
#include <vector>

#include "GameObject.h"

class Temple;

class Player : public Actor {
public:
    Player();
    virtual ~Player();
    
    virtual void setHP(int n); 
    void playerMaxHP(int n);
    
    // player actions
    void pickUpObject(GameObject* object);
    void swapWeapons();
    void activateScroll();
    
    // inventory stuff
    void printInventory();
    
private:
    int m_maxHP; 
    vector<GameObject*> inventory;
    
};

#endif /* Player_h */
