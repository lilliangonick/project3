//
//  Temple.hpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#ifndef Temple_h
#define Temple_h

#include <list>

using namespace std; 

class Player;
class Monster;
class GameObject;

class Temple {
public:
    Temple(Player* pointer);
    void printMap();
    void move();
    void printStats();
    
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
    void applyScroll(GameObject* scroll); 
    
private:
    char m_map[18][70];
    int m_level;
    Player* player;
    vector<Monster*> monsters;
    vector<GameObject*> objects; 
};

#endif /* Temple_h */
