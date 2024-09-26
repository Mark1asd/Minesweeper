#include "GameBoard.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

GameBoard::GameBoard(int width, int height, int mineCount, ResourceManager& resources)
    : boardWidth(width), boardHeight(height), mines(mineCount), remainingMines(mineCount), debugMode(false), gameEnded(false), resources(resources) {
    reset();

    // Initialize mine counter digit sprites
    for (int i = 0; i < 3; ++i) {
        digitSprites[i].setTexture(resources.getDigitsTexture());
        digitSprites[i].setPosition(20.f + i * 21.f, static_cast<float>(boardHeight * 32 + 20));
    }
    updateMineCounter(0); // Initialize the counter with the current number of mines
}

void GameBoard::reset() {
    cells.clear();
    cells.resize(boardWidth * boardHeight);

    for (int y = 0; y < boardHeight; ++y) {
        for (int x = 0; x < boardWidth; ++x) {
            int index = y * boardWidth + x;
            cells[index].setCoordinates(x * 32, y * 32);
            cells[index].setTextures(resources);
            cells[index].placeMine(false);
            cells[index].setSurroundingMines(0);
        }
    }

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < mines; ++i) {
        int index;
        do {
            index = rand() % (boardWidth * boardHeight);
        } while (cells[index].isMine());
        cells[index].placeMine(true);
    }

    for (int y = 0; y < boardHeight; ++y) {
        for (int x = 0; x < boardWidth; ++x) {
            int index = y * boardWidth + x;
            if (!cells[index].isMine()) {
                int adjacentMines = 0;
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < boardWidth && ny >= 0 && ny < boardHeight) {
                            int neighborIndex = ny * boardWidth + nx;
                            if (cells[neighborIndex].isMine()) {
                                ++adjacentMines;
                            }
                        }
                    }
                }
                cells[index].setSurroundingMines(adjacentMines);
                cells[index].setTextures(resources);
            }
        }
    }

    remainingMines = mines;
    updateMineCounter(0);
    debugMode = false;
    gameEnded = false;

    debugButton.setTexture(resources.getDebugTexture());
    testButton1.setTexture(resources.getTest1Texture());
    testButton2.setTexture(resources.getTest2Texture());
    testButton3.setTexture(resources.getTest3Texture());

    debugButton.setPosition(static_cast<float>((boardWidth * 32) / 2 + 95), static_cast<float>(boardHeight * 32));
    testButton1.setPosition(static_cast<float>((boardWidth * 32) / 2 + 159), static_cast<float>(boardHeight * 32));
    testButton2.setPosition(static_cast<float>((boardWidth * 32) / 2 + 224), static_cast<float>(boardHeight * 32));
    testButton3.setPosition(static_cast<float>((boardWidth * 32) / 2 + 288), static_cast<float>(boardHeight * 32));

    faceButton.setTexture(resources.getHappyFaceTexture());
    faceButton.setPosition(static_cast<float>((boardWidth * 32) / 2 - 32), static_cast<float>(boardHeight * 32));
}

void GameBoard::loadBoardFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open board file: " << filename << std::endl;
        return;
    }

    reset(); // Ensure the board is reset

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    if (lines.size() != boardHeight) {
        std::cerr << "Board file has incorrect number of rows." << std::endl;
        return;
    }

    int mineCount = 0;
    for (int row = 0; row < boardHeight; ++row) {
        if (lines[row].length() != static_cast<size_t>(boardWidth)) {
            std::cerr << "Board file has incorrect number of columns." << std::endl;
            return;
        }

        for (int col = 0; col < boardWidth; ++col) {
            char tileData = lines[row][col];
            int index = row * boardWidth + col;
            if (index >= cells.size()) {
                std::cerr << "Index out of bounds: " << index << std::endl;
                continue;
            }

            if (tileData == '1') {
                cells[index].placeMine(true);
                mineCount++;
            }
            else if (tileData == '0') {
                cells[index].placeMine(false);
            }
        }
    }

    // Recalculate surrounding mines after placing all mines
    for (int y = 0; y < boardHeight; ++y) {
        for (int x = 0; x < boardWidth; ++x) {
            int index = y * boardWidth + x;
            if (!cells[index].isMine()) {
                int adjacentMines = 0;
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < boardWidth && ny >= 0 && ny < boardHeight) {
                            int neighborIndex = ny * boardWidth + nx;
                            if (cells[neighborIndex].isMine()) {
                                ++adjacentMines;
                            }
                        }
                    }
                }
                cells[index].setSurroundingMines(adjacentMines);
            }
            // Update textures for all cells after recalculating
            cells[index].setTextures(resources);
        }
    }

    // Update the mine counter with the number of mines in the file
    remainingMines = mineCount;
    updateMineCounter(0);
}

void GameBoard::render(sf::RenderWindow& window) {
    // Draw the game board tiles
    for (int i = 0; i < cells.size(); ++i) {
        cells[i].render(window);
    }

    // Create a white rectangle for the bottom area
    sf::RectangleShape bottomArea(sf::Vector2f(static_cast<float>(window.getSize().x), 100.f));
    bottomArea.setFillColor(sf::Color::White);
    bottomArea.setPosition(0, static_cast<float>(boardHeight * 32));

    // Draw the white rectangle
    window.draw(bottomArea);

    // Draw the mine counter digits
    for (int i = 0; i < 3; ++i) {
        window.draw(digitSprites[i]);
    }

    // Draw the buttons
    window.draw(debugButton);
    window.draw(testButton1);
    window.draw(testButton2);
    window.draw(testButton3);
    window.draw(faceButton);
}


void GameBoard::handleLeftClick(int x, int y) {
    int tileX = x / 32;
    int tileY = y / 32;

    if (faceButton.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
        reset();
    }
    else if (!gameEnded && debugButton.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
        toggleMineVisibility();
    }
    else if (testButton1.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
        loadBoardFromFile("boards/testboard1.brd");
    }
    else if (testButton2.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
        loadBoardFromFile("boards/testboard2.brd");
    }
    else if (testButton3.getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
        loadBoardFromFile("boards/testboard3.brd");
    }
    else if (!gameEnded && tileX >= 0 && tileX < boardWidth && tileY >= 0 && tileY < boardHeight) {
        int index = tileY * boardWidth + tileX;
        revealTile(index);
    }
}

void GameBoard::handleRightClick(int x, int y) {
    if (gameEnded) return; // Prevent interaction if the game has ended

    int tileX = x / 32;
    int tileY = y / 32;
    int index = tileY * boardWidth + tileX;

    if (index >= 0 && index < cells.size() && !cells[index].isUncovered()) {
        cells[index].switchFlag();
        updateMineCounter(cells[index].isFlagged() ? -1 : 1);
    }
}

void GameBoard::toggleMineVisibility() {
    if (gameEnded) return; // Prevent toggling if the game has ended

    debugMode = !debugMode;
    for (auto& cell : cells) {
        if (cell.isMine()) {
            if (debugMode) {
                cell.setRevealedSprite();
            }
            else {
                cell.setHiddenSprite();
            }
        }
    }
}

void GameBoard::updateMineCounter(int change) {
    remainingMines += change;

    // Handle negative numbers
    bool isNegative = (remainingMines < 0);
    int mines = std::abs(remainingMines);

    // Create a string with the number, ensuring it is 3 characters long
    std::string minesStr = std::to_string(mines);
    while (minesStr.length() < 3) {
        minesStr = "0" + minesStr;
    }
    if (isNegative) {
        minesStr = "-" + minesStr;
    }

    // Set the texture rectangles for the sprites
    for (int i = 0; i < 3; ++i) {
        int digitIndex;
        if (isNegative && i == 0) {
            digitIndex = 10; // Assuming the '-' sign is the 11th character in the digits.png (index 10)
        }
        else {
            digitIndex = minesStr[i + (isNegative ? 1 : 0)] - '0';
        }
        digitSprites[i].setTextureRect(sf::IntRect(digitIndex * 21, 0, 21, 32));
    }
}

void GameBoard::revealTile(int index) {
    if (gameEnded) return;

    if (!cells[index].isUncovered() && !cells[index].isFlagged()) {
        cells[index].uncover();

        if (cells[index].isMine()) {
            gameEnded = true;
            std::cout << "Game Over! You clicked on a mine." << std::endl;

            for (auto& cell : cells) {
                if (cell.isMine()) {
                    cell.uncover();
                }
            }

            faceButton.setTexture(resources.getLoseFaceTexture());
        }
        else {
            if (cells[index].getSurroundingMines() == 0) {
                revealSurroundingTiles(index);
            }
            if (checkWinCondition()) {
                gameEnded = true;
                faceButton.setTexture(resources.getWinFaceTexture());
            }
        }
    }
}

void GameBoard::revealSurroundingTiles(int index) {
    int x = index % boardWidth;
    int y = index / boardWidth;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < boardWidth && ny >= 0 && ny < boardHeight) {
                int neighborIndex = ny * boardWidth + nx;
                if (!cells[neighborIndex].isUncovered() && !cells[neighborIndex].isFlagged()) {
                    revealTile(neighborIndex);
                }
            }
        }
    }
}

bool GameBoard::checkWinCondition() {
    for (const auto& cell : cells) {
        if (!cell.isMine() && !cell.isUncovered()) {
            return false;
        }
    }

    // Flag all mines and update the counter
    for (auto& cell : cells) {
        if (cell.isMine() && !cell.isFlagged()) {
            cell.switchFlag();
        }
    }
    remainingMines = 0; // Set remaining mines to 0 for the counter
    updateMineCounter(0);

    return true;
}

void GameBoard::updateFaceButton() {
    if (gameEnded) {
        if (checkWinCondition()) {
            faceButton.setTexture(resources.getWinFaceTexture());
        }
        else {
            faceButton.setTexture(resources.getLoseFaceTexture());
        }
    }
    else {
        faceButton.setTexture(resources.getHappyFaceTexture());
    }
}