/* 
* This class manages creeps of a player.
*/

#ifndef CreepManager_HPP
#define CreepManager_HPP

#include "Creep.hpp"
#include "Window.hpp"
#include "Team.hpp"
#include "Collision.hpp"
#include "VectorHelper.hpp"
#include "SoundManager.hpp"

#include <vector>
#include <stack>

class Team;

class CreepManager {
private:
	std::vector<Creep* > creeps;
	sf::RenderWindow& renderWindow;
	Window& window;
	sf::Clock waveTimer;
	std::stack<CreepType> creepTypes;
	std::vector<sf::Vector2i> pathPoints;
	Team *opponentTeam;
	int creepsRemaining;
	sf::Sound notEnoughMoneySound;
public:
	CreepManager(sf::RenderWindow&, Window&,Team*);
	~CreepManager();

	void init();	// get correct path points

	Creep* testCollision(const sf::Sprite&);
	Creep* getFirstCreepInRange(sf::Vector2f,float);
	Creep* getArmoredCreepInRange(sf::Vector2f,float);
	Creep* getStrongCreepInRange(sf::Vector2f,float);
	Creep* getWeakCreepInRange(sf::Vector2f,float);

	void damageInRange(sf::Vector2f,float,float);
	void reduceMaxHealthInRange(sf::Vector2f,float,float);

	int startNextWave(int money,CreepType cType); // return -1 if money is not sufficient else price of creep to be added in next update call
	void update();
	void reset();
	void draw();

	void setCreepDirection(Creep*,sf::Vector2i,sf::Vector2i);
};

#endif