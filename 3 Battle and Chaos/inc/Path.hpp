/**
 * \class
 * Path in which the Creeps can move.
 * 
 */


#ifndef Path_HPP
#define Path_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Path {
private:
	std::vector<sf::Vector2i> pathPoints;	///<vector containing path points
public:
	void loadPath(std::string);	///<loads the path
	std::vector<sf::Vector2i>& getPoints();	///<returns address to the vector of points
};

#endif
