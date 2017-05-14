/**
 * \class
 * This class represents bullets fired by heroes/towers.
 * 
 */

#ifndef Bullet_HPP
#define Bullet_HPP

#include "MyDefines.hpp"
#include "GameObject.hpp"
#include "Team.hpp"

enum BulletID {HEROS,TOWERS};

class Team;
///Bullet object for the game.
class Bullet : public GameObject {
private:
	TowerType bultyp; ///<Type of bullet according to the type of the tower.
	bool dead; ///<True if the bullet is dead.
	float damage; ///<Maximum damage the bullet can cause.
	sf::Vector2f direction; ///<Vector direction of the velocity of the bullet
	Team *opponentTeam; ///<Pointer to the opponent team relative to the bullet
	Team *myTeam; ///<Pointer to the my team relative to the bullet
	BulletID id; ///<Bullet from HEROES or the TOWERS
public:
	Bullet(sf::Vector2f,int,std::string,sf::RenderWindow&,Team*,sf::Vector2f,float,BulletID,TowerType); ///<Constructor
	~Bullet(); ///<Destructors
	TowerType getType(); ///<get the type of the bullet according to the type of the tower.

	bool isDead(); ///<get status of the bullet, dead or not.
	void setDead(bool); ///<set the status of the bullet, dead.
	void update(); ///<Update/ Animate the bullet at each frame of the game.
};

#endif