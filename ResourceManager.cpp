#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager() {
    loadAssets();
}

void ResourceManager::loadAssets() {
    if (!hiddenTexture.loadFromFile("images/tile_hidden.png")) {
        std::cerr << "Failed to load tile_hidden.png" << std::endl;
    }
    if (!revealedTexture.loadFromFile("images/tile_revealed.png")) {
        std::cerr << "Failed to load tile_revealed.png" << std::endl;
    }
    if (!mineTexture.loadFromFile("images/mine.png")) {
        std::cerr << "Failed to load mine.png" << std::endl;
    }
    if (!flagTexture.loadFromFile("images/flag.png")) {
        std::cerr << "Failed to load flag.png" << std::endl;
    }
    if (!restartTexture.loadFromFile("images/face_happy.png")) {
        std::cerr << "Failed to load face_happy.png" << std::endl;
    }
    if (!debugTexture.loadFromFile("images/debug.png")) {
        std::cerr << "Failed to load debug.png" << std::endl;
    }
    if (!test1Texture.loadFromFile("images/test_1.png")) {
        std::cerr << "Failed to load test_1.png" << std::endl;
    }
    if (!test2Texture.loadFromFile("images/test_2.png")) {
        std::cerr << "Failed to load test_2.png" << std::endl;
    }
    if (!test3Texture.loadFromFile("images/test_3.png")) {
        std::cerr << "Failed to load test_3.png" << std::endl;
    }
    if (!winFaceTexture.loadFromFile("images/face_win.png")) {
        std::cerr << "Failed to load face_win.png" << std::endl;
    }
    if (!loseFaceTexture.loadFromFile("images/face_lose.png")) {
        std::cerr << "Failed to load face_lose.png" << std::endl;
    }
    if (!happyFaceTexture.loadFromFile("images/face_happy.png")) {
        std::cerr << "Failed to load face_happy.png" << std::endl;
    }
    if (!digitsTexture.loadFromFile("images/digits.png")) {
        std::cerr << "Failed to load digits.png" << std::endl;
    }

    for (int i = 1; i <= 8; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("images/number_" + std::to_string(i) + ".png")) {
            std::cerr << "Failed to load number_" + std::to_string(i) + ".png" << std::endl;
        }
        numberTextures.push_back(texture);
    }

    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font \"fonts/arial.ttf\"" << std::endl;
    }
}

const sf::Texture& ResourceManager::getHiddenTexture() const { return hiddenTexture; }
const sf::Texture& ResourceManager::getRevealedTexture() const { return revealedTexture; }
const sf::Texture& ResourceManager::getMineTexture() const { return mineTexture; }
const sf::Texture& ResourceManager::getFlagTexture() const { return flagTexture; }
const sf::Texture& ResourceManager::getRestartTexture() const { return restartTexture; }
const sf::Texture& ResourceManager::getDebugTexture() const { return debugTexture; }
const sf::Texture& ResourceManager::getTest1Texture() const { return test1Texture; }
const sf::Texture& ResourceManager::getTest2Texture() const { return test2Texture; }
const sf::Texture& ResourceManager::getTest3Texture() const { return test3Texture; }
const sf::Texture& ResourceManager::getWinFaceTexture() const { return winFaceTexture; }
const sf::Texture& ResourceManager::getLoseFaceTexture() const { return loseFaceTexture; }
const sf::Texture& ResourceManager::getHappyFaceTexture() const { return happyFaceTexture; }
const sf::Texture& ResourceManager::getDigitsTexture() const { return digitsTexture; }
const sf::Texture& ResourceManager::getNumberTexture(int index) const { return numberTextures.at(index); }
const sf::Font& ResourceManager::getFont() const { return font; }
