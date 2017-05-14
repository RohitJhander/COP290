/*
* Game.h
*/

#ifndef Game_H
#define Game_H

#include "Team.hpp"
#include "StateManager.hpp"
#include "Block.hpp"
#include "Window.hpp"
#include "MyConnection.hpp"

#include <SFML/Graphics.hpp>

class Game{
private:
	Window window;
	sf::RenderWindow renderWindow;
	StateManager stateManager;
	bool isExit;
	Team myTeam;
	Team opponentTeam;
	Mode mode;
	MyConnection connection;
public:

	Game();
	~Game();

	void run();
	void Exit();
};

#endif