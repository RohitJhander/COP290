#include "GameObject.hpp"

GameObject::GameObject(sf::RenderWindow& rw) : renderWindow(rw) {
	sf::Vector2f pos(0.0f,0.0f);
}

GameObject::GameObject(sf::Vector2f position, int max_upgradeLevel, std::string textureFile,sf::RenderWindow& rw) : renderWindow(rw) {
	this->position = position;
	this->upgradeLevel = 0 ;
	this->max_upgradeLevel = max_upgradeLevel;
	texture.loadFromFile(textureFile);
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

GameObject::~GameObject(){}

sf::Vector2f GameObject::getPosition() {
	return position;
}

int GameObject::getUpgradeLevel() {
	return upgradeLevel;
}

int GameObject::get_Max_UpgradeLevel() {
	return max_upgradeLevel;
}

const sf::Sprite& GameObject::getSprite() {
	return sprite;
}
