/**
 * \class
 * This class contains a various drawing methods used in game. 
 * 
 */

#ifndef DrawableContainer_HPP
#define DrawableContainer_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class DrawableContainer : public sf::Drawable {
private:
	std::vector<sf::Drawable* > drawables;
public:
	DrawableContainer() {}
	~DrawableContainer() {
		for(auto it = drawables.begin() ; it != drawables.end() ; ++it) {
			delete *it;
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (auto it = drawables.begin(); it != drawables.end(); ++it) {
			target.draw(**it);
		}
	}

	void addDrawable(sf::Drawable *drawable) {
		drawables.push_back(drawable);
	}
};
#endif // DrawableContainer_HPP
