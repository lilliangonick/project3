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

class Actor {
public:
    Actor(int x_Pos, int yPos, int hit, int armor, int strength, int dexterity);
    
    virtual void move(); // all actors move the same (except the dragon)
    virtual void attack();
    
    // get actor attributes
    virtual int getHP();
    virtual int getArmor();
    virtual int getStrength();
    virtual int getDexterity();
    virtual int getSleepTime();
    
    // set actor attributes
    virtual void setHP(int n);
    virtual void setArmor(int n);
    virtual void setStrength(int n);
    virtual void setDexterity(int n);
    virtual void setSleepTime(int n);
    
    // display messages after actor action
    virtual void attackResult(); // all actors can attack
    
private:
    int m_x;
    int m_y;
    // member variable for current weapon (of type game object)
    int m_hit; // int 0 - 99
    int m_armor; // int 0 - 99
    int m_strength; // int 0 - 99
    int m_dexterity; // int 0 - 99
    int m_sleepTime;  // int 0 - 9

};

class Player : public Actor {
public:
    Player();
    virtual void move();
    
    // player actions
    void pickUpObject();
    void swapWeapons();
    void activateScroll();
    void seeInventory();
    
private:
    // vector for the inventory
    
};

class Monster : public Actor {
public:
    Monster();
    virtual void handleTurn() const = 0; // ABC
    // drop an item on death
};

class Bogeyman : public Monster {
public:
    Bogeyman();
    void smell();
    // 1/10 chance magic axe drop
};

class Snakewoman : public Monster {
public:
    Snakewoman();
    void smell();
    // 1/3 chance fangs drop
};

class Dragon : public Monster {
public:
    Dragon();
    void heal();
    // drop scroll
};

class Goblin : public Monster {
public:
    Goblin();
    void smell();
    // 1/3 chance fangs/axe drop
};

#endif /* Actor_h */
