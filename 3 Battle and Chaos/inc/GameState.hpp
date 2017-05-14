/**
 * \class
 * This class represents the state of the game.  
 * 
 */

#ifndef GameState_HPP
#define GameState_HPP

#include <SFML/Graphics.hpp>
#include "SoundManager.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
#include "Team.hpp"
#include "MyConnection.hpp"

class StateManager;

class GameState {
protected:
	sf::RenderWindow& renderWindow;
	StateManager& stateManager;
	Window& window;
	Team& myTeam;
	Team& opponentTeam;
	MyConnection& connection;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
    bool changeState;
public:
	GameState(sf::RenderWindow&,StateManager&,Window&,Team&,Team&,MyConnection&);
	~GameState();

	virtual void init() = 0 ;
	virtual void Exit() = 0 ;
	virtual void update() = 0 ;
	virtual void draw() = 0 ;
	virtual void handleEvent(const sf::Event&) = 0 ;
};

#endif