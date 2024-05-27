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

class Player : public Actor {
public:
    Player();
    virtual ~Player();
    
    // players can increase their max HP
    virtual void setHP(int n);
    void playerMaxHP(int n);
    int getMaxHP();
    
    
    void regainHP();
    
    // player can cheat
    void cheat();
    
private:
    int m_maxHP; 
};

#endif /* Player_h */
