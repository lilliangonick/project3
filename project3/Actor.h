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
    Actor(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity, bool isMonster);
    virtual ~Actor(); 
    
    // get actor attributes
    int getXPos();
    int getYPos();
    int getHP();
    int getArmor();
    int getStrength();
    int getDexterity();
    int getSleepTime();
    Weapon getWeapon();
    string getName();
    
    // set actor attributes
    virtual void setXPos(int n);
    virtual void setYPos(int n);
    virtual void setHP(int n);
    void setArmor(int n);
    void setStrength(int n);
    void setDexterity(int n);
    void setSleepTime(int n);
    void setWeapon(Weapon weapon);
    void CHANGESTRENGTH(int n);
    
    bool isMonster(); 
    
    // deal with sleeping functionality
    bool isSleeping();
    
private:
    string m_name;
    int m_x;
    int m_y;
    int m_hit; // int 0 - 99
    Weapon m_weapon;
    string weaponName;
    string actionString;
    int dexterityBonus;
    int damage;
    int m_armor; // int 0 - 99
    int m_strength; // int 0 - 99
    int m_dexterity; // int 0 - 99
    int m_sleepTime;  // int 0 - 9
    bool m_isMonster;

};


#endif /* Actor_h */
