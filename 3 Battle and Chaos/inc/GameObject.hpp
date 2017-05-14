/*
* This class represents a general game object.
* It is inherited by Tower, Creep, Hero etc.
*/

#ifndef GameObject_HPP
#define GameObject_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class GameObject{
private:
protected:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
	int price;
	int upgradeLevel;
	int max_upgradeLevel;
	sf::RenderWindow& renderWindow;
public:
	GameObject(sf::RenderWindow& rw);
	GameObject(sf::Vector2f position,int max_upgradeLevel,std::string textureFile,sf::RenderWindow& rw);
	~GameObject();

	sf::Vector2f getPosition();
	int getUpgradeLevel();
	int get_Max_UpgradeLevel();
	const sf::Sprite& getSprite();

	virtual int getPrice() {};
	virtual void update() {};		// write the logic in child class
	virtual void draw() {
		renderWindow.draw(sprite);
	}	//write the logic in child class
};

#endif
