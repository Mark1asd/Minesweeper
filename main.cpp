#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <direct.h>
#include "GameBoard.h"
#include "ResourceManager.h"

int main() {
    char currentDirectory[1024];
    if (_getcwd(currentDirectory, sizeof(currentDirectory)) != NULL) {
        std::cout << "Current working directory: " << currentDirectory << std::endl;
    }
    else {
        perror("_getcwd() error");
        return -1;
    }

    std::ifstream configFile("boards/config.cfg");
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config file." << std::endl;
        return -1;
    }

    int width, height, numberOfMines;
    configFile >> width >> height >> numberOfMines;
    configFile.close();

    if (width <= 0 || height <= 0 || numberOfMines <= 0 || numberOfMines >= width * height) {
        std::cerr << "Invalid board parameters from config file." << std::endl;
        return -1;
    }

    std::cout << "Width: " << width << ", Height: " << height << ", Mines: " << numberOfMines << std::endl;

    int tileSize = 32;
    int windowWidth = width * tileSize;
    int windowHeight = (height * tileSize) + 100;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");

    ResourceManager resources;
    GameBoard gameBoard(width, height, numberOfMines, resources);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    gameBoard.handleLeftClick(event.mouseButton.x, event.mouseButton.y);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    gameBoard.handleRightClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        window.clear();
        gameBoard.render(window);
        window.display();
    }

    return 0;
}
