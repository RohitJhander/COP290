/**
 * \class
 * This class manage Towers represents a Base Tower.
 * 
 */


#ifndef TowerManager_HPP
#define TowerManager_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Tower.hpp"
#include "Team.hpp"
#include "BulletManager.hpp"
#include "SoundManager.hpp"

class Team;
class BulletManager;
class Tower;

class TowerManager {
private:
	Tower *selected_tower;
	std::vector<Tower* > towers;
	sf::RenderWindow& renderWindow;
	Team *opponentTeam;
	BulletManager *bulletManager;
	sf::Sound notEnoughMoneySound;
public:
	TowerManager(sf::RenderWindow&,Team*,BulletManager*);
	~TowerManager();

	bool isTowerSelected();	// returns true if a tower is selected
	void selectNoTower();	// no tower is selected
	void selectTowerAtPosition(sf::Vector2f);	// select tower placed at specified position
	bool selected_Tower_Has_More_Upgrades(); // returns true if the selected tower can be upgraded further
	bool upgradeSelectedTower(int);
	void upgradeTowerAtPosition(sf::Vector2f);
	void sellSelectedTower();
	bool addTower(sf::Vector2f,int,TowerType);	// add a tower at specified position
	int getLatestTowerPrice();
	Tower* getSelectedTower();
	Tower* getTowerAtPosition(sf::Vector2f);
	void sellTowerAtPosition(sf::Vector2f);
	
	void update();
	void reset();	// reset the list of towers
	void draw();	// draw all the towers
};

#endif
