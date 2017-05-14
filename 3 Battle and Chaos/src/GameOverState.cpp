#include "GameOverState.hpp"

GameOverState::GameOverState(sf::RenderWindow& rw, StateManager& sm, Window& w, Team& mt,Team& ot,MyConnection& c):
	GameState(rw,sm,w,mt,ot,c),
	victorySound(*SoundManager::getInstance().getResource("victory.wav")),
	defeatSound(*SoundManager::getInstance().getResource("defeat.wav"))
{
	backgroundTexture.loadFromFile("data/images/bg.jpg");
	backgroundTexture.setSmooth(true);
	backgroundSprite.setTexture(backgroundTexture);

	resultText.setFont(font);
    resultText.setCharacterSize(200);
    resultText.setColor(sf::Color::Green);
    resultText.setPosition(0.0,220.0);

	exitButton = new Button(sf::Vector2f(1000,340),75,246,"data/images/button.png","Quit",&container);
	
	container.addDrawable(exitButton);
	mouseHold = false;
	changeState = false;
}

GameOverState::~GameOverState() {}

void GameOverState::init() {
	if(myTeam.getWinningStatus()){
		resultText.setString("Victory !");
		victorySound.play();
	}else{
		resultText.setPosition(683.0,400.0);
		resultText.setColor(sf::Color::Blue);
		resultText.setString("Defeat !");
		defeatSound.play();
	}
}

void GameOverState::Exit() {}

void GameOverState::update() {
}

void GameOverState::draw() {
	renderWindow.draw(backgroundSprite);
	renderWindow.draw(resultText);
	renderWindow.draw(container);
}

void GameOverState::handleEvent(const sf::Event& event) {
	if(event.type == sf::Event::MouseButtonPressed){
		sf::Vector2i mousePosition = sf::Mouse::getPosition(renderWindow);
		if(mouseHold)
			return;
		mouseHold = true;
		if(exitButton->isHover(mousePosition)){
			renderWindow.close();
		}
	} else if (event.type == sf::Event::MouseButtonReleased) {
		mouseHold = false;
	}
}