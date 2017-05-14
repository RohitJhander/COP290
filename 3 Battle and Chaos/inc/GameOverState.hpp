/**
 * \class
 * This class represents the game over state of the game.  
 * 
 */

#ifndef GameOverState_HPP
#define GameOverState_HPP

#include "GameState.hpp"
#include "DrawableContainer.hpp"
#include "Button.hpp"

class GameOverState : public GameState {
private:
	sf::Text resultText;
	Button *exitButton;
    DrawableContainer container;
    bool mouseHold;

    sf::Sound victorySound;
    sf::Sound defeatSound;

public:
	GameOverState(sf::RenderWindow&,StateManager&,Window&,Team&,Team&,MyConnection&);
	~GameOverState();

	void init();
	void Exit();
	void update();
	void draw();
	void handleEvent(const sf::Event&);
};

#endif