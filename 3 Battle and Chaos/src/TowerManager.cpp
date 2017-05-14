#include "TowerManager.hpp"

TowerManager::TowerManager(sf::RenderWindow& rw,Team *ot,BulletManager *bm):
	renderWindow(rw),opponentTeam(ot),bulletManager(bm),
	notEnoughMoneySound(*SoundManager::getInstance().getResource("notEnoughMoney.wav"))
{
	selected_tower = NULL;
}

TowerManager::~TowerManager() {
	reset();
}

bool TowerManager::isTowerSelected() {
	return selected_tower != NULL;
}

void TowerManager::selectNoTower() {
	selected_tower = NULL;
}

void TowerManager::selectTowerAtPosition(sf::Vector2f pos) {
	for(auto it = towers.begin() ; it!=towers.end() ; ++it) {
		if(pos == (*it)->getPosition()){
			selected_tower = (*it);
		}
	}
}

bool TowerManager::selected_Tower_Has_More_Upgrades() {
	return selected_tower->getUpgradeLevel() < selected_tower->get_Max_UpgradeLevel();
}

bool TowerManager::upgradeSelectedTower(int money) {
	if(selected_Tower_Has_More_Upgrades()) {
		if(money > selected_tower->getUpgradeCost()) {
			selected_tower->upgrade();
			return true;
		}else{
			notEnoughMoneySound.play();
			return false;
		}
	}
	return false;
}

void TowerManager::upgradeTowerAtPosition(sf::Vector2f pos) {
	Tower *tower = getTowerAtPosition(pos);
	tower->upgrade();
	tower->incrementUpgradeLevel();
}

bool TowerManager::addTower(sf::Vector2f pos,int money,TowerType tType) {
	// create a new tower having position = pos and maximum 3 upgrade levels
	Tower* tower = new Tower(pos,3,"data/images/Tower.png",renderWindow,opponentTeam,bulletManager,tType);
	if(tower->getPrice() > money) {
		delete tower;
		notEnoughMoneySound.play();
		return false;
	}
	towers.push_back(tower);	// add this new tower to the list of towers	
	selected_tower = NULL;
	return true;
}

void TowerManager::update() {
	for(auto it = towers.begin() ; it != towers.end() ; ++it) {
		(*it)->update();
	}
}

void TowerManager::reset() {
	towers.clear();
	selected_tower = NULL;
}

void TowerManager::draw() {
	for(auto it = towers.begin() ; it!=towers.end() ; ++it) {
		(*it)->draw();
		if((*it) == selected_tower) {
			(*it)->drawWithRange();
		}
	}
}

int TowerManager::getLatestTowerPrice() {
	return towers[towers.size()-1]->getPrice();
}

Tower* TowerManager::getSelectedTower() {
	return selected_tower;
}

void TowerManager::sellSelectedTower() {
	for(auto it=towers.begin(); it!=towers.end(); ++it) {
		if((*it) == selected_tower) {
			it = towers.erase(it);
			return;
		}
	}
}

Tower* TowerManager::getTowerAtPosition(sf::Vector2f pos) {
	for(auto it=towers.begin(); it!=towers.end(); ++it) {
		if((*it)->getPosition() == pos){
			return (*it);
		}
	}
	return NULL;
}

void TowerManager::sellTowerAtPosition(sf::Vector2f pos) {
	for(auto it=towers.begin(); it!=towers.end(); ++it) {
		if((*it)->getPosition() == pos){
			it = towers.erase(it);
			return;
		}
	}
}