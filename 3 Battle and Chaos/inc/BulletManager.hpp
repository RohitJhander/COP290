/**
 * \class
 * This class manage bullets fired by heroes.
 * 
 */
#ifndef BulletManager_HPP
#define BulletManager_HPP

#include <SFML/Graphics.hpp>
#include "CreepManager.hpp"
#include "Bullet.hpp"
#include "Window.hpp"
#include "Team.hpp"

class Team;
class Bullet;
///Manages/ Stores the bullets and updates them
class BulletManager {
private:
	std::vector<Bullet*> bullets;
	sf::RenderWindow& renderWindow;
	Window& window;
	Team *opponentTeam;
public:
	BulletManager(sf::RenderWindow&,Window&,Team*);
	~BulletManager();

	void addBullet(Bullet*);
	void update();
	void draw();
	void reset();
};

#endif