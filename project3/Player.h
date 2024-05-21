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
    
    // players can increase their max HP
    virtual void setHP(int n);
    void playerMaxHP(int n);
    
    // player actions
    void pickUpObject(GameObject* object);
    void applyScroll(GameObject* scroll);
    
    void weildWeapon();
    void readScroll();
    
    void regainHP();
    
    // inventory stuff
    void printInventory();
    void printInventoryResult();
    vector<string> getInventoryResults();
    
    // player can cheat
    void cheat();
    
private:
    int m_maxHP; 
    vector<GameObject*> inventory;
    vector<string> inventoryResult;
    
};

#endif /* Player_h */
