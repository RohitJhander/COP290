#include "CreepManager.hpp"

CreepManager::CreepManager(sf::RenderWindow& rw, Window& w, Team *ot):
	renderWindow(rw), window(w), opponentTeam(ot),
	notEnoughMoneySound(*SoundManager::getInstance().getResource("notEnoughMoney.wav"))
{
	creepsRemaining = 0;
}

CreepManager::~CreepManager() {
	reset();
}

void CreepManager::init() {
	pathPoints = window.getPathPoints(3-opponentTeam->getTeamNumber());
}

Creep* CreepManager::testCollision(const sf::Sprite& bulletSprite) {
	for(auto it = creeps.begin() ; it != creeps.end() ; ++it) {
		if(Collision::PixelPerfectTest(bulletSprite,(*it)->getSprite())) {
			return (*it);
		}
	}
	return NULL;
}

Creep* CreepManager::getFirstCreepInRange(sf::Vector2f pos,float range) {
	for(auto it = creeps.begin() ; it != creeps.end() ; ++it) {
		if (Collision::CircleTest((*it)->getPosition(),(*it)->getBoundingCircleRadius(),pos,range)){
			return (*it);
		}
	}
	return NULL;
}

Creep* CreepManager::getArmoredCreepInRange(sf::Vector2f pos, float range) {
	float armor = 0.0f;
	Creep *target = NULL;
	for(auto it = creeps.begin() ; it != creeps.end() ; ++it) {
		if (((*it)->getArmor() > armor) && Collision::CircleTest((*it)->getPosition(),(*it)->getBoundingCircleRadius(),pos,range)){
			target = (*it);
			armor = (*it)->getArmor();
		}
	}
	if(target != NULL) return target;
	else return NULL;
}

Creep* CreepManager::getStrongCreepInRange(sf::Vector2f pos, float range) {
	float health = 0.0f;
	Creep *target = NULL;
	for(auto it = creeps.begin() ; it != creeps.end() ; ++it) {
		if (((*it)->getHealth() > health) && Collision::CircleTest((*it)->getPosition(),(*it)->getBoundingCircleRadius(),pos,range)){
			target = *it;
			health = (*it)->getHealth();
		}
	}
	if(target != NULL) return target;
	else return NULL;
}

Creep* CreepManager::getWeakCreepInRange(sf::Vector2f pos, float range) {
	float health = 10000.0f;
	Creep *target = NULL;
	for(auto it = creeps.begin() ; it != creeps.end() ; ++it) {
		if (((*it)->getHealth() < health) && Collision::CircleTest((*it)->getPosition(),(*it)->getBoundingCircleRadius(),pos,range)){
			target = *it;
			health = (*it)->getHealth();
		}
	}
	if(target != NULL) return target;
	else return NULL;
}

int CreepManager::startNextWave(int money, CreepType cType) {
	Creep *creep = new Creep(sf::Vector2f(0,0),3,"data/images/Creep.png",renderWindow,cType);
	if(creep->getPrice() > money) {
		delete creep;
		notEnoughMoneySound.play();
		return -1;
	}
	creepsRemaining++;
	int price = creep->getPrice();
	creepTypes.push(cType);
	delete creep; 
	return price;
}

void CreepManager::update() {
	if(waveTimer.getElapsedTime() > (sf::seconds(1.5)) && (creepsRemaining > 0)) {
		sf::Vector2i startPosition = pathPoints[0];
		Creep *creep = new Creep(window.getBlockMiddlePosition(startPosition.x,startPosition.y),3,"data/images/Creep.png",renderWindow,creepTypes.top());
		setCreepDirection(creep,startPosition,pathPoints[1]);
		creeps.push_back(creep);
		creepsRemaining--;
		creepTypes.pop();
		waveTimer.restart();
	}
	for(auto it = creeps.begin() ; it != creeps.end() ; ++it) {
		// if the creep reaches at the opponent's base
		if((*it)->isReached()){
			#ifdef PRINT
				std::cout<<"creep reached\n";
			#endif
			opponentTeam->decreaseLife(1);
			delete *it;
			it = creeps.erase(it);
			if(it == creeps.end()){
				break;
			}
		}
		if((*it)->isDead()) {
			#ifdef PRINT
				std::cout<<"creep dead\n";
			#endif
			opponentTeam->increaseMoney((*it)->getPrice()/5);
			delete *it;
			it = creeps.erase(it);
			if(it == creeps.end()){
				break;
			}
		}
		(*it)->update();
		sf::Vector2f currPos = (*it)->getPosition();
		int nextCheckPointIndex = (*it)->getNextCheckPoint();
		sf::Vector2i nextCheckPoint = pathPoints[nextCheckPointIndex];
		sf::Vector2f pos = window.getBlockMiddlePosition(nextCheckPoint.x,nextCheckPoint.y);
		//length function defined in vectorHelper
		if(length(pos-currPos) < ((*it)->get_movement_speed().x)) {
			// last checkPoint
			if(nextCheckPointIndex == pathPoints.size()-1) {
				(*it)->setReached();
			}else {
				sf::Vector2i newNextCheckPoint = pathPoints[nextCheckPointIndex+1];
				setCreepDirection(*it,nextCheckPoint,newNextCheckPoint);
			}
			(*it)->incrementCheckPoint();
		}

		sf::Vector2f nextPos = (*it)->getNextPosition();
		if(!window.isInsideWindow(nextPos)) {
			(*it)->setDead(true);
		}else {
			(*it)->move(nextPos);
		}
	}
}

void CreepManager::reset() {
	for(auto it = creeps.begin() ; it!=creeps.end() ; ++it) {
		delete *it;
	}
	creeps.clear();
}

void CreepManager::draw() {
	for(auto it = creeps.begin() ; it!=creeps.end() ; ++it) {
		(*it)->draw();
	}
}

void CreepManager::setCreepDirection(Creep *creep, sf::Vector2i currCheckPoint, sf::Vector2i nextCheckPoint) {
	sf::Vector2i diff = nextCheckPoint - currCheckPoint;			
	if(diff.x == 0) {
		if(diff.y < 0){
			(creep)->setDirection(UP);
		}else{
			(creep)->setDirection(DOWN);
		}
	}else{
		if(diff.x > 0){
			(creep)->setDirection(RIGHT);
		}else{
			(creep)->setDirection(LEFT);
		}
	}
}

void CreepManager::damageInRange(sf::Vector2f pos, float range, float damage) {
	for(auto it = creeps.begin() ; it != creeps.end() ; ++it) {
		if (Collision::CircleTest((*it)->getPosition(),(*it)->getBoundingCircleRadius(),pos,range)){
			(*it)->setDamage(damage);
		}
	}
}

void CreepManager::reduceMaxHealthInRange(sf::Vector2f pos, float range, float damage) {
	for(auto it = creeps.begin() ; it != creeps.end() ; ++it) {
		if (Collision::CircleTest((*it)->getPosition(),(*it)->getBoundingCircleRadius(),pos,range)){
			(*it)->reduceMaxHealth(damage);
		}
	}	
}
