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
#include "Room.h"

using namespace std; 

class Actor;
class Player;
class Monster;
class GameObject;
class Weapon;

class Temple {
public:
    Temple(Player* pointer, int level, int goblinSmellDistance);
    ~Temple();
             
    //  printing actions to the dispplay
    void printMap();
    void printStats();
    void printActions();
    
    // set random rooms
    void generateRooms();
    bool overlaps(Room room1, Room room2);
    void printRoom(Room room);
    double calculateDistance(Room room1, Room room2); 
    void connectRooms();
    bool allRoomsConnected(); 
    void dfs(char copy[18][70], int i, int j);
    
    // set the positions for the spawn of player, monsters, and objects
    void setPlayerSpawn();
    void setMonsterSpawn();
    void setGameObjectSpawn();
    void setStairsSpawn(int x, int y);
    void setIdolSpawn(int x, int y);
    
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
    
    // place stairs
    void setStairs(); 
    
    // place golden idol
    void setIdol();
    
    // object pick up
    bool checkForObjects();
    bool isObjectAt(int x, int y);
    
    // let one actor attack another
    void attack(Actor* attacker, Actor* defender, Weapon weapon);

    // check if there is a monster where the player is moving
    bool isMonsterAt(int x, int y);
    Monster* getMonsterAt(int x, int y);
    
    // check if the player is where the monster is moving
    bool isPlayerAt(int x, int y); 
    
    // move monsters based on the player
    void moveMonsters(); 
    void moveTowardsPlayer(Monster* monster, char monsterChar);
    void dropItem(Monster* monster, int x, int y);
    
    // descent stairs
    bool atStairs();
    
    // pick up idol
    bool atIdol();
    
    // do not want the stairs, idol, or objects to get overwritten when an actor moves
    void keepObjects(Actor* mover);
    
    //getters
    GameObject* getStairs();
    GameObject* getIdol();
    char (*getMap())[18][70];
    vector<GameObject*> getObjects();
    
    // bfs
    vector<array<int, 2>> bfs(Monster* goblin, char copy[18][70]);
    bool isValidBFS(int x, int y, char copy[18][70]);
    
    
private:
    char m_map[18][70];
    Player* player;
    int m_level;
    GameObject* stairs;
    GameObject* idol;
    int m_goblinSmellDistance; 
    
    vector<Room*> rooms;
    
    // monsters/objects on screen
    vector<Monster*> monsters;
    vector<GameObject*> objects;
    vector<string> attacks;
};

#endif /* Temple_h */
