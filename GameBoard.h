#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Cell.h"
#include "ResourceManager.h"

class GameBoard {
public:
    GameBoard(int width, int height, int mineCount, ResourceManager& resources);
    void reset();
    void handleLeftClick(int x, int y);
    void handleRightClick(int x, int y);
    void render(sf::RenderWindow& window);

private:
    void loadBoardFromFile(const std::string& filename);
    void revealTile(int index);
    void revealSurroundingTiles(int index);
    void toggleMineVisibility();
    void updateMineCounter(int change);
    bool checkWinCondition();
    void updateFaceButton();

    int boardWidth;
    int boardHeight;
    int mines;
    int remainingMines;
    bool debugMode;
    bool gameEnded;

    std::vector<Cell> cells;
    ResourceManager& resources;

    sf::Sprite debugButton;
    sf::Sprite testButton1;
    sf::Sprite testButton2;
    sf::Sprite testButton3;
    sf::Sprite faceButton;

    sf::Sprite digitSprites[3];

    sf::Text mineCounterText;
};
