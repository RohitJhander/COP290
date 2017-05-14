/**
 * \class
 * This class contains parameters of window.
 * 
 */

#ifndef Window_HPP
#define Window_HPP

#include "Block.hpp"
#include "Path.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Window {
private:
	int windowX,windowY;
	int gridX,gridY;
	int menuY;
	int gridSize;
	Block **grid;
	sf::RenderWindow &renderWindow;
	Path myPath;
	Path opponentPath;
public:
	Window(sf::RenderWindow &);
	~Window();

	// getter and setter functions
	int getWindowX();
	int getWindowY();
	int getGridSize();

	void initGrid();
	void drawGrid();
	void setBlockColor(int,int,sf::Color);
	void setBlockCode(int,int,Code);
	Code getBlockCode(int,int);
	void setBlockCode(sf::Vector2f,Code);
	Code getBlockCode(sf::Vector2f);
	bool isInsideWindow(int,int);				// checks if the position specified by (int,int) is inside the window
	bool isInsideWindow(sf::Vector2f);			// checks if the position is inside the window
	sf::Vector2f getMiddlePosition(int,int);	// get position of center of block specified by mouse coordinates(int,int)
	sf::Vector2f getBlockMiddlePosition(int,int); // get position of center of block with (row,column)
	void setPath(std::string, int team);					// set path as described in file
	std::vector<sf::Vector2i>& getPathPoints(int team);
	void initForMainGame();
};

#endif
