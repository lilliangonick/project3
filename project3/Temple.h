//
//  Temple.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#ifndef Temple_h
#define Temple_h

#include <vector>

using namespace std; 

class Actor;
class Player;
class Monster;
class GameObject;
class Weapon;

class Temple {
public:
    Temple(Player* pointer);
    ~Temple();
             
    void printMap();
    void move();
    void printStats();
    void printActions();
    
    void setPlayerSpawn(); 
    void setMonsterSpawn();
    void setGameObjectSpawn();
    
    // validate moves
    bool validMove(int xPos, int yPos);
    bool validMoveChar(char c);
    
    // move player
    void setPlayer(int x, int y);
    void movePlayer(char c);
    
    // move monster 
    void setMonster();
    void moveMonster();
    
    // game objects
    void setGameObject(); 
//    void applyScroll(GameObject* scroll); 
    bool checkForObjects();
    bool isObjectAt(int x, int y);
    
    // let one actor attack another
    void attack(Actor* attacker, Actor* defender, Weapon weapon);

    // check if there is a monster where the player is moving
    bool isMonsterAt(int x, int y);
    Monster* getMonsterAt(int x, int y);
    
    // was an actor just attacked
    bool justAttacked();
    
    

    
private:
    char m_map[18][70];
    Player* player;
    int m_level;
    vector<Monster*> monsters;
    vector<GameObject*> objects; 
    vector<string> attacks;
    bool m_justAttacked; 
};

#endif /* Temple_h */
