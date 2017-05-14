#include "MainMenuState.hpp"

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

MainMenuState::MainMenuState(sf::RenderWindow& rw, StateManager& sm, Window& w, Team& mt,Team& ot,MyConnection& c):
	GameState(rw,sm,w,mt,ot,c)
{
	changeState = false;	
	backgroundTexture.loadFromFile("data/images/bg.jpg");
	backgroundTexture.setSmooth(true);
	backgroundSprite.setTexture(backgroundTexture);

	EnterText.setString("Enter team/ Number of Players : ");
    EnterText.setFont(font);
    EnterText.setCharacterSize(50);
    EnterText.setColor(sf::Color::Yellow);
    EnterText.setPosition(100.0,600.0);

    inputText.setFont(font);
    inputText.setCharacterSize(50);
    inputText.setColor(sf::Color::Yellow);
    inputText.setPosition(100.0,670.0);

    mouseHold = false;
    currentSubstate = START;

    hostButton = new Button(sf::Vector2f(938,300),100,228,"data/images/button.png","Host",&container);
    joinButton = new Button(sf::Vector2f(938,420),100,228,"data/images/button.png","Join",&container);
    exitButton = new Button(sf::Vector2f(938,540),100,228,"data/images/button.png","Exit",&container);
    backButton = new Button(sf::Vector2f(938,660),100,228,"data/images/button.png","Back",&container);
    backButton->setVisible(false);

    container.addDrawable(hostButton);
	container.addDrawable(joinButton);
	container.addDrawable(exitButton);
	container.addDrawable(backButton);
}

MainMenuState::~MainMenuState() {}

void MainMenuState::init() {
	
}

void MainMenuState::Exit() {
	
}

void MainMenuState::update() {
	if(changeState){
		changeState = false;
		stateManager.changeGameState("MainGameState"); 
	}
	sf::Vector2i position = sf::Mouse::getPosition();
	if(hostButton->isHover(position))
		hostButton->hover();
	else
		hostButton->normal();

	if(exitButton->isHover(position))
		exitButton->hover();
	else
		exitButton->normal();
	
	if(joinButton->isHover(position))
		joinButton->hover();
	else
		joinButton->normal();
	
	if(backButton->isHover(position))
		backButton->hover();
	else
		backButton->normal();
}

void MainMenuState::forceUpdate(){
	renderWindow.clear();
	draw();
	renderWindow.display();
}

void MainMenuState::draw(){
	renderWindow.draw(backgroundSprite);
	renderWindow.draw(EnterText);
	renderWindow.draw(inputText);
	renderWindow.draw(container);
}

void MainMenuState::acceptNewPlayer(int i){
	int joinerTeam;
	sf::IpAddress joinerIp;

	connection.accept(joinerTeam, joinerIp);
	if (joinerTeam == teamNumber) {
		myTeam.addPlayer(joinerIp);
	} else {
		opponentTeam.addPlayer(joinerIp);
	}

	EnterText.setString(std::to_string(i) + string(" Player(s) joined"));
}

void MainMenuState::addPlayersToTeam(std::map< sf::IpAddress, int >& teamMap) {
	int myTeamNumber = myTeam.getTeamNumber();
	for(auto it = teamMap.begin(); it != teamMap.end(); ++it){
		if(it->second == myTeamNumber) {
			myTeam.addPlayer(it->first);
		} else {
			opponentTeam.addPlayer(it->first);
		}
	}
}

void MainMenuState::changeSubstate(Substate s){
	switch(s) {
		case HOST:{
			currentSubstate = HOST;
			connection.changeMode(Host);

			teamNumber = 1;
			myTeam.setTeamNumber(teamNumber);
			opponentTeam.setTeamNumber(3-teamNumber);
			
			string s = inputText.getString();
			int numberOfPlayer = std::stoi(s);
			inputText.setString("");
			EnterText.setString(std::to_string(numberOfPlayer-1) + string(" Player(s) joining"));
			joinButton->setVisible(false);
			backButton->setVisible(true);
			hostButton->setText("Start");

			for(int i=1; i<numberOfPlayer; ++i){
				forceUpdate();
				acceptNewPlayer(i);
			}
			break;
		}
		case JOIN:{
			currentSubstate = JOIN;
			string s = inputText.getString();
			teamNumber = std::stoi(s);
			myTeam.setTeamNumber(teamNumber);
			opponentTeam.setTeamNumber(3-teamNumber);

			inputText.setString("");
			EnterText.setString("Enter server IP");
			joinButton->setText("Connect");
			backButton->setVisible(true);
			hostButton->setVisible(false);
			break;
		}
		case GAME:{
			if (currentSubstate == HOST){
				connection.establishP2P();
				#ifdef PRINT
					std::cout<<"p2p established for HOST!"<<std::endl;
				#endif
				connection.sendStartCommand();
				connection.changeMode(Client);
			} else if (currentSubstate == JOIN){
				connection.changeMode(Client);
				string s = inputText.getString();
				int space = s.find_first_of(" ",0);
				string IP = s.substr(0,space);
				unsigned short Port = std::stoi(s.substr(space));
				connection.addPeer(sf::IpAddress(IP),Port,1);
				connection.sendJoinRequest(teamNumber);

				inputText.setString("");
				EnterText.setString("Wait for server to start");

				forceUpdate();
				connection.establishP2P();
				addPlayersToTeam(connection.getTeamMap());
				#ifdef PRINT
					std::cout<<"p2p established!"<<std::endl;
					std::cout<<"waiting to receive start command"<<std::endl;
				#endif
				connection.receiveStartCommand();
				std::cout<<"received start command!"<<std::endl;
			}
			changeState = true;
			break;
		}
		case START:{
			currentSubstate = START;
			inputText.setString("");
			EnterText.setString("Enter team/ Number of Players : ");
			joinButton->setText("Join");
			hostButton->setText("Host");
			backButton->setVisible(false);
			joinButton->setVisible(true);
			hostButton->setVisible(true);
			break;
		}
		default:
			break;
	}
}

void MainMenuState::handleEvent(const sf::Event& event){
	if(event.type == sf::Event::MouseButtonPressed){
		sf::Vector2i mousePosition = sf::Mouse::getPosition(renderWindow);
		mouseHold = true;
		if (exitButton->isHover(mousePosition)){
			renderWindow.close();
		} else if (currentSubstate == START){
			if (hostButton->isHover(mousePosition)){
				changeSubstate(HOST);
			} else if (joinButton->isHover(mousePosition)){
				changeSubstate(JOIN);
			}
		} else if (currentSubstate == HOST){
			if (hostButton->isHover(mousePosition)){
				changeSubstate(GAME);
			} else if (backButton->isHover(mousePosition)){
				changeSubstate(START);
			}
		} else if (currentSubstate == JOIN){
			if (joinButton->isHover(mousePosition)) {
				changeSubstate(GAME);
			} else if (backButton->isHover(mousePosition)) {
				changeSubstate(START);
			}
		}
	} else if (event.type == sf::Event::MouseButtonReleased){
		mouseHold = false;
	} else if (currentSubstate != HOST && event.type == sf::Event::KeyPressed) {

		string s = inputText.getString();
		//Alphabets
		if (event.key.code >= 0 && event.key.code < 26) {
			//capital letters
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				s += (char)(event.key.code+65);
			else
				s += (char)(event.key.code+97);
		} else if (event.key.code >= 26 && event.key.code < 36){
			s += (char) (event.key.code + 22);
		}
		else {
			switch(event.key.code) {
				case 57: s+=" "; break;
				case 59: if (s.length() > 0) s.erase(s.end()-1); break;
				case 50: s += "."; break;
			}
		}
		if (s.length() <= 32) inputText.setString(s);
	}
}
