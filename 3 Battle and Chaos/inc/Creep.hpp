/*
* This class represents a Creep (Enemy).
*/

#ifndef Creep_HPP
#define Creep_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "GameObject.hpp"
#include "MyDefines.hpp"

///Container for the creeps/ enemies on the screen and information about them.
class Creep : public GameObject{
private:
	sf::Vector2f movement_speed;
	bool dead;
	bool slowed;
	CreepType creepType;
	bool reached;
	float health;
	float armor;
	float maxHealth;
	Direction direction;
	int nextCheckPoint;
	sf::RectangleShape *rBar, *gBar, *vBar;
	sf::Texture textures[6];
	int tcount;
	float pcounter;
	float decay;
	float decaytime;
	float scounter;
	float slow;
	float slowtime;
public:
	Creep(sf::Vector2f,int,std::string,sf::RenderWindow&,CreepType);
	~Creep();

	sf::Vector2f get_movement_speed();
	void set_movement_speed(sf::Vector2f);
	float getHealth();
	void setHealth(float);
	void setDamage(float);
	bool isDead();
	void setDead(bool);
	Direction getDirection();
	void setDirection(Direction);
	sf::Vector2f getNextPosition();
	float getBoundingCircleRadius();
	int getNextCheckPoint();
	void incrementCheckPoint();

	void setArmor(float);
	float getArmor();
	CreepType getCreepType();
	float getDecay();
	void reduceArmor();
	void dot(float,int);	//damage over time, arguments: factor,time
	void sot(float,int);	//slow over time
	
	int getPrice();
	void update();
	void move(sf::Vector2f);
	void draw();

	bool isReached();
	void setReached();
	void reduceMaxHealth(float damage);
};

#endif