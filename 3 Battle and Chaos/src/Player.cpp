#include "Player.hpp"

Player::Player(sf::RenderWindow& rw, Window& w, Team *ot, BulletManager *bm) : 
			renderWindow(rw), window(w), opponentTeam(ot), bulletManager(bm) 
{}

Player::~Player() {
	reset();
}

void Player::init(int teamNumber) {
	if(teamNumber == 1) {
		// set appropriate position and texture of hero
		hero = new Hero(window.getBlockMiddlePosition(0,4),2,"data/images/Hero1.png",renderWindow,opponentTeam,bulletManager);
		window.setBlockCode(window.getBlockMiddlePosition(0,4),HERO);
	}else {
		hero = new Hero(window.getBlockMiddlePosition(33,12),2,"data/images/Hero2.png",renderWindow,opponentTeam,bulletManager);
		window.setBlockCode(window.getBlockMiddlePosition(33,12),HERO);
	}
}

sf::Vector2f Player::getPosition() {
	return hero->getPosition();
}

void Player::setPosition(sf::Vector2f pos){
	hero->move(pos);
}

float Player::getRotation() {
	return hero->getRotation();
}

void Player::setRotation(float f) {
	return hero->setRotation(f);
}

void Player::fireBullet() {
	hero->fireBullet();
}

bool Player::isHeroDead() {
	return hero->isDead();
}

void Player::move(bool w, bool s, bool a, bool d){
	if (w && !s) move(UP);
	if (!w && s) move(DOWN);
	if (a && !d) move(LEFT);
	if (!a && d) move(RIGHT);
}

void Player::move(Direction dir) {
	if(hero->isDead()) {
		return;
	}
	sf::Vector2f currPos = hero->getPosition();
	Code currBlockCode = window.getBlockCode(currPos);
	sf::Vector2f nextPos = hero->getNextPosition(dir);
	if(!window.isInsideWindow(nextPos)) {
		return;
	}
	Code nextBlockCode = window.getBlockCode(nextPos);
	// if hero is not on path
	if(currBlockCode == HERO) {
		switch(nextBlockCode){
			case HERO:
				hero->move(nextPos);
				break;
			case TOWER:
			case PATH:
				hero->move(nextPos);
				window.setBlockCode(currPos,NONE);
				break;
			case NONE:
				hero->move(nextPos);
				window.setBlockCode(nextPos,HERO);
				window.setBlockCode(currPos,NONE);
				break;
			default:
				break;
		}
	}else if(currBlockCode == PATH || currBlockCode == TOWER) {
		switch(nextBlockCode) {
			case NONE:
				hero->move(nextPos);
				window.setBlockCode(nextPos,HERO);
				break;
			case TOWER:
			case PATH:
				hero->move(nextPos);
				break;
			default:
				break;
		}
	}
}

void Player::draw() {
	if(!hero->isDead()) {
		hero->draw();
	}
}

void Player::update() {
	hero->update();
}

void Player::reset() {
	delete hero;
}

Hero* Player::testCollision(const sf::Sprite& object) {
	if(hero->isDead()){
		return NULL;
	}
	if(Collision::PixelPerfectTest(object,hero->getSprite())) {
		return hero;
	}
	return NULL;
}