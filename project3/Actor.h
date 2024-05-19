//
//  Header.h
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#ifndef Actor_h
#define Actor_h

#include <vector>
#include <string>
using namespace std;

#include "GameObject.h"

class Actor {
public:
    Actor(int xPos, int yPos, int hit, int armor, int strength, int dexterity);
    
    // get actor attributes
    int getXPos();
    int getYPos();
    int getHP();
    int getArmor();
    int getStrength();
    int getDexterity();
    int getSleepTime();
    
    // set actor attributes
    virtual void setXPos(int n);
    virtual void setYPos(int n);
    virtual void setHP(int n);
    void setArmor(int n);
    void setStrength(int n);
    void setDexterity(int n);
    void setSleepTime(int n);
    
    
    // display messages after actor action
    void attackResult(); // all actors can attack
    
    bool isDead(); // initially false 
    
private:
    int m_x;
    int m_y;
//    GameObject weapon;
    int m_hit; // int 0 - 99
    int m_armor; // int 0 - 99
    int m_strength; // int 0 - 99
    int m_dexterity; // int 0 - 99
    int m_sleepTime;  // int 0 - 9

};


#endif /* Actor_h */
