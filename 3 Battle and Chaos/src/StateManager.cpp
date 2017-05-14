#include "StateManager.hpp"
#include <iostream>

StateManager::StateManager() {
	currentGameState = NULL;
}

StateManager::~StateManager() {
	currentGameState = NULL;
	map<string,GameState*>::iterator it = states.begin();

	for(; it!=states.end() ; ++it) {
		delete it->second;
	}
	states.clear();
}

void StateManager::addGameState(string name, GameState* gameState) {
	states[name] = gameState;
}

void StateManager::changeGameState(string name) {
	if(currentGameState != NULL) {
		currentGameState->Exit() ;
	}
	map<string,GameState*>::iterator it = states.find(name);
	if(it != states.end()) {
		currentGameState = it->second;
		currentGameState->init();
	}else{
		#ifdef PRINT
			cout<<"throw exception\n";
		#endif
	}
}

void StateManager::update() {
	currentGameState->update();
}

void StateManager::draw() {
	currentGameState->draw();
}

void StateManager::handleEvent(const sf::Event& event) {
	currentGameState->handleEvent(event);
}