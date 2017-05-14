/**
 * \class Block
 * Grid underneath the working of the game.
 */

#ifndef Block_HPP
#define Block_HPP

#include <SFML/Graphics.hpp>

/** 
 * \defgroup TYPEDEFS Typedefs/Enums
 * @{
 */
enum Code{
	NONE,TOWER,CREEP,HERO,PATH,MENU,TOOL
};
/** @} */

///Stores the data of a grid.
class Block {
private:
	Code code;
public:
	Block(); ///<Constructor
	~Block(); ///<Destructor
	sf::RectangleShape drawing; ///<Drawing rectangle shown in the grid.
	void setPosition(sf::Vector2f); ///<Set position of the grid contents.
    void setSize(sf::Vector2f); ///<set the size of grid (default used is 40*40 pixels)
    void setFillColor(sf::Color); ///<set the fill color of the rectangle

    void setCode(Code); ///<set contents of the grid. Argument enum Code
    Code getCode(); ///<get contents of the grid. Return type enum Code
};

#endif //Block_HPP