// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) : m_goblinSmellDistance(goblinSmellDistance), player(Player()), board(Temple(&player))
{}

int Game::getGoblinSmellDistance() {
    return m_goblinSmellDistance;
}

void Game::play()
{
    cout << "The game hasn't been implemented yet." << endl;
    cout << "Press q to exit game." << endl;
    
    // spawn the player
    board.setPlayerSpawn();
    board.setPlayer(player.getXPos(), player.getYPos());
    
    // spawn the monsters
    board.setMonster();
    board.setMonsterSpawn();
    
    // spawn the game objects
    board.setGameObject();
    board.setGameObjectSpawn();
    
    char c = '\0';
    while (c != 'q') {
        player.regainHP();
        c = getCharacter();
        switch (c) {
            // check if the desired position is valid, then reprint the display, stats (and action line)
            case ARROW_LEFT:
                if (!board.validMove(player.getXPos() - 1, player.getYPos())) {
                    continue;
                }
                else {
                    board.movePlayer(c);
                }
                board.printMap();
                board.printStats();
                if (board.justAttacked()) {
                    board.printActions();
                }
                break;
            case ARROW_RIGHT:
                if (!board.validMove(player.getXPos() + 1, player.getYPos())) {
                    continue;
                }
                else {
                    board.movePlayer(c);
                }
                board.printMap();
                board.printStats();
                if (board.justAttacked()) {
                    board.printActions();
                }
                break;
            case ARROW_UP:
                if (!board.validMove(player.getXPos(), player.getYPos() - 1)) {
                    continue;
                }
                else {
                    board.movePlayer(c);
                }
                board.printMap();
                board.printStats();
                if (board.justAttacked()) {
                    board.printActions();
                }
                break;
            case ARROW_DOWN:
                if (!board.validMove(player.getXPos(), player.getYPos() + 1)) {
                    continue;
                }
                else {
                    board.movePlayer(c);
                }
                board.printMap();
                board.printStats();
                if (board.justAttacked()) {
                    board.printActions();
                }
                break;
            case 'g':
                if (board.checkForObjects()) {
                    continue;
                }
                board.printMap();
                board.printStats();
                if (board.justAttacked()) {
                    board.printActions();
                }
                break;
            // cheating increasings the players stats
            case 'c':
                player.cheat();
                board.printMap();
                board.printStats();
                break;
            // print the inventory
            case 'i':
                clearScreen();
                player.printInventory();
                break; 
            // print inventory, then weild a weapon
            case 'w':
                clearScreen();
                player.weildWeapon();
                board.printMap();
                board.printStats();
                player.printInventoryResult();
                break;
            // print inventory, then read  a scroll
            case 'r':
                clearScreen();
                player.readScroll();
                board.printMap();
                board.printStats();
                player.printInventoryResult();
                break;
            // if invalid input, do not do anything
            default:
                board.printMap();
                board.printStats(); 
                break;
        }
        board.moveMonsters(); 
        if (board.justAttacked()) {
            board.printActions();
        }
        
        if (player.getHP() <= 0) {
            break;
        }
    }
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons, 
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.

// in board, switch statement for what item you recieve, then get the player's stats and change them, then remove the object from the board
