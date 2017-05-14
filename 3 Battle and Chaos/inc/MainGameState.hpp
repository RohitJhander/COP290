/**
 * \class
 * This class represents the main game state of the game.  
 * 
 */

#ifndef MainGameState_HPP
#define MainGameState_HPP

#include "GameState.hpp"
#include "DrawableContainer.hpp"
#include "Button.hpp"
#include "MyDefines.hpp"

#include <SFML/Network.hpp>

class MainGameState : public GameState {
private:
	sf::Music music;		///<background music
	sf::Sound bulletSound;	///<sound of bullet
	Button *exitButton;		///<button to exit the game

	DrawableContainer topBar,menuBar;	///<containers for bottom and top menus
	
	sf::Text moneyText;		///<string containing money of team
	sf::Text lifeText;		///<string containing life of team
	
	sf::Texture tpanel;		///<texture for  bottom panel
	sf::Sprite panel;		///<sprite for bottom panel

	sf::Texture topPanel;		///<texture for top panel
	sf::Sprite topPanelSprite;		///<sprite for top panel

	bool spaceKeyHold;		///<true if spacekey is held

	Button *towerButtons[6];		///<buttons for towers
	Button *creepButtons[6];		///<buttons for creeps

	void initText();		///<initializes the text
	void initButtons();		///<initializes the buttons

	CreepType getCreepType(sf::Vector2i);	///<returns the type of creep
	TowerType getTowerType(sf::Vector2i);	///<returns the type of tower

	sf::Text towerTypeText;		///<string containing tower type
	sf::Text towerSpeedText;	///<string containing speed
	sf::Text towerDamageText;	///<string containing damage
	sf::Text towerPriceText;	///<string containing price

	void displayTowerDetails(Tower *selectedTower);	///<displays the details of tower
	void dontDisplayTowerDetails();		///<erases the details of tower

	Button *sellTowerButton;		///<button for selling tower
	Button *upgradeTowerButton;		///<button for upgrading tower

public:
	MainGameState(sf::RenderWindow&,StateManager&,Window&,Team&,Team&,MyConnection&);		///<constructor of mainGmaeState
	~MainGameState();	///<destructor for mainGmaeState

	void init();	///<initializes all the elements
	void Exit();	///<exits the game
	void update();		///<updates all the managers, and sends and recievs messages
	void draw();	///<draws all the drawables
	void handleEvent(const sf::Event&);		///<handles the events related to player
};

#endif
