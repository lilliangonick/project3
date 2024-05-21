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
    
    bool smell(Player* player);
    int getSmellRange();
private:
    bool m_isDead; 
    
private:
    int m_smellRange;
};

class Bogeyman : public Monster {
public:
    Bogeyman(int smellRange);
    // 1/10 chance magic axe drop
};

class Snakewoman : public Monster {
public:
    Snakewoman(int smellRange);
    // 1/3 chance fangs drop
};

class Dragon : public Monster {
public:
    Dragon(int smellRange);
    void heal();
    // drop scroll
};

class Goblin : public Monster {
public:
    Goblin(int smellRange);
    // 1/3 chance fangs/axe drop
};

#endif /* Monster_h */
