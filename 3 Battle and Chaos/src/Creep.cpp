#include "Creep.hpp"

Creep::Creep(sf::Vector2f pos,int max_upgradeLevel,std::string textureFile,sf::RenderWindow& rw,CreepType cType):
			GameObject(pos,max_upgradeLevel,textureFile,rw)
{
	sprite.setScale(0.4,0.4);
	sf::FloatRect box = sprite.getLocalBounds();
	sprite.setOrigin((float)box.width/2,(float)box.height/2);
	direction = LEFT;
	movement_speed = sf::Vector2f(0.5,0.5);
	maxHealth = 100.0;
	health = maxHealth;
	dead = false;
	reached = false;
	nextCheckPoint = 1;
	creepType = cType;
	
	for(int i=0; i<6; i++){
		textures[i].loadFromFile("data/images/creep/Creep" + std::to_string(i) + ".png");
	}

	armor = 0;
	tcount = 0;
	decay = 0;
	pcounter = 0;
	decaytime = 0;

	switch(creepType) {
		case SWARM :
		{
			sprite.setScale(0.3,0.3);
			sf::Vector2f vel = Creep::get_movement_speed();
			set_movement_speed(sf::Vector2f(4*vel.x,4*vel.y));
			setHealth(getHealth()/3);
			maxHealth/=3;
			armor = 5;
			break;
		}
		case GIANT :
		{
			sprite.setScale(0.5,0.5);
			sf::Vector2f vel = Creep::get_movement_speed();
			set_movement_speed(sf::Vector2f(0.5*vel.x,0.5*vel.y));
			setHealth(getHealth()*5);
			maxHealth*=5;
			armor = 20;
			break;
		}
		case ARMOR :
		{
			sprite.setScale(0.4,0.4);
			setHealth(getHealth()*2);
			maxHealth*=2;
			armor = 50;
			break;
		}
		case REGEN :
		{
			sprite.setScale(0.4,0.4);
			setHealth(getHealth()*2);
			maxHealth*=2;
			armor = 5;
			break;
		}
		case SUPER :
		{
			sprite.setScale(0.7,0.7);
			setHealth(getHealth()*5);
			maxHealth*=5;
			armor = 50;
			break;
		}
		default :
			sprite.setScale(0.4,0.4);
			break;
	}

	box = sprite.getGlobalBounds();
	rBar = new sf::RectangleShape(sf::Vector2f(box.width, 5.0));
	gBar = new sf::RectangleShape(sf::Vector2f(box.width, 5.0));
	vBar = new sf::RectangleShape(sf::Vector2f(box.width, 5.0));
	rBar->setFillColor(sf::Color(250,0,0));
	vBar->setFillColor(sf::Color(125,125,5*armor));
	gBar->setFillColor(sf::Color(50,250,50));

	slowed = false;
}

Creep::~Creep() {}

sf::Vector2f Creep::get_movement_speed() {
	return movement_speed;
}

void Creep::set_movement_speed(sf::Vector2f movement_speed) {
	this->movement_speed = movement_speed;
}

float Creep::getHealth() {
	return health;
}

void Creep::setHealth(float health) {
	this->health = health;
}

void Creep::setArmor(float arm){
	armor = arm;
	vBar->setFillColor(sf::Color(125,125,5*armor));
}

float Creep::getArmor(){
	return armor;
}

CreepType Creep::getCreepType() {
	return creepType;
}

float Creep::getDecay() {
	return decay;
}

void Creep::setDamage(float damage) {
	if(damage >= armor)
		health = health - (damage-armor);
	else
		health = health - 0.0;
	gBar->setScale(float(health)/maxHealth,1.0);
	if(health <= 0.0){
		dead = true;
	}
}

bool Creep::isDead() {
	return dead;
}

void Creep::setDead(bool b) {
	dead = b ;
}

Direction Creep::getDirection() {
	return direction;
}

void Creep::setDirection(Direction dir) {
	direction = dir;
}

sf::Vector2f Creep::getNextPosition() {
	sf::Vector2f pos = position;
	switch(direction) {
		case LEFT:
			pos.x = (pos.x - movement_speed.x);
			break;
		case RIGHT:
			pos.x = (pos.x + movement_speed.x);
			break;
		case UP:
			pos.y = (pos.y - movement_speed.y);
			break;
		case DOWN:
			pos.y = (pos.y + movement_speed.y);
			break;
		default:
			break;
	}
	return pos;
}

float Creep::getBoundingCircleRadius() {
	sf::FloatRect box = sprite.getGlobalBounds();
	return (box.width + box.height) / 4;
}

int Creep::getNextCheckPoint() {
	return nextCheckPoint;
}

void Creep::incrementCheckPoint() {
	nextCheckPoint++;
}

int Creep::getPrice() {
	switch(creepType) {
		case SIMPLE : 
			return 20;
			break;
		case SWARM : 
			return 10;
			break;
		case ARMOR : 
			return 30;
			break;
		case GIANT : 
			return 75;
			break;
		case REGEN : 
			return 40;
			break;
		case SUPER : 
			return 150;
			break;
		default : 
			return 100;
	}
}

void Creep::update() {
	pcounter+=0.01f;
	if(pcounter > decaytime){
		pcounter=0;
		decay=0;
	}
	scounter+=0.01f;
	if(scounter > slowtime){
		scounter=0;
		if(slowed){
			movement_speed.x=movement_speed.x/(1-slow);
			movement_speed.y=movement_speed.y/(1-slow);
			slow=0;
			slowed = false;
		}
	}
	if(creepType==REGEN){
		if(health<maxHealth)
			health+=0.2f;
	}
	setDamage(decay+armor);
	sprite.setTexture(textures[tcount/4]);
	tcount++;
	if (tcount>23) tcount -= 24;
	if(decay!=0.0f)
		sprite.setColor(sf::Color(100,255,100,255));
	else
		sprite.setColor(sf::Color(255,255,255,255));
}

void Creep::reduceArmor(){
	armor--;
}

void Creep::dot(float fact,int tm) {
	pcounter=0;
	decay=fact;
	decaytime=tm;
}

void Creep::sot(float fact,int tm) {
	if(!slowed){
		movement_speed.x=movement_speed.x*(1-fact);
		movement_speed.y=movement_speed.y*(1-fact);
	}
	slowed = true;
	scounter=0;
	slow=fact;
	slowtime=tm;
}

void Creep::move(sf::Vector2f pos) {
	position = pos;
	sprite.setPosition(position);
	sf::FloatRect Box = sprite.getGlobalBounds();
	rBar->setPosition(position.x - Box.width/2, position.y - 5 - Box.height/2);
	gBar->setPosition(position.x - Box.width/2, position.y - 5 - Box.height/2);
	vBar->setPosition(position.x - Box.width/2, position.y - 10 - Box.height/2);
}

void Creep::draw(){
	renderWindow.draw(sprite);
	renderWindow.draw(*vBar);
	renderWindow.draw(*rBar);
	renderWindow.draw(*gBar);
}

bool Creep::isReached() {
	return reached;
}

void Creep::setReached() {
	reached = true;
}

void Creep::reduceMaxHealth(float damage) {
	if(maxHealth > (damage + 10)) {
		maxHealth -= damage;
	}
	if(maxHealth < health) {
		health = maxHealth;
	}
}