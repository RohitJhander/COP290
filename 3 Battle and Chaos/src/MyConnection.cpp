#include "MyConnection.hpp"
#include <iostream>

void MyConnection::addTower(sf::Vector2f position,TowerType tType) {
	sf::Packet packet;
	packet<<protocolID<<counter;
	counter++;
	int msg = 1003;
	packet<<msg<<position.x<<position.y<<int(tType);
	addToOutQ(packet);
}

void MyConnection::addHeroPosition(sf::Vector2f position, float angle) {
	sf::Packet packet;
	packet<<protocolID<<counter;
	counter++;
	int msg = 2005;
	packet<<msg<<position.x<<position.y<<angle;
	addToOutQ(packet);
}

void MyConnection::addHeroFireMessage() {
	sf::Packet packet;
	packet<<protocolID<<counter;
	counter++;
	int msg = 507;
	packet<<msg;
	addToOutQ(packet);
}

void MyConnection::addNextWaveMessage(CreepType cType) {
	sf::Packet packet;
	packet<<protocolID<<counter;
	counter++;
	int msg = 911;
	packet<<msg<<(int)cType;
	addToOutQ(packet);
}

void MyConnection::addSelectTowerAtPosition(sf::Vector2f pos) {
	sf::Packet packet;
	packet<<protocolID<<counter;
	counter++;
	int msg = 1311;
	packet<<msg<<pos.x<<pos.y;
	addToOutQ(packet);
}

void MyConnection::addUpgradeTowerAtPosition(sf::Vector2f pos) {
	sf::Packet packet;
	packet<<protocolID<<counter;
	counter++;
	int msg = 1517;
	packet<<msg<<pos.x<<pos.y;
	addToOutQ(packet);
}