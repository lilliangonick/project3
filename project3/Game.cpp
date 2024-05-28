// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) : m_goblinSmellDistance(goblinSmellDistance), player(Player()), board( new Temple(&player, 0, goblinSmellDistance)), m_level(0){}

// delete dynamically allocated board
Game::~Game() {
    delete board;
}

int Game::getGoblinSmellDistance() {
    return m_goblinSmellDistance;
}

// generate a new level (temple) on command
void Game::newLevel() {
    // incrememnt the level
    m_level++;
    
    // clear old level
    clearScreen();
    delete board;
    
    // create a new board
    board = new Temple(&player, m_level, m_goblinSmellDistance);
    
    // spawn the monsters
    board->setMonster();
    board->setMonsterSpawn();
    
    // spawn the game objects
    board->setGameObject();
    board->setGameObjectSpawn();
    
    if (m_level < 4) {
        // spawn the stairs
        board->setStairs();
    } else {
        board->setIdol(); 
    }
    
    // spawn the player
    board->setPlayerSpawn();
    board->setPlayer(player.getXPos(), player.getYPos());
}

// play a level of Doom
void Game::play()
{
    // spawn the monsters
    board->setMonster();
    board->setMonsterSpawn();
    
    // spawn the game objects
    board->setGameObject();
    board->setGameObjectSpawn();
    
    // spawn the stairs
    board->setStairs();
    
    // spawn the player
    board->setPlayerSpawn();
    board->setPlayer(player.getXPos(), player.getYPos());
    
    // display the map
    board->printMap();
    board->printStats();
    
    char c = '\0';
    while (c != 'q') {
        player.regainHP();
        c = getCharacter();

        // deal with movement when the player is asleep (the monsters can still attack) 
        if (player.isSleeping()) {
            board->movePlayer('x');
                board->moveMonsters();
                board->printMap();
                board->printStats();
                cout << "player asleep for: " << player.getSleepTime() << endl;
//                if (board->justAttacked()) {
                    board->printActions();
//                }
            if (player.getHP() <= 0) {
                break;
            }
            continue;
        }
                switch (c) {
            // check if the desired position is valid, then reprint the display, stats (and action line)
            case ARROW_LEFT:
                if (!board->validMove(player.getXPos() - 1, player.getYPos())) {
                    continue;
                }
                else {
                    board->movePlayer(c);
                }
                board->printMap();
                board->printStats();
                if (board->justAttacked()) {
                    board->printActions();
                }
                if (!board->atIdol()) {
                    board->moveMonsters();
                    if (board->justAttacked()) {
                        board->printActions();
                    }
                }
                break;
            case ARROW_RIGHT:
                if (!board->validMove(player.getXPos() + 1, player.getYPos())) {
                    continue;
                }
                else {
                    board->movePlayer(c);
                }
                board->printMap();
                board->printStats();
//                if (board->justAttacked()) {
                    board->printActions();
//                }
                if (!board->atIdol()) {
                    board->moveMonsters();
//                    if (board->justAttacked()) {
                        board->printActions();
//                    }
                }
                break;
            case ARROW_UP:
                if (!board->validMove(player.getXPos(), player.getYPos() - 1)) {
                    continue;
                }
                else {
                    board->movePlayer(c);
                }
                board->printMap();
                board->printStats();
//                if (board->justAttacked()) {
                    board->printActions();
//                }
                if (!board->atIdol()) {
                    board->moveMonsters();
//                    if (board->justAttacked()) {
                        board->printActions();
//                    }
                }
                break;
            case ARROW_DOWN:
                if (!board->validMove(player.getXPos(), player.getYPos() + 1)) {
                    continue;
                }
                else {
                    board->movePlayer(c);
                }
                board->printMap();
                board->printStats();
//                if (board->justAttacked()) {
                    board->printActions();
//                }
                if (!board->atIdol()) {
                    board->moveMonsters();
//                    if (board->justAttacked()) {
                        board->printActions();
//                    }
                }
                break;
            case 'g':
                if (board->atIdol()) {
                    cout << "You pick up the golden idol\n" << "Congratulations, you won!";
                    return; 
                }
                if (board->checkForObjects()) {
                    continue;
                }
                board->printMap();
                board->printStats();
//                if (board->justAttacked()) {
                    board->printActions();
//                }
                break;
            // cheating increasings the players stats
            case 'c':
                player.cheat();
                board->printMap();
                board->printStats();
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
                board->printMap();
                board->printStats();
                player.printInventoryResult();
                break;
            // print inventory, then read  a scroll
            case 'r':
                clearScreen();
                player.readScroll(board);
                board->printMap();
                board->printStats();
                player.printInventoryResult();
                break;
            // generate a new level
            case '>':
                if (board->atStairs()) {
                    newLevel();
                    board->printMap();
                    board->printStats();
                    break;
                }
            // if invalid input, do not do anything
            default:
                board->printMap();
                board->printStats();
                if (!board->atIdol()) {
                    board->moveMonsters();
//                    if (board->justAttacked()) {
                        board->printActions();
//                    }
                }
        }
        if (player.getHP() <= 0) {
            break;
        }
    }
    cout << "Press q to exit game." << endl;
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons, 
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.

// in board, switch statement for what item you recieve, then get the player's stats and change them, then remove the object from the board
