#include "Bullet.hpp"
#include "VectorHelper.hpp"
#include <iostream>

Bullet::Bullet(sf::Vector2f pos,int max_upgradeLevel,std::string textureFile,sf::RenderWindow& rw,Team *ot,sf::Vector2f dir,float dmg,BulletID id,TowerType bul) : 
				GameObject(pos,max_upgradeLevel,textureFile,rw),opponentTeam(ot) {
	bultyp = bul;
	dead = false;
	damage = dmg;
	direction = dir;
	sf::FloatRect box = sprite.getLocalBounds();
	sprite.setOrigin(float(box.width)/2,float(box.height)/2);
	float angle = angleBetweenD(sf::Vector2f(0,-1), direction);
	if (direction.x < 0){
		sprite.setRotation(360 - angle);
	}else {
		sprite.setRotation(angle);
	}
	this->id = id;
}

Bullet::~Bullet() {}

bool Bullet::isDead() {
	return dead;
}

void Bullet::setDead(bool b) {
	dead = b;
}

void Bullet::update() {
	//move sprite according to speed
	position.x += direction.x * 5.0f;
	position.y += direction.y * 5.0f;
	sprite.setPosition(position);
	//test collision with any creep
	if(id == TOWERS) {
		Creep* target = opponentTeam->testCollisionWithCreeps(this->getSprite());
		if(target != NULL) {
			// set damage to creep
			target->setDamage(damage);
			if(bultyp == POISON)
				target->dot(0.1f,1);
			if(bultyp == SLOW)
				target->sot(0.5f,2);
			if(bultyp == PEIRCING)
				target->reduceArmor();
			dead = true;
		}
	}else if(id == HEROS) {
		Hero* target = opponentTeam->testCollisionWithHeroes(this->getSprite());
		if(target != NULL) {
			target->setDamage(damage);
			dead = true;
		} else {
			//std::cout<<"NULL aaya hai"<<std::endl;
		}
	}
}

TowerType Bullet::getType(){
	return bultyp;
}
