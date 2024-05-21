//
//  Monster.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/18/24.
//

#ifndef Monster_h
#define Monster_h

#include "Actor.h"
#include <string>

#include "Player.h"

class Monster : public Actor {
public:
    Monster(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity, int smellRange);
    virtual ~Monster();
    
    virtual bool smell(Player* player);
    int getSmellRange();

    
private:
    bool m_isDead; 
    
private:
    int m_smellRange;
};

class Bogeyman : public Monster {
public:
    Bogeyman(int smellRange);
};

class Snakewoman : public Monster {
public:
    Snakewoman(int smellRange);
};

class Dragon : public Monster {
public:
    Dragon(int smellRange);
    void heal();
};

class Goblin : public Monster {
public:
    Goblin(int smellRange);
    virtual bool smell(Player* player, int smellRange);
};

#endif /* Monster_h */
