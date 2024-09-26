#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Cell {
public:
    Cell();
    void render(sf::RenderWindow& window);
    void setCoordinates(int x, int y);
    void setTextures(const ResourceManager& resources);
    void placeMine(bool mine);
    void setSurroundingMines(int count);
    void uncover();
    void cover();
    void setRevealedSprite();
    void setHiddenSprite();
    void switchFlag();
    bool isMine() const;
    bool isUncovered() const;
    bool isFlagged() const;
    int getSurroundingMines() const;

private:
    sf::Sprite hiddenSprite;
    sf::Sprite revealedSprite;
    sf::Sprite numberSprite;
    sf::Sprite flagSprite;
    sf::Sprite mineSprite;
    bool minePresence;
    bool uncovered;
    bool flagged;
    int surroundingMines;
};
