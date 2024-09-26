#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ResourceManager {
public:
    ResourceManager();
    void loadAssets();

    const sf::Texture& getHiddenTexture() const;
    const sf::Texture& getRevealedTexture() const;
    const sf::Texture& getMineTexture() const;
    const sf::Texture& getFlagTexture() const;
    const sf::Texture& getRestartTexture() const;
    const sf::Texture& getDebugTexture() const;
    const sf::Texture& getTest1Texture() const;
    const sf::Texture& getTest2Texture() const;
    const sf::Texture& getTest3Texture() const;
    const sf::Texture& getWinFaceTexture() const;
    const sf::Texture& getLoseFaceTexture() const;
    const sf::Texture& getHappyFaceTexture() const;
    const sf::Texture& getDigitsTexture() const;
    const sf::Texture& getNumberTexture(int index) const;
    const sf::Font& getFont() const;

private:
    sf::Texture hiddenTexture;
    sf::Texture revealedTexture;
    sf::Texture mineTexture;
    sf::Texture flagTexture;
    sf::Texture restartTexture;
    sf::Texture debugTexture;
    sf::Texture test1Texture;
    sf::Texture test2Texture;
    sf::Texture test3Texture;
    sf::Texture winFaceTexture;
    sf::Texture loseFaceTexture;
    sf::Texture happyFaceTexture;
    sf::Texture digitsTexture;
    std::vector<sf::Texture> numberTextures;
    sf::Font font;
};
