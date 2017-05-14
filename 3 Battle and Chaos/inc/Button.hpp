/**
 * \class
 * This class manage UI buttons of the game.
 * 
 */
#ifndef Button_HPP
#define Button_HPP

#include <SFML/Graphics.hpp>
#include "DrawableContainer.hpp"

///Button required for the interaction of the player in the game.
class Button : public sf::Drawable {
private:
	sf::Sprite bsprite;
	sf::Texture btexture;
	sf::Font font;
	sf::Text text;
	bool visible;
	bool hovered;
	DrawableContainer *container;
public:
	Button(sf::Vector2f position, float height, float width, std::string textureFile, std::string text, DrawableContainer *myContainer);
	~Button();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(visible) {
			target.draw(bsprite);
			target.draw(text);
		}
	}
	void hover();
	void normal();
	const sf::Sprite& getSprite();
	void setVisible(bool b);
	bool isHover(sf::Vector2i mousePosition);
	void setText(std::string);
	void setTextColor(sf::Color);
};

#endif // Button_HPP
