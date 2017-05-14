#include "Team.hpp"

Team::Team(sf::RenderWindow& rw, Window& w, Team *ot, bool isMyTeam) : 
		renderWindow(rw), window(w), opponentTeam(ot)
{
	money = 500;
	teamLife = 10;
	winningStatus = false;
	gameOver = false;
	myCreepManager = new CreepManager(rw,w,ot);
	bulletManager = new BulletManager(rw,w,ot);
	if(isMyTeam) {
		player = new Player(renderWindow,window,ot,bulletManager);
	}else {
		player = NULL;
	}
	towerManager = new TowerManager(rw,ot,bulletManager);
}

Team::~Team() {

}

void Team::setTeamNumber(int teamNumber) {
	this->teamNumber = teamNumber;
}

int Team::getTeamNumber() {
	return teamNumber;
}

int Team::getNumberOfPlayers() {
	return players.size();
}

bool Team::isMoneySufficient(int price) {
	return (money >= price) ;
}

void Team::decreaseMoney(int amount) {
	money -= amount;
}

void Team::increaseMoney(int amount) {
	money += amount;
}

int Team::getMoney() {
	return money;
}

int Team::getTeamLife() {
	return teamLife;
}

bool Team::getWinningStatus() {
	return winningStatus;
}

void Team::setWinningStatus(bool b) {
	winningStatus = true;
}

void Team::addPlayer(sf::IpAddress ip) {
	Player *newPlayer = new Player(renderWindow,window,opponentTeam,bulletManager);
	players[ip] = newPlayer;
}

void Team::update() {
	towerManager->update();
	bulletManager->update();
	myCreepManager->update();
	if(player != NULL) player->update();
	for(auto it = players.begin(); it != players.end(); ++it) {
		it->second->update();
	}
}

void Team::draw() {
	towerManager->draw();
	bulletManager->draw();
    myCreepManager->draw();
    if(player != NULL) player->draw();
    for(auto it = players.begin(); it != players.end(); ++it) {
		it->second->draw();
	}
}

Creep* Team::testCollisionWithCreeps(const sf::Sprite& object) {
	return myCreepManager->testCollision(object);
}

Hero* Team::testCollisionWithHeroes(const sf::Sprite& object) {
	Hero* target;
	for (auto it = players.begin(); it != players.end(); ++it) {
		target = it->second->testCollision(object);
		if(target != NULL) return target;
	}
	if (player != NULL) return player->testCollision(object);
	return NULL;
}

Creep* Team::getFirstCreepInRange(sf::Vector2f pos, float range) {
	return myCreepManager->getFirstCreepInRange(pos,range);
}

Creep* Team::getArmoredCreepInRange(sf::Vector2f pos,float range){
	return myCreepManager->getArmoredCreepInRange(pos,range);
}

Creep* Team::getStrongCreepInRange(sf::Vector2f pos,float range){
	return myCreepManager->getStrongCreepInRange(pos,range);
}

Creep* Team::getWeakCreepInRange(sf::Vector2f pos,float range){
	return myCreepManager->getWeakCreepInRange(pos,range);
}

bool Team::addTower(sf::Vector2f pos, TowerType tType) {
	if(towerManager->addTower(pos,money,tType)) {
		money -= towerManager->getLatestTowerPrice();
		return true;
	}
	return false;
}

bool Team::startNextWave(CreepType cType) {
	int price = myCreepManager->startNextWave(money,cType); 
	if(price != -1) {
		money -= price ;
		return true;
	}
	return false;
}

void Team::init() {
	myCreepManager->init();
	if(player != NULL) {
		player->init(getTeamNumber());
	}
	for(auto it = players.begin() ; it != players.end() ; ++it) {
		it->second->init(getTeamNumber());
	}
}

void Team::decreaseLife(int n) {
	teamLife -= n;
	if(teamLife <= 0) {
		opponentTeam->setWinningStatus(true);
		opponentTeam->setGameOver(true);
		this->gameOver = true;
	}
}

void Team::setGameOver(bool b) {
	gameOver = b;
}

bool Team::isGameOver() {
	return gameOver;
}

bool Team::isFound(sf::IpAddress ip) {
	return players.count(ip) != 0;
}

void Team::setPlayerPosition(sf::IpAddress ip, sf::Vector2f pos){
	players[ip]->setPosition(pos);
}

void Team::setPlayerRotation(sf::IpAddress ip, float angle){
	players[ip]->setRotation(angle);
}

void Team::fireBullet(sf::IpAddress ip){
	players[ip]->fireBullet();
}

void Team::sellSelectedTower() {
	Tower *selectedTower = towerManager->getSelectedTower();
	money += (selectedTower->getPrice() * 3)/4;
	sf::Vector2f heroPos = player->getPosition();
	sf::Vector2f selectedTowerPos = selectedTower->getPosition();
	if(window.getMiddlePosition(heroPos.x,heroPos.y) == window.getMiddlePosition(selectedTowerPos.x,selectedTowerPos.y)) {
		// hero is on the same square as tower
		window.setBlockCode(selectedTowerPos,HERO);
	}else {
		window.setBlockCode(selectedTowerPos,NONE);
	}
	towerManager->sellSelectedTower();
}

bool Team::upgradeSelectedTower() {
	if(towerManager->upgradeSelectedTower(money)) {
		Tower *selectedTower = towerManager->getSelectedTower();
		money -= (selectedTower->getUpgradeCost());
		selectedTower->incrementUpgradeLevel();
		return true;
	}
	return false;
}

void Team::sellTowerAtPosition(sf::Vector2f pos) {
	Tower *tower = towerManager->getTowerAtPosition(pos);
	if(tower == NULL) {
		#ifdef PRINT
			std::cout<<"no tower at position "<<pos.x<<" "<<pos.y<<std::endl;
		#endif
		return;
	}
	money += (tower->getPrice() * 3)/4;
	towerManager->sellTowerAtPosition(pos);
}

void Team::upgradeTowerAtPosition(sf::Vector2f pos) {
	Tower *tower = towerManager->getTowerAtPosition(pos);
	if(tower == NULL) {
		#ifdef PRINT
			std::cout<<"no tower at position "<<pos.x<<" "<<pos.y<<std::endl;
		#endif
		return;
	}
	money -= tower->getUpgradeCost();
	towerManager->upgradeTowerAtPosition(pos);
}

void Team::removePlayer(sf::IpAddress ip){
	players.erase(ip);
}

void Team::damageInRange(sf::Vector2f pos, float range, float damage) {
	myCreepManager->damageInRange(pos,range,damage);
}

void Team::reduceMaxHealthInRange(sf::Vector2f pos, float range, float damage) {
	myCreepManager->reduceMaxHealthInRange(pos,range,damage);
}