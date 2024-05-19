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
    void play();
private:
    Player player; 
    Temple board;
};

#endif // GAME_INCLUDED
