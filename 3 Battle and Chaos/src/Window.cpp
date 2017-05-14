#include "Window.hpp"

Window::Window(sf::RenderWindow &rWindow) : renderWindow(rWindow) {
	windowY = 768;     //(int)rWindow.getSize().y;
	windowX = 1366;    //(int)rWindow.getSize().x;
    gridSize = 40;
	gridY = windowY/gridSize;
	gridX = windowX/gridSize;
	menuY = 5;
	grid = new Block*[gridX];
	for(int i=0 ; i < gridX ; i++){
		grid[i] = new Block[gridY];
	}
}

Window::~Window() {}

int Window::getWindowX() {
	return windowX;
}

int Window::getWindowY() {
	return windowY;
}

int Window::getGridSize() {
    return gridSize;
}

void Window::initGrid() {
	for(int i=0;i<gridX;i++){
        for(int j=0;j<gridY;j++){
            grid[i][j].setPosition(sf::Vector2f(gridSize*i,gridSize*j));
            grid[i][j].setSize(sf::Vector2f(gridSize,gridSize));
            grid[i][j].setCode(NONE);
        }
        grid[i][0].setCode(MENU);
        grid[i][0].setFillColor(sf::Color::Yellow);
    }
}

void Window::drawGrid() {
    for(int i=0;i<gridX;i++){
        for(int j=0;j<gridY;j++){
            renderWindow.draw(grid[i][j].drawing);
        }
    }
}

void Window::setBlockColor(int i, int j, sf::Color color) {
	grid[i/gridSize][j/gridSize].setFillColor(color);
}

void Window::setBlockCode(int i, int j, Code code) {
    grid[i/gridSize][j/gridSize].setCode(code);
}

Code Window::getBlockCode(int i,int j) {
    return grid[i/gridSize][j/gridSize].getCode();
}

void Window::setBlockCode(sf::Vector2f pos, Code code) {
    int i = (int)pos.x;
    int j = (int)pos.y;
    if(isInsideWindow(i,j))
        setBlockCode(i,j,code);
}

Code Window::getBlockCode(sf::Vector2f pos) {
    int i = (int)pos.x;
    int j = (int)pos.y;
    if(isInsideWindow(i,j))
        return getBlockCode(i,j);
    return NONE;
}

bool Window::isInsideWindow(int i, int j) {
    return (i>=0 && j>=0 && i<windowX-gridSize/2 && j<windowY-gridSize/2);
}

bool Window::isInsideWindow(sf::Vector2f pos) {
    int i = (int)pos.x;
    int j = (int)pos.y;
    return isInsideWindow(i,j);
}

sf::Vector2f Window::getMiddlePosition(int i,int j) {
    int a = (i/gridSize)*gridSize + gridSize/2;
    int b = (j/gridSize)*gridSize + gridSize/2;
    return sf::Vector2f((float)a,(float)b);
}

sf::Vector2f Window::getBlockMiddlePosition(int row,int column) {
    int a = row * gridSize + gridSize/2;
    int b = column * gridSize + gridSize/2;
    return sf::Vector2f((float)a,(float)b);
}

void Window::setPath(std::string pathFileName, int n) {
    std::vector<sf::Vector2i> points;
    if (n == 1) {
        myPath.loadPath(pathFileName);
        points = myPath.getPoints();
    } else if (n == 2) {
        opponentPath.loadPath(pathFileName);
        points = opponentPath.getPoints();
    }

    int i,j,x,y,dx,dy;
    for (i=1;i<points.size();++i){
        x = points[i-1].x;
        y = points[i-1].y;
        dx = points[i].x - x;
        dy = points[i].y - y;
        if (dx == 0) {
            if (dy > 0) {
                for(j=0;j<dy;j++) {
                    grid[x][j+y].setFillColor(sf::Color::Blue);
                    grid[x][j+y].setCode(PATH);
                }
            } else {
                for(j=0;j>dy;j--) {
                    grid[x][j+y].setFillColor(sf::Color::Blue);
                    grid[x][j+y].setCode(PATH);
                }
            }
        } else if (dy == 0) {
            if (dx > 0) {
                for(j=0;j<dx;j++) {
                    grid[j+x][y].setFillColor(sf::Color::Blue);
                    grid[j+x][y].setCode(PATH);
                }
            } else {
                for(j=0;j>dx;j--) {
                    grid[j+x][y].setFillColor(sf::Color::Blue);
                    grid[j+x][y].setCode(PATH);
                }
            }
        }
    }

    x = points[i-1].x;
    y = points[i-1].y;
    grid[x][y].setFillColor(sf::Color::Blue);
    grid[x][y].setCode(PATH);
}

std::vector<sf::Vector2i>& Window::getPathPoints(int n) {
    if (n == 1) return myPath.getPoints();
    else if (n == 2) return opponentPath.getPoints();
}

void Window::initForMainGame() {
    for (int i=0;i<gridX;i++){
        grid[i][gridY-1].setCode(TOOL);
        grid[i][gridY-2].setCode(TOOL);
        grid[i][gridY-3].setCode(TOOL);

        grid[i][gridY-1].setFillColor(sf::Color::Black);
        grid[i][gridY-2].setFillColor(sf::Color::Black);
        grid[i][gridY-3].setFillColor(sf::Color::Black);
    }
}