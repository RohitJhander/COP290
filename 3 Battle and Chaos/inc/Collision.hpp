/**
 * \class
 * This class manage collisions in the game.
 * 
 */

#ifndef Collision_HPP
#define	Collision_HPP

#include <SFML/Graphics.hpp>
///Testing collisions of drawing in the game with each other.
class Collision {
private:
	Collision();
public:
	~Collision();

	static bool PixelPerfectTest(const sf::Sprite&,const sf::Sprite&);
	static bool CircleTest(const sf::Vector2f&,float,const sf::Vector2f&,float);
	//static bool PixelPerfectTest(const sf::Sprite& Object , sf::Vector2f Point, sf::Uint8 AlphaLimit = 127);
};

#endif
