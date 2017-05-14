#include "Block.hpp"

Block::Block() {}

Block::~Block() {}

void Block::setPosition(sf::Vector2f V) {
	drawing.setPosition(V);
}

void Block::setSize(sf::Vector2f V) {
	drawing.setSize(V);
}

void Block::setFillColor(sf::Color C) {
	drawing.setFillColor(C);
}

void Block::setCode(Code code) {
	this->code = code ;
}

Code Block::getCode() {
	return code;
}