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
#include "GameObject.h"

class Monster : public Actor {
public:
    Monster(string name, int xPos, int yPos, int hit, string weaponName, string actionString, int dexterityBonus, int damage, int armor, int strength, int dexterity, int smellRange);
    virtual ~Monster();
    
    virtual bool smell(Player* player);
    int getSmellRange();
    
    // dropping items on death
    virtual bool shouldDrop(); 
    virtual GameObject* dropNewItem();

    
private:
    int m_smellRange;
    bool m_isDead;
};

class Bogeyman : public Monster {
public:
    Bogeyman(int smellRange);
    virtual bool shouldDrop();
    virtual GameObject* dropNewItem();
};

class Snakewoman : public Monster {
public:
    Snakewoman(int smellRange);
    virtual bool shouldDrop();
    virtual GameObject* dropNewItem();
};

class Dragon : public Monster {
public:
    Dragon(int smellRange);
    virtual bool shouldDrop();
    virtual GameObject* dropNewItem();
    void heal();
};

class Goblin : public Monster {
public:
    Goblin(int smellRange);
    virtual bool shouldDrop(); 
    virtual GameObject* dropNewItem();
    virtual bool smell(Player* player, int smellRange);
};

#endif /* Monster_h */
