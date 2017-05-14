/**
 * \class
 * This class represents a team of the game.
 * 
 */

#ifndef Team_HPP
#define Team_HPP

#include "Player.hpp"
#include "TowerManager.hpp"
#include "CreepManager.hpp"
#include "BulletManager.hpp"
#include "Window.hpp"
#include "MyDefines.hpp"

#include <SFML/Network.hpp>
#include <string>

class BulletManager;
class CreepManager;
class TowerManager;
class Player;
class Hero;

class Team {
private:
	int teamNumber;
	int money;
	int teamLife;
	bool winningStatus;
	bool gameOver;
	std::map<sf::IpAddress, Player*> players;
	sf::RenderWindow& renderWindow;
	Window& window;
public:
	Player *player;
	TowerManager *towerManager;
	CreepManager *myCreepManager;
	BulletManager *bulletManager;
	Team *opponentTeam;
	
	Team(sf::RenderWindow&, Window&, Team*, bool);
	~Team();

	void setTeamNumber(int);
	int getTeamNumber();
	int getNumberOfPlayers();
	bool isMoneySufficient(int price);
	void decreaseMoney(int amount);
	void increaseMoney(int amount);
	int getMoney();
	int getTeamLife();

	bool getWinningStatus();
	void setWinningStatus(bool);

	bool isGameOver();
	void setGameOver(bool);

	void addPlayer(sf::IpAddress);
	void removePlayer(sf::IpAddress);
	
	void update();
	void draw();

	Creep* testCollisionWithCreeps(const sf::Sprite&);
	Hero* testCollisionWithHeroes(const sf::Sprite&);
	Creep* getFirstCreepInRange(sf::Vector2f,float);
	Creep* getArmoredCreepInRange(sf::Vector2f,float);
	Creep* getStrongCreepInRange(sf::Vector2f,float);
	Creep* getWeakCreepInRange(sf::Vector2f,float);
	
	bool addTower(sf::Vector2f,TowerType);
	bool startNextWave(CreepType);
	void init();
	void decreaseLife(int);
	bool isFound(sf::IpAddress);
	void setPlayerPosition(sf::IpAddress, sf::Vector2f);
	void setPlayerRotation(sf::IpAddress, float);
	void fireBullet(sf::IpAddress);

	void sellSelectedTower();
	bool upgradeSelectedTower();
	void sellTowerAtPosition(sf::Vector2f pos);
	void upgradeTowerAtPosition(sf::Vector2f pos);

	void damageInRange(sf::Vector2f pos, float range, float damage);
	void reduceMaxHealthInRange(sf::Vector2f pos, float range, float damage);
};

#endif
