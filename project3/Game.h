// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Temple.h"
#include "Player.h"
#include "Monster.h"

#include <list>

// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game(); 
    int getGoblinSmellDistance();
    void play();
    void newLevel(); 
private:
    int m_goblinSmellDistance;
    int m_level;
    Player player;
    Temple* board;
};

#endif // GAME_INCLUDED
