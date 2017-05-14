#include "Path.hpp"
#include <fstream>

void Path::loadPath(std::string pathFileName) {
	pathPoints.clear();
	sf::Vector2i next;
	std::fstream File(("data/path/"+pathFileName));
	while(!File.eof())
	{
		File >> next.x;
		File >> next.y;
		pathPoints.push_back(next);
	}
	File.close();
}

std::vector<sf::Vector2i>& Path::getPoints() {
	return pathPoints;
}