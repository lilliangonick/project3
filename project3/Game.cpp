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
    
    char c = '\0';
    while (c != 'q') {

        c = getCharacter();
        switch (c) {
                //TODO stops moving on x pos 17
            case ARROW_LEFT:
                if (!board.validMove(player.getXPos() - 1, player.getYPos())) {
                    continue;
                }
                else {
                    board.movePlayer(c);
                }
                break;
            case ARROW_RIGHT:
                if (!board.validMove(player.getXPos() + 1, player.getYPos())) {
                    continue;
                }
                else {
                    board.movePlayer(c);
                }
                break;
            case ARROW_UP:
                if (!board.validMove(player.getXPos(), player.getYPos() - 1)) {
                    continue;
                }
                else {
                    board.movePlayer(c);
                }
                break;
            case ARROW_DOWN:
                if (!board.validMove(player.getXPos(), player.getYPos() + 1)) {
                    continue;
                }
                else {
                    board.movePlayer(c);
                }
                break;
            default:
                continue;
        }
        board.printMap();
        
    }
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons, 
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.
