/**
 * \class
 * This class represents a Base Tower.
 * It is inherited by FireTower, FreezeTower etc..
 * 
 */


#ifndef Tower_HPP
#define Tower_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Team.hpp"
#include "BulletManager.hpp"
#include "SoundManager.hpp"
#include "MyDefines.hpp"

class BulletManager;

class Tower : public GameObject{
private:
	float range;
	float damage;
	float attack_speed;
	sf::CircleShape rangeShape;
	sf::Clock shootTimer;
	sf::Sound bulletSound;
	Team *opponentTeam;
	BulletManager *bulletManager;
	TowerType towerType;
	sf::Texture fire[6];
	bool firing;
	int tcount;
	sf::Sound rangeSound;
	sf::Sprite rangeEffect;
	Creep* AI_getTarget();
	
public:
	Tower(sf::Vector2f,int,std::string,sf::RenderWindow&,Team*,BulletManager*,TowerType);
	~Tower();
	
	float getRange();
	void setRange(float);
	float getDamage();
	void setDamage(float);
	float getAttack_speed();
	void setAttack_speed(float);

	TowerType getTowerType();
	
	int getPrice();
	void update();
	void draw();
	void drawWithRange();
	void upgrade();
	int getUpgradeCost();
	void incrementUpgradeLevel();
};

#endif
