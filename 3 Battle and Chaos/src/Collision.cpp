#include "Collision.hpp"
#include <iostream>
#include <math.h>

Collision::Collision() {}

Collision::~Collision() {}

bool Collision::PixelPerfectTest(const sf::Sprite& object1, const sf::Sprite& object2) {
	sf::FloatRect box1 = object1.getGlobalBounds();
    sf::FloatRect box2 = object2.getGlobalBounds();
    if (box1.intersects(box2)) {
    	return true;
    }
    return false;
}

bool Collision::CircleTest(const sf::Vector2f& Position1,float Radius1,const sf::Vector2f& Position2,float Radius2 )
{
	float xd = Position1.x - Position2.x;
	float yd = Position1.y - Position2.y;

	return sqrt(xd * xd + yd * yd) <= Radius1 + Radius2;
}