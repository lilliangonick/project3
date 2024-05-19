//
//  Monster.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/18/24.
//

#ifndef Monster_h
#define Monster_h

#include "Actor.h"
//#include "Temple.h"
#include <string>

class Monster : public Actor {
public:
    Monster(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity);
    virtual ~Monster();
    void handleTurn(); // ABC
    void dropItem(); // will eventually return a weapon type 
//    void setMonsterSpawn(Temple board);
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

#endif /* Monster_h */
