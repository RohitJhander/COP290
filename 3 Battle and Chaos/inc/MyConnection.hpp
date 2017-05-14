/**
 * \class
 * This class contains various connection methods  
 * 
 */

#ifndef MyConnection_HPP
#define MyConnection_HPP

#include "Connection.hpp"
#include "MyDefines.hpp"

class MyConnection : public Connection {
private:
public:
	void addTower(sf::Vector2f position,TowerType tType);	///<add Tower message
	void addHeroPosition(sf::Vector2f position,float angle);	///<add Hero Position message
	void addHeroFireMessage();	///<message for hero bullet fire
	void addNextWaveMessage(CreepType cType);	///<message for adding new creep wave
	void addSelectTowerAtPosition(sf::Vector2f pos);	///<select tower message
	void addUpgradeTowerAtPosition(sf::Vector2f pos);	///<upgrade tower message
};

#endif // MyConnection_HPP
