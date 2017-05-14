#include "MainGameState.hpp"

#include <iostream>

MainGameState::MainGameState(sf::RenderWindow& rw, StateManager& sm, Window& w,Team& mt,Team& ot,MyConnection& c):
	GameState(rw,sm,w,mt,ot,c),
	bulletSound(*SoundManager::getInstance().getResource("Shoot.wav"))
{
	backgroundTexture.loadFromFile("data/images/background.jpg");
	backgroundTexture.setSmooth(true);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(1.0,1.0);
	tpanel.loadFromFile("data/images/Panel.jpg");
	panel.setTexture(tpanel);
	panel.setPosition(0,645);

	topPanel.loadFromFile("data/images/topBar.png");
	topPanelSprite.setTexture(topPanel);
	topPanelSprite.setPosition(0,0);

	initText();		// initialize money and life text
	initButtons();	// initialize towerButtons, creepButtons, exitButton	

	music.openFromFile("data/sounds/bgm.ogg");
	music.setVolume(50);         // reduce the volume
	music.setLoop(true);         // make it loop
}

MainGameState::~MainGameState() {}

void MainGameState::init() {	
	changeState = false;
	music.play();
	window.initForMainGame();
	window.setPath("path1.txt",1);
	window.setPath("path2.txt",2);

	myTeam.init();
	opponentTeam.init();
}

void MainGameState::Exit() {
	music.stop();
}

void MainGameState::update() {
	if(myTeam.isGameOver()) {
		changeState = true;
	}
	if(changeState){
		stateManager.changeGameState("GameOverState");
		return;
	}
	myTeam.player->move(
		sf::Keyboard::isKeyPressed(sf::Keyboard::W),
		sf::Keyboard::isKeyPressed(sf::Keyboard::S),
		sf::Keyboard::isKeyPressed(sf::Keyboard::A),
		sf::Keyboard::isKeyPressed(sf::Keyboard::D));
	myTeam.update();
	connection.addHeroPosition(myTeam.player->getPosition(),myTeam.player->getRotation());
	connection.send();
	connection.receive();
	auto &inQ = connection.getInQ();
	bool isMyTeam;
	sf::IpAddress ip;
	for(auto IT = inQ.begin() ; IT != inQ.end() ; ++IT) {
		ip = (IT->first);
		std::map< int, sf::Packet > &subInQ = (IT)->second;
		isMyTeam = myTeam.isFound(ip);
		for(auto it = subInQ.begin() ; it != subInQ.end() ; ++it) {
			int msg;
			sf::Packet packet = it->second;
			packet>>msg;
			#ifdef PRINT
				std::cout<<"Message received "<<msg<<std::endl;
			#endif
			switch(msg){
				case 1003 :{	//tower added
					float posX,posY;
					int tTyp;
					packet>>posX>>posY>>tTyp;
					TowerType tType = (TowerType)tTyp;
					if(isMyTeam){
						if(myTeam.addTower(window.getMiddlePosition(posX,posY),tType)){
							window.setBlockCode(sf::Vector2f(posX,posY),TOWER);
						}
					} else {
						if(opponentTeam.addTower(window.getMiddlePosition(posX,posY),tType)) {
							window.setBlockCode(sf::Vector2f(posX,posY),TOWER);
						}
					}
					break;
				}
				case 2005 :{	// hero position
					float posX,posY,angle;
					packet>>posX>>posY>>angle;
					if (isMyTeam){
						myTeam.setPlayerPosition(ip, sf::Vector2f(posX,posY));
						myTeam.setPlayerRotation(ip, angle);
					} else {
						opponentTeam.setPlayerPosition(ip, sf::Vector2f(posX,posY));
						opponentTeam.setPlayerRotation(ip, angle);
					}
					break;
				}
				case 507 :{		// fire bullet message
					if (isMyTeam){
						myTeam.fireBullet(ip);
					} else {
						opponentTeam.fireBullet(ip);
					}
					bulletSound.play();
					break;
				}
				case 911 :{		// send next creep
					int cTyp;
					packet>>cTyp;
					CreepType cType = (CreepType)cTyp;
					if (isMyTeam) {
						if(myTeam.startNextWave(cType)){}
					} else{
						if(opponentTeam.startNextWave(cType)){}
					}
					break;
				}
				case 1311 :{	// sell tower at specified position
					float posX,posY;
					packet>>posX>>posY;
					if(isMyTeam) {
						myTeam.sellTowerAtPosition(sf::Vector2f(posX,posY));
					}else {
						opponentTeam.sellTowerAtPosition(sf::Vector2f(posX,posY));
					}
				}
				case 1517 :{	// upgrade tower at specified position
					float posX,posY;
					packet>>posX>>posY;
					if(isMyTeam) {
						myTeam.upgradeTowerAtPosition(sf::Vector2f(posX,posY));
					}else {
						opponentTeam.upgradeTowerAtPosition(sf::Vector2f(posX,posY));
					}
				}
				default:
					break;
			}
		}
		subInQ.clear();
	}
	opponentTeam.update();

	auto& dis = connection.getDeadConnection();
	while(!dis.empty()){
		ip = dis.front();dis.pop();
		if(myTeam.isFound(ip)){
			myTeam.removePlayer(ip);
		}else{
			opponentTeam.removePlayer(ip);
		}
	}

	moneyText.setString("Money : " + std::to_string(myTeam.getMoney()));
	lifeText.setString("Life : " + std::to_string(myTeam.getTeamLife()));
}

void MainGameState::draw() {
	renderWindow.draw(backgroundSprite);
	renderWindow.draw(topBar);
	renderWindow.draw(menuBar);
	opponentTeam.draw();
	myTeam.draw();
}

void MainGameState::handleEvent(const sf::Event& event) {
	if(event.type == sf::Event::MouseButtonPressed){
	    if(event.mouseButton.button == sf::Mouse::Left){
	    	sf::Vector2i mousePosition = sf::Mouse::getPosition(renderWindow); 
	        int i = mousePosition.x;
	        int j = mousePosition.y;
	        if(window.isInsideWindow(i,j)){
	        	sf::Vector2f position = window.getMiddlePosition(i,j);
	        	Code code = window.getBlockCode(i,j);
	        	#ifdef PRINT
	        		std::cout<<"code = "<<code<<"\n";
	            #endif
	            switch(code) {
	            	case MENU:
						{
							if(exitButton->isHover(mousePosition)){
								music.stop();
								myTeam.towerManager->selectNoTower();
								dontDisplayTowerDetails();
								renderWindow.close();
							}
							break;
						}
					case TOWER:
						{
							myTeam.towerManager->selectTowerAtPosition(position);
							Tower *selectedTower = myTeam.towerManager->getSelectedTower();
							if(selectedTower != NULL) {
								displayTowerDetails(selectedTower);
							}
							break;
						}
					case TOOL :
					{
						CreepType cType = getCreepType(mousePosition);
						if(cType != NOCREEP) {
							if(myTeam.startNextWave(cType)) {
								connection.addNextWaveMessage(cType);
							}
						}

						TowerType tType = getTowerType(mousePosition);
						if(tType != NOTOWER) {
							sf::Vector2f position = myTeam.player->getPosition();
							Code code = window.getBlockCode(position);
							if(code == HERO){
								position = window.getMiddlePosition(position.x,position.y);
								if(myTeam.addTower(position,tType)) {
									window.setBlockCode(position,TOWER);
									connection.addTower(position,tType);
								}
							}
						}

						if(sellTowerButton->isHover(mousePosition)) {
							Tower *selectedTower = myTeam.towerManager->getSelectedTower();
							sf::Vector2f pos = selectedTower->getPosition();
							pos = window.getMiddlePosition(pos.x,pos.y);
							myTeam.sellSelectedTower();
							connection.addSelectTowerAtPosition(pos);
							dontDisplayTowerDetails();
						}else if(upgradeTowerButton->isHover(mousePosition)) {
							if(myTeam.upgradeSelectedTower()) {
								Tower *selectedTower = myTeam.towerManager->getSelectedTower();
								sf::Vector2f pos = selectedTower->getPosition();
								pos = window.getMiddlePosition(pos.x,pos.y);
								connection.addUpgradeTowerAtPosition(pos);
								displayTowerDetails(myTeam.towerManager->getSelectedTower());
							}
						}

						break;
					}
					default:
						myTeam.towerManager->selectNoTower();
						dontDisplayTowerDetails();
	            }
	        }
	    }
	}else if(event.type == sf::Event::KeyPressed) {
		switch(event.key.code) {
			case sf::Keyboard::Space:
				if (!spaceKeyHold) {
					if(!(myTeam.player->isHeroDead())) {
						myTeam.player->fireBullet();
						bulletSound.play();
						connection.addHeroFireMessage();
					}
				}
				spaceKeyHold = true;
				break;
			default:
				break;
		}
	} else if (event.type == sf::Event::KeyReleased){
		if (event.key.code == sf::Keyboard::Space) spaceKeyHold = false;
	}
}

void MainGameState::initText() {
	moneyText.setString("Money : " + std::to_string(myTeam.getMoney()));
	moneyText.setFont(font);
    moneyText.setCharacterSize(30);
    moneyText.setColor(sf::Color::White);
    moneyText.setPosition(100.0,0.0);

    lifeText.setString("Life : " + std::to_string(myTeam.getTeamLife()));
	lifeText.setFont(font);
    lifeText.setCharacterSize(30);
    lifeText.setColor(sf::Color::White);
    lifeText.setPosition(300.0,0.0);

	towerTypeText.setFont(font);
    towerTypeText.setCharacterSize(25);
    towerTypeText.setColor(sf::Color::Black);
    towerTypeText.setPosition(850.0,650.0);    

	towerSpeedText.setFont(font);
    towerSpeedText.setCharacterSize(25);
    towerSpeedText.setColor(sf::Color::Black);
    towerSpeedText.setPosition(850.0,675.0);

    towerDamageText.setFont(font);
    towerDamageText.setCharacterSize(25);
    towerDamageText.setColor(sf::Color::Black);
    towerDamageText.setPosition(850.0,700.0);

	towerPriceText.setFont(font);
    towerPriceText.setCharacterSize(25);
    towerPriceText.setColor(sf::Color::Black);
    towerPriceText.setPosition(850.0,725.0);

    topBar.addDrawable(&topPanelSprite);
    topBar.addDrawable(&moneyText);
	topBar.addDrawable(&lifeText);

	menuBar.addDrawable(&panel);

	menuBar.addDrawable(&towerTypeText);
	menuBar.addDrawable(&towerSpeedText);
	menuBar.addDrawable(&towerDamageText);
	menuBar.addDrawable(&towerPriceText);
}

void MainGameState::initButtons() {
	exitButton = new Button(sf::Vector2f(0,0),40,80,"data/images/button.png","Exit",&topBar);
	topBar.addDrawable(exitButton);

	towerButtons[0] = new Button(sf::Vector2f(0,650),50,120,"data/images/button.png","Normal",&menuBar);
	towerButtons[1] = new Button(sf::Vector2f(120,650),50,120,"data/images/button.png","Poison",&menuBar);
	towerButtons[2] = new Button(sf::Vector2f(240,650),50,120,"data/images/button.png","Slow",&menuBar);
	towerButtons[3] = new Button(sf::Vector2f(0,700),50,120,"data/images/button.png","Decay",&menuBar);
	towerButtons[4] = new Button(sf::Vector2f(120,700),50,120,"data/images/button.png","Peircing",&menuBar);
	towerButtons[5] = new Button(sf::Vector2f(240,700),50,120,"data/images/button.png","Diminish",&menuBar);

	creepButtons[0] = new Button(sf::Vector2f(400,650),50,120,"data/images/button.png","Simple",&menuBar);
	creepButtons[1] = new Button(sf::Vector2f(520,650),50,120,"data/images/button.png","Swarm",&menuBar);
	creepButtons[2] = new Button(sf::Vector2f(640,650),50,120,"data/images/button.png","Giant",&menuBar);
	creepButtons[3] = new Button(sf::Vector2f(400,700),50,120,"data/images/button.png","Armor",&menuBar);
	creepButtons[4] = new Button(sf::Vector2f(520,700),50,120,"data/images/button.png","Regen",&menuBar);
	creepButtons[5] = new Button(sf::Vector2f(640,700),50,120,"data/images/button.png","Super",&menuBar);

	sellTowerButton = new Button(sf::Vector2f(1100,650),50,120,"data/images/button.png","Sell",&menuBar);
	upgradeTowerButton = new Button(sf::Vector2f(1100,700),50,120,"data/images/button.png","Upgrade",&menuBar);

	sellTowerButton->setVisible(false);
	upgradeTowerButton->setVisible(false);
	sellTowerButton->setTextColor(sf::Color::Black);
	upgradeTowerButton->setTextColor(sf::Color::Black);
	
	for(int i=0; i<6; i++){
		towerButtons[i]->setTextColor(sf::Color::Black);
		creepButtons[i]->setTextColor(sf::Color::Black);
		menuBar.addDrawable(towerButtons[i]);
		menuBar.addDrawable(creepButtons[i]);
	}
	menuBar.addDrawable(sellTowerButton);
	menuBar.addDrawable(upgradeTowerButton);
}

CreepType MainGameState::getCreepType(sf::Vector2i mousePosition) {
	int index = 6;
	for(int i=0; i<6; i++) {
		if(creepButtons[i]->isHover(mousePosition)) {
			index = i;
		}
	}
	switch(index) {
		case 0:
			return SIMPLE;
		case 1:
			return SWARM;
		case 2:
			return GIANT;
		case 3:
			return ARMOR;
		case 4:
			return REGEN;
		case 5:
			return SUPER;
		default:
			return NOCREEP;
	}
}

TowerType MainGameState::getTowerType(sf::Vector2i mousePosition) {
	int index = 6;
	for(int i=0; i<6; i++) {
		if(towerButtons[i]->isHover(mousePosition)) {
			index = i;
		}
	}
	switch(index) {
		case 0:
			return NORMAL;
		case 1:
			return POISON;
		case 2:
			return SLOW;
		case 3:
			return DECAY;
		case 4:
			return PEIRCING;
		case 5:
			return DIMINISH;
		default:
			return NOTOWER;
	}	
}

void MainGameState::displayTowerDetails(Tower *selectedTower) {
	TowerType tType = selectedTower->getTowerType();
	switch(tType) {
		case NORMAL : 
			towerTypeText.setString("TowerType : Normal");
			break;
		case PEIRCING : 
			towerTypeText.setString("TowerType : Peircing");
			break;
		case POISON : 
			towerTypeText.setString("TowerType : Poison");
			break;
		case DIMINISH : 
			towerTypeText.setString("TowerType : Diminish");
			break;
		case SLOW : 
			towerTypeText.setString("TowerType : Slow");
			break;
		case DECAY : 
			towerTypeText.setString("TowerType : Decay");
			break;
		default : 
			towerTypeText.setString("TowerType : Default");
	}

	towerSpeedText.setString("Attack Time : " + std::to_string(selectedTower->getAttack_speed()));
	towerDamageText.setString("Damage : " + std::to_string(selectedTower->getDamage()));
	towerPriceText.setString("Upgrade Cost : " + std::to_string(selectedTower->getUpgradeCost()));

	sellTowerButton->setVisible(true);
	upgradeTowerButton->setVisible(true);	
}

void MainGameState::dontDisplayTowerDetails() {
	towerTypeText.setString("");
	towerSpeedText.setString("");
	towerDamageText.setString("");
	towerPriceText.setString("");

	sellTowerButton->setVisible(false);
	upgradeTowerButton->setVisible(false);
}