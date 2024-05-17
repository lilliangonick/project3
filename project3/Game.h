// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Temple.h"
#include "Player.h"

// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
private:
    int m_level;
    Temple board; 
    Player player; 
};

#endif // GAME_INCLUDED
