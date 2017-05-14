/**
 * \class
 * This class represents a Player.
 * 
 */

#ifndef Player_HPP
#define Player_HPP

#include "Hero.hpp"
#include "MyDefines.hpp"
#include "Window.hpp"
#include "Team.hpp"
#include "BulletManager.hpp"
#include <string>
#include <iostream>

class Team;
class BulletManager;
class Hero;

class Player{
private:
	sf::RenderWindow& renderWindow;	///<The render window
	Window& window;	///<The window
	BulletManager *bulletManager;	///<Pointer to bullet manager
	Hero *hero;	///<Pointer to hero
	Team *opponentTeam;	///<pointer to opponent team
public:
	///constructor for player-
	Player(sf::RenderWindow&,Window&,Team*,BulletManager*);
	///destructor for player
	~Player();

	///initialzer function
	void init(int);
	
	std::string getName();	///<returns the string containg name
	void setName(std::string);	///<sets the name

	sf::Vector2f getPosition();	///<returns the position
	void setPosition(sf::Vector2f);	///<sets the position

	void setRotation(float);	///<sets the rotation
	float getRotation();		///<retutns the rotation

	void fireBullet();	///<fires bullet
	void move(bool,bool,bool,bool);	///<move function
	void move(Direction);	///<move function
	void draw();	///<draws all drawables
	void update();	///<update function
	void reset();	///<reset function

	Hero* testCollision(const sf::Sprite&);	///<tests collision
	bool isHeroDead();	///<true if hero is dead
};

#endif
