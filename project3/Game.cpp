// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) : m_level(0), player(Player()), board(Temple(&player))
{

}

void Game::play()
{
    cout << "The game hasn't been implemented yet." << endl;
    cout << "Press q to exit game." << endl;
    
    player.setSpawn(board);
    board.setPlayer(player.getXPos(), player.getYPos());
    
    char c = getCharacter();
    while (c != 'q') {
        // switch statement based on input that calls functions
        if (c == ARROW_LEFT) {
            
        } else if (c == ARROW_RIGHT) {
            
        } else if (c == ARROW_UP) {
    
        } else if (c == ARROW_DOWN) {
            
        } else {
            
        }
        
        board.printMap();
        c = getCharacter();
        
    }
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons, 
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.
