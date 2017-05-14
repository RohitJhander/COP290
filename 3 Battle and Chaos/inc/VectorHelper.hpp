#ifndef VectorHelper_HPP
#define VectorHelper_HPP

#include <SFML/System/Vector2.hpp>

#ifndef PI
#define PI (3.14159265358979323846)
#endif

float RADTODEG(const float Radians);
float DEGTORAD(const float Degrees);

float length(const sf::Vector2f&);
void normalize(sf::Vector2f&);
float angleBetweenR(const sf::Vector2f&, const sf::Vector2f&);
float angleBetweenD(const sf::Vector2f&, const sf::Vector2f&);
float Dot(const sf::Vector2f&, const sf::Vector2f&);
void rotateV(sf::Vector2f&,float);

#endif