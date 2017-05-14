/*
* This class represents a Hero.
*/

#ifndef Hero_HPP
#define Hero_HPP

#include "GameObject.hpp"
#include "MyDefines.hpp"
#include "Team.hpp"
#include "BulletManager.hpp"

#include <string>

class Team;
class BulletManager;

class Hero : public GameObject{
private:
	float health,maxHealth;
	float damage;
	float attack_speed;
	float movement_speed;
	float range;
	TowerType typ;
	bool dead;
	sf::Vector2f dir;
	Team *opponentTeam;
	BulletManager *bulletManager;
	sf::Clock reSpawnTimer;
	int numberOfDeaths;
	sf::Texture fire[5];
	int tcount;
public:
	Hero(sf::Vector2f,int,std::string,sf::RenderWindow&,Team*,BulletManager*);
	~Hero();

	float getHealth();
	void setHealth(float);
	float getDamage();
	void setDamage(float);
	float getAttack_speed();
	void setAttack_speed(float);
	float get_movement_speed();
	void set_movement_speed(float);
	float getRange();
	void setRange(float);

	float getRotation();
	void setRotation(float);

	int getPrice();

	sf::Vector2f getDirection();
	sf::Vector2f getNextPosition(Direction);
	void fireBullet();
	bool isDead();

	void update();
	void move(sf::Vector2f);
	void reSpawn();
};

#endif