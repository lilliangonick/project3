//
//  Temple.cpp
//  project3
//
//  Created by lilly mai-vy gonick on 5/16/24.
//

#include "Temple.h"
#include "Player.h"
#include "Monster.h"
#include "utilities.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <cmath>

using namespace std;

// create temple (constructor)
Temple::Temple(Player* pointer, int level, int goblinSmellDistance) : player(pointer), m_level(level), m_justAttacked(false), stairs(new GameObject("stairs", "step")), idol(new GameObject("golden idol", "yay")), m_goblinSmellDistance(goblinSmellDistance) {
    int counter = 0;
    do {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 70; j++) {
                m_map[i][j] = '#';
            }
        }
        generateRooms();
        connectRooms();
        for (vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
            delete *it;
        }
        rooms.clear();
        counter++;
    } while (!allRoomsConnected());

 }

// destructor (deallocate memory)
Temple::~Temple() {
    // delete monsters vector
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        delete *it;
    }
    monsters.clear();
    
    // delete objects vector
    for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        delete *it;
    }
    objects.clear();
    
    // delete rooms vector
    for (vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
        delete *it;
    }
    rooms.clear();
    
//    // delete inventory vector
//    for (vector<GameObject*>::iterator it = inventory.begin(); it != inventory.end(); it++) {
//        delete *it;
//    }
//    inventory.clear(); 
    
    delete stairs;
    delete idol;
}

// getters
GameObject* Temple::getStairs() {
    return stairs;
}

GameObject* Temple::getIdol() {
    return idol;
}

char (*Temple::getMap())[18][70] {
    return &m_map;
}

vector<GameObject*> Temple::getObjects() {
    return objects; 
}

// display map
void Temple::printMap() {
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            std::cout << m_map[i][j];
        }
        cout << endl;
    }
}

// do the rooms overlap?
bool Temple::overlaps(Room room1, Room room2) {
    if (room1.getX() + room1.getWidth() + 1 <= room2.getX() - 1|| room2.getX() + room2.getWidth() + 1 <= room1.getX() - 1|| room1.getY() + room1.getHeight() + 1 <= room2.getY() - 1|| room2.getY() + room2.getHeight() + 1 <= room1.getY() - 1) {
        return false;
    } else {
        return true;
    }
}

// calculate the distance between rooms
double Temple::calculateDistance(Room room1, Room room2) {
    // get the center points of each room
    int x1 = room1.getX() + room1.getWidth() / 2;
    int y1 = room1.getY() + room1.getHeight() / 2;
    int x2 = room2.getX() + room2.getWidth() / 2;
    int y2 = room2.getY() + room2.getHeight() / 2;
    
    // return the distance between the two centers (distance formula)
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// create random rooms
void Temple::generateRooms() {
    int numRooms = randInt(4, 6);
    for (int i = 0; i < numRooms; i++) {
        bool roomAdded = false;
        while(!roomAdded) {
            int xPos = randInt(1, 69);
            int yPos = randInt(1, 17);
            
            int width = randInt(8, 15);
            int height = randInt(3, 8);
            
            // ensure the room fits within the map
            while (xPos + width > 69) {
                xPos = randInt(1, 69);
            }
            
            while (yPos + height > 17) {
                yPos = randInt(1, 17);
            }
            
            Room* newRoom = new Room(xPos, yPos, width, height, false);
            
            // rooms can not overlap
            bool overlap = false;
            for (vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
                if (overlaps(*newRoom, **it)) {
                    overlap = true;
                    break;
                }
            }

            // if the room is valid, add it to the room vector
            if (!overlap) {
                rooms.push_back(newRoom);
                printRoom(*newRoom);
                roomAdded = true; // can exit the while loop
            } else { // if not valid room, delete the point that was made;
                delete newRoom;
            }
            
        }
    }
}

// create the corridors between rooms
void Temple::connectRooms() {
    for (vector<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
        int minDistance = 1000;
        Room* closestRoom = nullptr;
        // determine the closest room to the current room
        for (vector<Room*>::iterator other = rooms.begin(); other != rooms.end(); ++other) {
            if (it != other) {
                if ((*other)->isConnected() == false) {
                    if (calculateDistance(**it, **other) < minDistance) {
                        minDistance = calculateDistance(**it, **other);
                        closestRoom = *other;
                    }
                }
            }
        }
        if (closestRoom != nullptr) {
            closestRoom->setConnected(true);
            (*it)->setConnected(true);
            
            // connect the two rooms
            int startingX = (*it)->getX() + (*it)->getWidth() / 2;
            int startingY = (*it)->getY() + (*it)->getHeight() / 2;
            int endingX = closestRoom->getX() + closestRoom->getWidth() / 2;
            int endingY = closestRoom->getY() + closestRoom->getHeight() / 2;
            
            // horizontal pathway
            for (int x = min(startingX, endingX); x <= max(startingX, endingX); ++x) {
                m_map[startingY][x] = ' ';
            }
            
            // vertical pathway
            for (int y = min(startingY, endingY); y <= max(startingY, endingY); ++y) {
                m_map[y][endingX] = ' ';
            }
        }
    }
}

// if there is not a path to every room, regenerate
bool Temple::allRoomsConnected() {
    char copy[18][70];
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            copy[i][j] = m_map[i][j];
        }
    }
    
    int numberOfIslands = 0;
    
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            if (copy[i][j] == ' ') {
                dfs(copy, i, j);
                numberOfIslands++;
            }
        }
    }
    return numberOfIslands == 1;
}

// depth first search to check that every room has been visited
void Temple::dfs(char copy[18][70], int i, int j) {
    if (i < 0 || i >= 18 || j < 0 || j >= 70 || copy[i][j] == '#') {
        return;
    }
    
    copy[i][j] = '#';
    
    dfs(copy, i + 1, j);
    dfs(copy, i, j - 1);
    dfs(copy, i - 1, j);
    dfs(copy, i, j + 1);
    
}

// display the rooms with ' '
void Temple::printRoom(Room room) {
    int startingX = room.getX();
    int startingY = room.getY();
    int endingX = room.getX() + room.getWidth();
    int endingY = room.getY() + room.getHeight();
    
    for (int y = startingY; y < endingY; y++) {
        for (int x = startingX; x < endingX; x++) {
            m_map[y][x] = ' ';
        }
    }
}

// display player stats
void Temple::printStats() {
    cout << "Level: " << m_level << ", Hit points: " << player->getHP() << ", Armor: " << player->getArmor() << ", Strength: " << player->getStrength() << ", Dexterity: " << player->getDexterity() << endl << endl; 
}

void Temple::printActions() {
    size_t initialSize = attacks.size();
        for (size_t i = 0; i < initialSize; ++i) {
            cout << attacks[i] << endl;
        }
        // erase all attacks up to the last index printed
        attacks.erase(attacks.begin(), attacks.begin() + initialSize);
}

// set player icon
void Temple::setPlayer(int x, int y) {
    m_map[y][x] = '@';
}

// set stairs
void Temple::setStairsSpawn(int x, int y) {
    m_map[y][x] = '>';
}

// set idol
void Temple::setIdolSpawn(int x, int y) {
    m_map[y][x] = '&';
}

void Temple::setStairs() {
    int x = randInt(1, 69);
    int y = randInt(1, 17);
    while (
           !validMove(x, y)
           ) {
        x = randInt(1, 69);
        y = randInt(1, 17);
    }
    stairs->setXPos(x);
    stairs->setYPos(y);
    setStairsSpawn(stairs->getXPos(), stairs->getYPos());
}

// set golden idol on level 4
void Temple::setIdol() {
    int x = randInt(1, 69);
    int y = randInt(1, 17);
    while (!validMove(x, y)) {
        x = randInt(1, 69);
        y = randInt(1, 17);
    }
    idol->setXPos(x);
    idol->setYPos(y);
    setIdolSpawn(idol->getXPos(), idol->getYPos());
}

bool Temple::justAttacked() {
    return m_justAttacked;
}

// see if the move is valid
bool Temple::validMove(int xPos, int yPos) {
    if (m_map[yPos][xPos] == '#') {
        return false;
    }
    return true;
}

// see if the move is valid
bool Temple::validMonsterMove(int xPos, int yPos) {
    if (m_map[yPos][xPos] == '#' || m_map[yPos][xPos] == 'B' || m_map[yPos][xPos] == 'S' || m_map[yPos][xPos] == 'D' || m_map[yPos][xPos] == 'G') {
        return false;
    }
    return true;
}

// move the player based on a command
void Temple::movePlayer(char c) {
    // if sleeping, decrement the sleep time and skip turn
    if (player->isSleeping()) {
        player->decreaseSleepTime();
        return;
    }
    
    m_justAttacked = false;
    int newX = player->getXPos();
    int newY = player->getYPos();

    // determine the new position based on the direction
    if (c == ARROW_LEFT) {
        newX -= 1;
    } else if (c == ARROW_RIGHT) {
        newX += 1;
    } else if (c == ARROW_UP) {
        newY -= 1;
    } else if (c == ARROW_DOWN) {
        newY += 1;
    }
    
    // check if there is a monster at the new position
    if (isMonsterAt(newX, newY)) {
        Monster* monster = getMonsterAt(newX, newY);
        attack(player, monster, player->getWeapon());
        m_justAttacked = true;
        return; // do not move the player
    }
    
    m_map[player->getYPos()][player->getXPos()] = ' ';
    if (player->getXPos() == stairs->getXPos() && player->getYPos() == stairs->getYPos()) {
        setStairsSpawn(player->getXPos(), player->getYPos());
    }
    if (player->getXPos() == idol->getXPos() && player->getYPos() == idol->getYPos()) {
        setIdolSpawn(player->getXPos(), player->getYPos());
    }
    
    if (isObjectAt(player->getXPos(), player->getYPos())) {
        for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            if ((*it)->getXPos() == player->getXPos() && (*it)->getYPos() == player->getYPos()) {
                if ((*it)->getType() == "Scroll") {
                    m_map[(*it)->getYPos()][(*it)->getXPos()] = '?';
                } else {
                    m_map[(*it)->getYPos()][(*it)->getXPos()] = '(';
                }
            }
        }
    }
    
    // move the player to the new position
    player->Actor::setXPos(newX);
    player->Actor::setYPos(newY);
    setPlayer(player->getXPos(), player->getYPos());
}

// set spawn of the player 
void Temple::setPlayerSpawn() {
    int x = randInt(1, 69);
    int y = randInt(1, 17);
    while (!validMove(x, y)) {
        x = randInt(1,69);
        y = randInt(1, 17);
    }
    player->setXPos(x);
    player->setYPos(y);
}

// set spawn of the monsters
void Temple::setMonsterSpawn() {
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!validMove(x, y)) {
            x = randInt(1, 69);
            y = randInt(1, 17);
        }
        (*it)->setXPos(x);
        (*it)->setYPos(y);
        Monster& monster = **it;  // Dereference the iterator and the pointer
        if (typeid(monster) == typeid(Snakewoman)) {
            m_map[monster.getYPos()][monster.getXPos()] = 'S';
        } else if (typeid(monster) == typeid(Goblin)) {
            m_map[monster.getYPos()][monster.getXPos()] = 'G';
        } else if (typeid(monster) == typeid(Bogeyman)) {
            m_map[monster.getYPos()][monster.getXPos()] = 'B';
        } else if (typeid(monster) == typeid(Dragon)) {
            m_map[monster.getYPos()][monster.getXPos()] = 'D';
        }
    }
}

// create new monsters at the spawn of a new level
void Temple::setMonster() {
    int m;
    if (m_level == 0) {
        m = randInt(2, 5*(0+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 1);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(m_goblinSmellDistance);
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 1) {
        m = randInt(2, 5*(0+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 1);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(m_goblinSmellDistance);
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 2) {
        m = randInt(2, 5*(2+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 2);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(m_goblinSmellDistance);
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman(5);
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 3) {
        m = randInt(2, 5*(3+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 3);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(m_goblinSmellDistance);
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman(5);
                    monsters.push_back(monster);
                } else if (rand == 3) {
                    monster = new Dragon(0);
                    monsters.push_back(monster);
                }
        }
    } else if (m_level == 4) {
        m = randInt(2, 5*(4+1)+1);
        for (int i = 0; i < m; i++) {
            Monster* monster = nullptr;
            int rand = randInt(0, 3);
                if (rand == 0) {
                    monster = new Snakewoman(3);
                    monsters.push_back(monster);
                } else if (rand == 1) {
                    monster = new Goblin(m_goblinSmellDistance);
                    monsters.push_back(monster);
                } else if (rand == 2) {
                    monster = new Bogeyman(5);
                    monsters.push_back(monster);
                } else if (rand == 3) {
                    monster = new Dragon(0);
                    monsters.push_back(monster);
                }
        }
    }
}

// spawn 2 -3 GameObjects at the start of a new level
void Temple::setGameObject() {
    int num = randInt(2, 3);
    vector<string> objectTypes = {
            "mace", "short sword", "long sword",
            "scroll of enhance armor", "scroll of strength",
            "scroll of enhance health", "scroll of enhance dexterity"
        };

    for (int i = 0; i < num; i++) {
        int randIndex = randInt(0, 6);
        string objectType = objectTypes[randIndex];
        
        GameObject* object = nullptr;
        if (objectType == "mace") {
            object = new Weapon("mace", "swings", 0, 2);
            objects.push_back(object);
        } else if (objectType == "short sword") {
            object = new Weapon("short sword", "slashes", 0, 2);
            objects.push_back(object);
        } else if (objectType == "long sword") {
            object = new Weapon("long sword", "swings", 2, 4);
            objects.push_back(object);
        } else if (objectType == "scroll of enhance armor") {
            object = new Scroll("scroll of enhance armor");
            objects.push_back(object);
        } else if (objectType == "scroll of strength") {
            object = new Scroll("scroll of strength");
            objects.push_back(object);
        } else if (objectType == "scroll of enhance health") {
            object = new Scroll("scroll of enhance health");
            objects.push_back(object);
        } else if (objectType == "scroll of enhance dexterity") {
            object = new Scroll("scroll of enhance dexterity");
            objects.push_back(object);
        }
    }
}

// set the positions of the GameObjects (at the start of the level)
void Temple::setGameObjectSpawn() {
    for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        int x = randInt(1, 69);
        int y = randInt(1, 17);
        while (!validMove(x, y)) {
            x = randInt(1, 69);
            y = randInt(1, 17);
        }
        (*it)->setXPos(x);
        (*it)->setYPos(y);

        if ((*it)->getName() == "scroll of teleportation" || (*it)->getName() == "scroll of enhance armor" || (*it)->getName() == "scroll of strength" || (*it)->getName() == "scroll of enhance health" || (*it)->getName() == "scroll of enhance dexterity") {
            m_map[(*it)->getYPos()][(*it)->getXPos()] = '?';
        } else {
            m_map[(*it)->getYPos()][(*it)->getXPos()] = '(';
        }
    }
}


// check if there is an object on the same position of an actor (to be able to 'g' command it into the inventory) 
bool Temple::checkForObjects() {
    for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        if (player->getXPos() == (*it)->getXPos() && player->getYPos() == (*it)->getYPos()) {
            player->pickUpObject(*it);
            it = objects.erase(it);
            return true;
        }
    }
    return false;
}

// check the position of each object in the inventory
bool Temple::isObjectAt(int x, int y) {
    for (size_t i = 0; i < objects.size(); i++) {
        if (objects[i]->getXPos() == x && objects[i]->getYPos() == y) {
            return true;
        }
    }
    return false;
}


// check if there is monster where the player wants to go
bool Temple::isMonsterAt(int x, int y) {
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        if ((*it)->getXPos() == x && (*it)->getYPos() == y) {
            return true;
        }
    }
    return false;
}

// if there is a monster where the player wants to move, return a pointer to that monster
Monster* Temple::getMonsterAt(int x, int y) {
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        if ((*it)->getXPos() == x && (*it)->getYPos() == y) {
            return *it;
        }
    }
    return nullptr;
}

// let one actor attack another
void Temple::attack(Actor* attacker, Actor* defender, Weapon weapon) {
    int attackerPoints = attacker->getDexterity() + weapon.getDexterityBonus();
    int defenderPoints = defender->getDexterity() + defender->getArmor();
 
    bool hit = false;
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damageAmount = randInt(0, attacker->getStrength() + weapon.getDamage() - 1);
        defender->setHP(-damageAmount);
        hit = true;
    }
    
    string result;
    string attackerName = attacker->getName();
    string weaponAction = weapon.getAction();
    string weaponName = weapon.getName();
    string defenderName = defender->getName();
    
    // deletes the monster if it dies
    if (defender->getHP() <= 0) {
        attacks.push_back(attackerName + " " + weaponAction + " " + weaponName + " at " + defenderName + " dealing a final blow.");
        m_map[defender->getYPos()][defender->getXPos()] = ' ';
        if (defender->isMonster()) {
            // drop an item (based on a probability) upon death
            if (!isObjectAt(defender->getXPos(), defender->getYPos())) {
                if (defender->shouldDrop()) {
                    GameObject* droppedItem = defender->dropNewItem();
                    droppedItem->setXPos(defender->getXPos());
                    droppedItem->setYPos(defender->getYPos());
                    objects.push_back(droppedItem);
                    if (droppedItem->getName() == "scroll of teleportation" || droppedItem->getName() == "scroll of enhance armor" || droppedItem->getName() == "scroll of strength" || droppedItem->getName() == "scroll of enhance health" || droppedItem->getName() == "scroll of enhance dexterity") {
                        m_map[droppedItem->getYPos()][droppedItem->getXPos()] = '?';
                    } else {
                        m_map[droppedItem->getYPos()][droppedItem->getXPos()] = '(';
                    }
                }
            }
            vector<Monster*>::iterator it = find(monsters.begin(), monsters.end(), defender);
            if (it != monsters.end()) {
                delete *it;
                monsters.erase(it);
            }
        }
        return;
    }
    
    if (hit) {
        if (weapon.getName() == "magic fangs") {
            defender->magicFangsEffect();
        }
        result = "hits";
    } else {
        result = "misses";
    }

    attacks.push_back(attackerName +  " " + weaponAction + " " + weaponName + " at " + defenderName + " and " + result);
}

// move the monsters based on the position of the player
void Temple::moveMonsters() {
    m_justAttacked = false;
    for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
        if ((*it)->isSleeping()) {
            ((*it))->decreaseSleepTime();
        } else if ((*it)->getName() == "the Bogeyman") {
            if ((*it)->smell(player)) {
                moveTowardsPlayer(*it, 'B');
            }
        } else if ((*it)->getName() == "the Snakewoman") {
            if ((*it)->smell(player)) {
                moveTowardsPlayer(*it, 'S');
            }
        } else if ((*it)->getName() == "the Dragon") {
            // dragons have a 1/10 chance of healing
            if (trueWithProbability(0.1)) {
                ((*it))->setHP(1);
            }
            
            // if the dragon is already next to the player, attack directly
            if ((*it)->getXPos() + 1 == player->getXPos() && (*it)->getYPos() == player->getYPos()) {
                attack((*it), player, (*it)->getWeapon());
                m_justAttacked = true;
                return;
            } else if ((*it)->getXPos() - 1 == player->getXPos() && (*it)->getYPos() == player->getYPos()) {
                attack((*it), player, (*it)->getWeapon());
                m_justAttacked = true;
                return;
            } else if ((*it)->getXPos() == player->getXPos() && (*it)->getYPos() + 1 == player->getYPos()) {
                attack((*it), player, (*it)->getWeapon());
                m_justAttacked = true;
                return;
            } else if ((*it)->getXPos() == player->getXPos() && (*it)->getYPos() - 1 == player->getYPos()) {
                attack((*it), player, (*it)->getWeapon());
                m_justAttacked = true;
                return;
            }
        } else if ((*it)->getName() == "the Goblin") {
            if ((*it)->smell(player)) {
                moveTowardsPlayer(*it, 'G');
            }
        }
        // if player is already dead when the monsters are attacking, return
        if (player->getHP() <=0) {
            return;
        }
    }
}

// calculate which step to move towards the player
void Temple::moveTowardsPlayer(Monster* monster, char monsterChar) {
    m_justAttacked = false;
    int playerXPos = player->getXPos();
    int playerYPos = player->getYPos();
    int monsterXPos = monster->getXPos();
    int monsterYPos = monster->getYPos();
    
    // if the monster is already next to the player, attack directly
    if (monsterXPos + 1 == playerXPos && monsterYPos == playerYPos) {
        attack(monster, player, monster->getWeapon());
        m_justAttacked = true;
        return;
    } else if (monsterXPos - 1 == playerXPos && monsterYPos == playerYPos) {
        attack(monster, player, monster->getWeapon());
        m_justAttacked = true;
        return;
    } else if (monsterXPos == playerXPos && monsterYPos + 1 == playerYPos) {
        attack(monster, player, monster->getWeapon());
        m_justAttacked = true;
        return;
    } else if (monsterXPos == playerXPos && monsterYPos - 1 == playerYPos) {
        attack(monster, player, monster->getWeapon());
        m_justAttacked = true;
        return;
    }
    
    
    // variables to store new position
    int newMonsterXPos = monsterXPos;
    int newMonsterYPos = monsterYPos;
    
    if (playerXPos > monsterXPos && validMonsterMove(monsterXPos + 1, monsterYPos)) {
        newMonsterXPos = monsterXPos + 1;
    } else if (playerXPos < monsterXPos && validMonsterMove(monsterXPos - 1, monsterYPos)) {
        newMonsterXPos = monsterXPos - 1;
    } else if (playerYPos > monsterYPos && validMonsterMove(monsterXPos, monsterYPos + 1)) {
        newMonsterYPos = monsterYPos + 1;
    } else if (playerYPos < monsterYPos && validMonsterMove(monsterXPos, monsterYPos - 1)) {
        newMonsterYPos = monsterYPos - 1;
    }
    
    m_map[monsterYPos][monsterXPos] = ' '; // clear the old position
    
    // do not overwrite the stairs
    if (monster->getXPos() == stairs->getXPos() && monster->getYPos() == stairs->getYPos()) {
        setStairsSpawn(monster->getXPos(), monster->getYPos());
    }
    
    // do not overwrite the golden idol
    if (monster->getXPos() == idol->getXPos() && monster->getYPos() == idol->getYPos()) {
        setIdolSpawn(monster->getXPos(), monster->getYPos());
    }
    
    // make sure player movement does not overwrite the objects
    if (isObjectAt(monster->getXPos(), monster->getYPos())) {
        for (vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            if ((*it)->getXPos() == monster->getXPos() && (*it)->getYPos() == monster->getYPos()) {
                if ((*it)->getType() == "Scroll") {
                    m_map[(*it)->getYPos()][(*it)->getXPos()] = '?';
                } else {
                    m_map[(*it)->getYPos()][(*it)->getXPos()] = '(';
                }
            }
        }
    }
    m_map[newMonsterYPos][newMonsterXPos] = monsterChar; // set the new position
    monster->setXPos(newMonsterXPos);
    monster->setYPos(newMonsterYPos);
}

// is the player at the stairs
bool Temple::atStairs() {
    if (player->getXPos() == stairs->getXPos() && player->getYPos() == stairs->getYPos()) {
        return true;
    } else {
        return false; 
    }
}

// is the player at the idol
bool Temple::atIdol() {
    if (player->getXPos() == idol->getXPos() && player->getYPos() == idol->getYPos()) {
        return true;
    } else {
        return false; 
    }
}
