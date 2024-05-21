//
//  Temple.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#ifndef Temple_h
#define Temple_h

#include <vector>
#include <string>

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
             
    //  printing actions to the dispplay
    void printMap();
    void printStats();
    void printActions();
    
    // set the positions for the spawn of player, monsters, and objects
    void setPlayerSpawn();
    void setMonsterSpawn();
    void setGameObjectSpawn();
    
    // validate moves
    bool validMove(int xPos, int yPos);
    bool validMoveChar(char c);
    bool validMonsterMove(int xPos, int yPos);
    
    // move player
    void setPlayer(int x, int y);
    void movePlayer(char c);
    
    // move monster 
    void setMonster();
    void moveMonster();
    
    // place game objects
    void setGameObject();
    
//    void applyScroll(GameObject* scroll);
    bool checkForObjects();
    bool isObjectAt(int x, int y);
    
    // let one actor attack another
    void attack(Actor* attacker, Actor* defender, Weapon weapon);

    // check if there is a monster where the player is moving
    bool isMonsterAt(int x, int y);
    Monster* getMonsterAt(int x, int y);
    
    // check if the player is where the monster is moving
    bool isPlayerAt(int x, int y); 
    
    // was an actor just attacked
    bool justAttacked();
    
    // move monsters based on the player
    void moveMonsters(); 
    void moveTowardsPlayer(Monster* monster, char monsterChar);
    void dropItem(Monster* monster, int x, int y);
    

    
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
