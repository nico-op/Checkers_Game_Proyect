/*
*	The CheckerGame class has the checker game loop and keeps track of the state of the game (which player is winning).
*	This class handles manipulations to checkerpieces as well as high level AI operations. For instance, during gameplay a player will click
*	an arbitrary square to select a checker to move (green highlight), and then the player will click another square to move the checker onto (magenta highlight).
*	The computer checks to see if that jump or movement is legal by finding the square and then finding the checker that resides on the square.
*	There are 2 methods for jumping once a checker has been selected, either by selecting the checker to jump over, or by selecting an empty space beyond the checker to jump over.
*
*		***CHECKER RULES***
*	1) Pawns move forward (towards their king row) and diagonal (one square).
*	2) Kings move diagonal forward or backward (one square).
*	3) If a jump presents itself, the checker in play must jump, but it can decide which jump to take and where.
*	4) Double jumps can occur if the jumping checker does not need to make an additional move in order to secure the double jump.
*	5) A pawn can become a king by traversing from its starting row towards the farthest row opposite of the starting row on the starting board.
*	6) Last team standing wins.
*
*	It is assumed that only two players are playing at a time (it could be two humans or even two computers!).
*	At the moment, player one is red, and player two is yellow. In the future, it will be randomized or customizeable.
*	The checkers vector maintains an index of the checker that's in play. It should be consistent throughout the code for each turn.
*/

#ifndef CHECKERGAME_HPP
#define CHECKERGAME_HPP

#include <SFML/Graphics.hpp> // allows window drawing
#include <SFML/Audio.hpp> // allows audio loading and playback
#include <SFML/Window.hpp> // allows window instantation
#include <SFML/System.hpp> // needed for window instantion (and sf::Time)
#include <iostream>
#include <string>
#include <fstream> // for file IO
#include <ios> // for appending to save file
#include <sstream> // for string streams
#include <string> // for strings
#include <vector> // for vectors
#include "AI.hpp"
#include "SoundManager.hpp"

class CheckerGame
{
private:
	bool isPlaying; // used to keep track of the state of the game
	static sf::Time timeElapsed; // time elapsed from most recent checkers game
	static int winner; // winner of the most recent game (0 if there's no winner)
	Checkerboard* checkerboard;
	Checkerpiece cpDrawer;
	Player* p1;
	Player* p2;

	bool playerHasToJump(Player*&, Player*&);
	bool playerCannotMove(Player*&, Player*&, Checkerboard*&);
	void gameLoop(sf::RenderWindow&, sf::Event&);
	void showWinner(sf::RenderWindow&, sf::Event&);
	void createTeams();
	void changeTurn();
	void handleGameState(sf::Clock&);
	bool isActivePlayerHuman();
	void printChecker(Checkerpiece*, const std::string&);
	void deleteCheckerFromGame(Player*, const int&); 
	void ifCheckerKinged(Checkerpiece*, Square*);
	void saveTime(const double&);
public:
	CheckerGame(sf::RenderWindow&, const bool&, const bool&);
	~CheckerGame();
	void startCheckers(sf::RenderWindow&, sf::Event&);
};

#endif