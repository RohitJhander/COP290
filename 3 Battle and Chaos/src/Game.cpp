#include "Game.hpp"
#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include "GameOverState.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() : renderWindow(sf::VideoMode(1366,768), "Battle and Chaos", sf::Style::Fullscreen), 
                window(renderWindow), myTeam(renderWindow,window,&opponentTeam,true), 
                opponentTeam(renderWindow,window,&myTeam,false)
{
	isExit = false;

    stateManager.addGameState("MainMenuState" , new MainMenuState(renderWindow,stateManager,window,myTeam,opponentTeam,connection));
    stateManager.addGameState("MainGameState" , new MainGameState(renderWindow,stateManager,window,myTeam,opponentTeam,connection));
    stateManager.addGameState("GameOverState" , new GameOverState(renderWindow,stateManager,window,myTeam,opponentTeam,connection));

    stateManager.changeGameState("MainMenuState");
}

Game::~Game() {}

void Game::run() {
	renderWindow.setFramerateLimit(60);
    window.initGrid();
    while(renderWindow.isOpen() && !isExit){
        sf::Event event;
        while(renderWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                renderWindow.close();
                Exit();
                exit(0);    // exit otherwise stack smashing attack
            }
            stateManager.handleEvent(event);
        }
        stateManager.update();
        renderWindow.clear();
        stateManager.draw();
        renderWindow.display();
    }
}

void Game::Exit() {
	isExit = true;
}