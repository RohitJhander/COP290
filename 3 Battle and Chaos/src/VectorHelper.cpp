#include "VectorHelper.hpp"
#include <math.h>
#include <iostream>

float RADTODEG(const float Radians)	{return static_cast<float>(Radians * 180.0f / PI);}
float DEGTORAD(const float Degrees) { return static_cast<float>(Degrees * PI / 180.0f);}

float length(const sf::Vector2f& vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

void normalize(sf::Vector2f& vec) {
	vec = sf::Vector2f(vec.x/length(vec),vec.y/length(vec));
}

float angleBetweenR(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return acos(Dot(v1,v2));
}

float angleBetweenD(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return RADTODEG(angleBetweenR(v1,v2));
}

float Dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return (v1.x * v2.x + v1.y * v2.y);
}

void rotateV(sf::Vector2f& v, float angle) {
	angle = DEGTORAD(angle);
	sf::Vector2f temp = v;
	v.x = temp.x * cos(angle) - temp.y * sin(angle);
	v.y = temp.x * sin(angle) + temp.y * cos(angle);
}