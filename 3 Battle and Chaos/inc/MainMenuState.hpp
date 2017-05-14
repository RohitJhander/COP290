/**
 * \class
 * This class represents the main menu state of the game.  
 * 
 */

#ifndef MainMenuState_HPP
#define MainMenuState_HPP

#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "GameState.hpp"
#include "DrawableContainer.hpp"
#include "Button.hpp"

///substates of the main menu state
enum Substate{
    START, HOST, JOIN, GAME
};

class MainMenuState : public GameState {
private:
    sf::Text EnterText;	
    sf::Text inputText;	///<stores the input given by user

    int teamNumber;		///<stores the team number

    Button *hostButton;	///<host button
    Button *joinButton;	///<join button
    Button *exitButton;	///<exit button
    Button *backButton;	///<back button
    DrawableContainer container;	///<container object for various drawables

    Substate currentSubstate;	///<current substate

    bool mouseHold;		///<true if mouse is held

    void changeSubstate(Substate);	///<changes the current substate
    void forceUpdate();		///<forcefully calls the update function
    void acceptNewPlayer(int);	///<accepts a new player
    void addPlayersToTeam(map< sf::IpAddress, int >&);	///<adds player to team

public:
	///constructor for class
	MainMenuState(sf::RenderWindow&,StateManager&,Window&,Team&,Team&,MyConnection&);
	///destructor for class
	~MainMenuState();

	void init();	///<initializes tall the elements
	void Exit();	///<Frees the resources after exiting the gamestate
	void update();		///<updates all the elemets
	void draw();	///<draws all the drawable objetcs
	void handleEvent(const sf::Event&);	///<handles all the events
};

#endif
