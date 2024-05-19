//
//  GameObject.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/18/24.
//

#ifndef GameObject_h
#define GameObject_h

#include <string>

using namespace std;


class GameObject {
public:
    GameObject(string name); 
    int getXPos();
    int getYPos();
    
    void setXPos(int n);
    void setYPos(int n);
    
    string getName(); 
private:
    string m_name;
    int m_x;
    int m_y;

};

class Weapon : public GameObject {
public:
    Weapon(string name, int dexterityBonus, int damage); 
private:
    string actionString;
    int m_dexterityBonus;
    int m_damage;
};

class Scroll : public GameObject {
public:
    Scroll(string name);
};


#endif /* GameObject_h */



//Maces, with a dexterity bonus of 0 and a damage amount of 2.
//Short swords, with a dexterity bonus of 0 and a damage amount of 2.
//Long swords, with a dexterity bonus of 2 and a damage amount of 4.
//Magic axes, with a dexterity bonus of 5 and a damage amount of 5.
//Magic fangs of sleep, with a dexterity bonus of 3 and a damage amount of 2. In addition to the regular hit point damage magic fangs of sleep do when the attacker hits the defender, there is a 1 in 5 chance that the magic fangs of sleep will put the defender to sleep. The number of moves the sleep will last (the sleep time) is a random integer from 2 to 6, call it X. If the defender is already asleep, with current sleep time Y, then the defender's sleep time becomes the maximum of X and Y (and not, say, Y+X).
//
