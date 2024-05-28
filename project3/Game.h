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
    void playerMonsterTurn();
private:
    int m_goblinSmellDistance;
    Player player;
    Temple* board;
    int m_level;
};

#endif // GAME_INCLUDED
