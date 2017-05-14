#include "Hero.hpp"
#include "VectorHelper.hpp"
#include <iostream>

Hero::Hero(sf::Vector2f pos,int max_upgradeLevel,std::string textureFile,sf::RenderWindow& rw,Team *ot,BulletManager *bm):
		GameObject(pos,max_upgradeLevel,textureFile,rw),
		opponentTeam(ot),bulletManager(bm) 
{
	typ = NORMAL;

	for(int i=0; i<5; i++) {
		fire[i].loadFromFile("data/images/hero" + std::to_string(3-opponentTeam->getTeamNumber()) + "/hero" + std::to_string(i) + ".png");
	}
	tcount=0;
	sprite.setTexture(fire[0]);
	sprite.setScale(1.0,1.0);
	movement_speed = 3.5;
	sf::FloatRect box = sprite.getLocalBounds();
	sprite.setOrigin((float)box.width/2,(float)box.height/2);
	dir = sf::Vector2f(0,-1);
	damage = 5.0f;
	maxHealth = 50;
	health = maxHealth;
	dead = false;
	numberOfDeaths = 0;
}

Hero::~Hero() {}

float Hero::getDamage() {
	return damage;
}

void Hero::setDamage(float damage) {
	health -= damage;
	if(health <= 0.0f){
		dead = true;
		numberOfDeaths++;
		reSpawnTimer.restart();
		opponentTeam->increaseMoney((getPrice()*numberOfDeaths)/2);
	}
}

float Hero::getAttack_speed() {
	return attack_speed;
}

void Hero::setAttack_speed(float attack_speed) {
	this->attack_speed = attack_speed;
}

float Hero::get_movement_speed() {
	return movement_speed;
}

void Hero::set_movement_speed(float movement_speed) {
	this->movement_speed = movement_speed;
}

float Hero::getRange() {
	return range;
}

void Hero::setRange(float range) {
	this->range = range;
}

sf::Vector2f Hero::getDirection() {
	return dir;
}

float Hero::getRotation() {
	return sprite.getRotation();
}

void Hero::setRotation(float angle) {
	sprite.setRotation(angle);
	dir.x = 0.0f;
	dir.y = -1.0f;
	rotateV(dir,angle);	
}

int Hero::getPrice() {
	switch(upgradeLevel) {
		case 0 : 
			return 100;
			break;
		case 1 : 
			return 150;
			break;
		case 2 : 
			return 200;
			break;
		case 3 : 
			return 250;
			break;
		default : 
			return 300;
	}
}

sf::Vector2f Hero::getNextPosition(Direction direction) {
	sf::Vector2f pos = position;
	switch(direction) {
		case UP:
			pos.x = (pos.x + movement_speed * dir.x);
			pos.y = (pos.y + movement_speed * dir.y);
			break;
		case DOWN:
			pos.x = (pos.x - movement_speed * dir.x);
			pos.y = (pos.y - movement_speed * dir.y);
			break;
		case LEFT:
			sprite.rotate(-4.0);
			rotateV(dir,-4.0);
			break;
		case RIGHT:
			sprite.rotate(4.0);
			rotateV(dir,4.0);
			break;
		default:
			break;
	}
	return pos;
}

void Hero::fireBullet() {
	bulletManager->addBullet(new Bullet(position,1,"data/images/Bullet.png",renderWindow,opponentTeam,dir,damage,HEROS,typ));
}

void Hero::update() {
	sprite.setTexture(fire[tcount/3]);
	tcount++;
	if(tcount > 14)
		tcount = 0 ;
	if(dead && reSpawnTimer.getElapsedTime() > (sf::seconds(5.0f))) {
		reSpawn();
	}
}

void Hero::move(sf::Vector2f pos) {
	position = pos;
	sprite.setPosition(position);
}

bool Hero::isDead() {
	return dead;
}

void Hero::reSpawn() {
	health = maxHealth;
	dead = false;
}
