#include "Tower.hpp"
#include "VectorHelper.hpp"

Tower::Tower(sf::Vector2f pos,int max_upgradeLevel,std::string textureFile,sf::RenderWindow& rw,Team *ot,BulletManager *bm,TowerType tType):
			GameObject(pos,max_upgradeLevel,textureFile,rw), 
			opponentTeam(ot),
			bulletManager(bm),
			bulletSound(*SoundManager::getInstance().getResource("Shoot_tower.wav")),
			rangeSound(*SoundManager::getInstance().getResource("range_tower.wav"))
{
	towerType = tType;
	
	sprite.setScale(0.5,0.5);
	sf::FloatRect box = sprite.getLocalBounds();
	sprite.setOrigin((float)box.width/2,(float)box.height/2);
	attack_speed = 1.5;
	range = 100.0f;
	damage = 10.0f;
	
	bulletSound.setVolume(40);
	rangeSound.setVolume(30);

	if(tType == DIMINISH || tType == DECAY) {
		for(int i=0; i<6; i++){
			fire[i].loadFromFile("data/images/tower/range/Fire" + std::to_string(i) + ".png");
		}		
	}else{
		for(int i=0; i<6; i++){
			fire[i].loadFromFile("data/images/tower/fire/Fire" + std::to_string(i) + ".png");
		}
	}
	tcount = 0;
	firing = false;

	if(towerType==POISON){
		sprite.setColor(sf::Color(100,255,100,255));
		attack_speed = 1.5;
		range = 90.0f;
		damage = 10.0f;
	}
	else if(towerType==SLOW){
		sprite.setColor(sf::Color(100,100,255,255));
		attack_speed = 1.2;
		range = 70.0f;
		damage = 8.0f;
	}
	else if(towerType==DECAY){
		sprite.setColor(sf::Color(255,100,100,255));
		attack_speed = 3.0;
		range = 100.0f;
		damage = 8.0f;
	}
	else if(towerType==PEIRCING){
		sprite.setColor(sf::Color(255,50,255,255));
		attack_speed = 1.5;
		range = 120.0f;
		damage = 10.0f;
	}
	else if(towerType==DIMINISH){
		sprite.setColor(sf::Color(255,255,100,255));
		attack_speed = 3.5f;
		range = 90.0f;
		damage = 6.0f;
	}
	else{
		sprite.setColor(sf::Color(255,255,255,255));
		attack_speed = 1.0;
		range = 100.0f;
		damage = 8.0f;
	}

	rangeShape.setRadius(range);
	rangeShape.setFillColor(sf::Color(255,255,255,100));
	rangeShape.setOutlineColor(sf::Color::Black);
	rangeShape.setPosition(pos);
	rangeShape.setOrigin(range,range);

	rangeEffect.setTexture(fire[0]);
	rangeEffect.setColor(sf::Color(255,255,255,100));

	rangeEffect.setPosition(pos);
	rangeEffect.setOrigin((float)box.width/2,(float)box.height/2);
}

Tower::~Tower() {}

float Tower::getRange() {
	return range;
}

void Tower::setRange(float range) {
	this->range = range;
}

float Tower::getDamage() {
	return damage;
}

void Tower::setDamage(float damage) {
	this->damage = damage;
}

float Tower::getAttack_speed() {
	return attack_speed;
}

void Tower::setAttack_speed(float attack_speed) {
	this->attack_speed = attack_speed;
}

TowerType Tower::getTowerType() {
	return towerType;
}

int Tower::getPrice() {
	int cost;
	switch(towerType) {
		case NORMAL : 
			cost = 10;
			break;
		case PEIRCING : 
			cost = 25;
			break;
		case POISON : 
			cost = 20;
			break;
		case DIMINISH : 
			cost = 30;
			break;
		case SLOW : 
			cost = 25;
			break;
		case DECAY : 
			cost = 15;
			break;
		default : 
			cost = 300;
	}
	return cost;
}

Creep* Tower::AI_getTarget(){
	Creep* target = NULL;
	switch(towerType){
		case PEIRCING:
			target = opponentTeam->getArmoredCreepInRange(position,range);
			if(target == NULL) target = opponentTeam->getStrongCreepInRange(position,range);
			break;
		case POISON:
			target = opponentTeam->getFirstCreepInRange(position,range);
			break;
		case SLOW:
			target = opponentTeam->getStrongCreepInRange(position,range);
			break;
		case NORMAL:
			target = opponentTeam->getWeakCreepInRange(position,range);
			break;
		default:
			target = NULL;
			break;
	}
	return target;
}

void Tower::update() {
	Creep* target = AI_getTarget();
	if(firing && (towerType!=DIMINISH) && (towerType!=DECAY)){
		sprite.setTexture(fire[tcount/2]);
		tcount++;
		if (tcount>11){
			tcount=0;
			firing=false;
		} 
	}
	if(firing && ((towerType==DIMINISH) || (towerType==DECAY))) {
		rangeEffect.setTexture(fire[tcount/2]);
		tcount++;
		if (tcount>11){
			tcount=0;
			firing=false;
		} 
	}

	rangeEffect.setScale(range/30,range/30);

	if(towerType == DIMINISH) {
		if(shootTimer.getElapsedTime() > (sf::seconds(attack_speed))) {
			opponentTeam->reduceMaxHealthInRange(position,range,damage);
			rangeSound.play();
			firing=true;
			shootTimer.restart();
		}
		return;
	}
	if(towerType == DECAY) {
		if(shootTimer.getElapsedTime() > (sf::seconds(attack_speed))) {
			opponentTeam->damageInRange(position,range,damage);
			rangeSound.play();
			firing=true;
			shootTimer.restart();
		}
		return;
	}
	if(target != NULL) {
		sf::Vector2f targetPosition = target->getPosition();
		sf::Vector2f direction = targetPosition - position;
		normalize(direction);
		float angle = angleBetweenD(sf::Vector2f(0,-1),direction);
		if(targetPosition.x <= position.x) {
			sprite.setRotation(360 - angle);
		}else {
			sprite.setRotation(angle);
		}
		if(shootTimer.getElapsedTime() > (sf::seconds(attack_speed))) {
			bulletManager->addBullet(new Bullet(position,1,"data/images/Bullet.png",renderWindow,opponentTeam,direction,damage,TOWERS,towerType));
			bulletSound.play();
			firing=true;
			shootTimer.restart();
		}
	}
}

void Tower::draw() {
	renderWindow.draw(sprite);
	if(firing && ((towerType==DECAY) || (towerType==DIMINISH))) {
		renderWindow.draw(rangeEffect);
	}
}

void Tower::drawWithRange() {
	renderWindow.draw(rangeShape);
}

void Tower::upgrade() {
	range += 15.0f;
	damage += 10.0f;
	attack_speed -= 0.2f;
	rangeShape.setRadius(range);
	rangeShape.setPosition(this->getPosition());
	rangeShape.setOrigin(range,range);
}

int Tower::getUpgradeCost() {
	return getPrice() * (upgradeLevel+1);
}

void Tower::incrementUpgradeLevel() {
	upgradeLevel++;
}
