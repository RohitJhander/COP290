/**
 * \class
 * This class manage various states in the game.
 * 
 */

#ifndef StateManager_HPP
#define StateManager_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "GameState.hpp"

class GameState;

using namespace std;

class StateManager {
private:
	map<string,GameState*> states;
	GameState *currentGameState;
public:
	StateManager();
	~StateManager();

	void addGameState(string,GameState*);
	void changeGameState(string);

	void update();
	void draw();
	void handleEvent(const sf::Event&);
};

#endif
