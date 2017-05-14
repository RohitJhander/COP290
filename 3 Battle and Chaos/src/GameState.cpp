#include "GameState.hpp"

GameState::GameState(sf::RenderWindow& rw,StateManager& sm, Window& w, Team& mt, Team& ot, MyConnection& c):
	renderWindow(rw),
	stateManager(sm),
	window(w),
	myTeam(mt),
	opponentTeam(ot),
	connection(c)
{
	if (!font.loadFromFile("data/images/font.ttf")){
        // error...
    }
    changeState = false;
}

GameState::~GameState() {}