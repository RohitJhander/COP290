#include "BulletManager.hpp"
#include <iostream>

BulletManager::BulletManager(sf::RenderWindow& rw, Window& w, Team *ot) : renderWindow(rw) , window(w), opponentTeam(ot) {

}

BulletManager::~BulletManager() {
	reset();
}

void BulletManager::addBullet(Bullet* bullet) {
	bullets.push_back(bullet);
}

void BulletManager::update() {
	for(auto it = bullets.begin(); it!=bullets.end() ; ++it) {
		(*it)->update();
		if(!(window.isInsideWindow((*it)->getPosition()))){
			//std::cout<<"Bullet out of window\n";
			(*it)->setDead(true);
		}
		if((*it)->isDead()) {
			delete *it;
			it = bullets.erase(it);
			if(it == bullets.end()){
				break;
			}
		}
	}
}

void BulletManager::draw() {
	for(auto it = bullets.begin(); it!=bullets.end() ; ++it) {
		(*it)->draw();
	}
}

void BulletManager::reset() {
	for(auto it = bullets.begin(); it!=bullets.end() ; ++it) {
		delete *it;
	}
}