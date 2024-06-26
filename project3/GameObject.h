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
    GameObject(string type, string name);
    virtual ~GameObject(); 
    
    // object getters
    int getXPos();
    int getYPos();
    
    // object setters
    void setXPos(int n);
    void setYPos(int n);
    
    string getName();
    string getType(); 
    
private:
    string m_type;
    string m_name;
    int m_x;
    int m_y;

};

// weapons are a type of object
class Weapon : public GameObject {
public:
    Weapon(string name, string actionString, int dexterityBonus, int damage);
    string getAction();
    int getDexterityBonus();
    int getDamage();
    
private:
    string m_actionString;
    int m_dexterityBonus;
    int m_damage;
};

// scrolls are a type of object
class Scroll : public GameObject {
public:
    Scroll(string name);
};


#endif /* GameObject_h */


