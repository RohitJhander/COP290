#include "Button.hpp"

Button::Button(sf::Vector2f position, float height, float width, std::string textureFile, std::string m_text, 
		 DrawableContainer *myContainer) {

	btexture.loadFromFile(textureFile);
	bsprite.setTexture(btexture);
	bsprite.setPosition(position);
	if (!font.loadFromFile("data/images/minimal.otf")){
        // error...
    }
    sf::FloatRect box = bsprite.getGlobalBounds();
	float scaleX = width/box.width;
	float scaleY = height/box.height;
	bsprite.setScale(scaleX,scaleY);
	
	text.setFont(font);
	text.setString(m_text);
	text.setPosition(position.x + width/3, position.y + height/5);
	text.setCharacterSize((int)(height/2));
    text.setColor(sf::Color::White);
	
	container = myContainer;
	visible = true;
	hovered = false;
}

Button::~Button() {}

const sf::Sprite& Button::getSprite(){
	return bsprite;
}

void Button::setVisible(bool b) {
	visible = b ;
}

void Button::hover(){
	if(!hovered){
		bsprite.setColor(sf::Color(155,50,250,255));
		hovered=true;
	}
}

void Button::normal(){
	if(hovered){
		bsprite.setColor(sf::Color(255,255,255,255));
		hovered=false;
	}
}

bool Button::isHover(sf::Vector2i mousePosition){
	if(!visible) {
		return false;
	}
	sf::FloatRect box = bsprite.getGlobalBounds();
	if(box.contains(sf::Vector2f(mousePosition.x,mousePosition.y))) {
		return true;
	}
	return false;
}

void Button::setText(std::string s){
	text.setString(s);
}

void Button::setTextColor(sf::Color color) {
	text.setColor(color);
}