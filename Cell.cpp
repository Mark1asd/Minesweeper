#include "Cell.h"

Cell::Cell()
    : minePresence(false), uncovered(false), flagged(false), surroundingMines(0) {}

void Cell::render(sf::RenderWindow& window) {
    if (uncovered) {
        window.draw(revealedSprite);
        if (minePresence) {
            if (flagged) {
                window.draw(flagSprite);
            }
            window.draw(mineSprite);
        }
        else if (surroundingMines > 0) {
            window.draw(numberSprite);
        }
    }
    else {
        window.draw(hiddenSprite);
        if (flagged) {
            window.draw(flagSprite);
        }
    }
}

void Cell::setCoordinates(int x, int y) {
    hiddenSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    revealedSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    mineSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    numberSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    flagSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
}

void Cell::setTextures(const ResourceManager& resources) {
    hiddenSprite.setTexture(resources.getHiddenTexture());
    revealedSprite.setTexture(resources.getRevealedTexture());
    mineSprite.setTexture(resources.getMineTexture());
    flagSprite.setTexture(resources.getFlagTexture());
    if (surroundingMines > 0) {
        numberSprite.setTexture(resources.getNumberTexture(surroundingMines - 1));
    }
}

void Cell::placeMine(bool mine) {
    minePresence = mine;
}

void Cell::setSurroundingMines(int count) {
    surroundingMines = count;
}

void Cell::uncover() {
    uncovered = true;
}

void Cell::cover() {
    uncovered = false;
}

void Cell::setRevealedSprite() {
    uncovered = true;
}

void Cell::setHiddenSprite() {
    uncovered = false;
}

void Cell::switchFlag() {
    flagged = !flagged;
}

bool Cell::isMine() const {
    return minePresence;
}

bool Cell::isUncovered() const {
    return uncovered;
}

bool Cell::isFlagged() const {
    return flagged;
}

int Cell::getSurroundingMines() const {
    return surroundingMines;
}
