#include <filesystem>
#include <iostream>
#include "../includes/Orca.hpp"
#include "../includes/Extern.hpp"

Orca::Orca(const sf::VideoMode &videoMode, const std::string &fontPath)
    : _quit(false)
{
    window.setSize(sf::Vector2u(videoMode.width, videoMode.height));
    windowSize = videoMode;
    minScreenSize = sf::VideoMode(800, 600);

    if (std::filesystem::exists(fontPath))
        font.loadFromFile(fontPath);
    static const int x_shift = 150;
    addElement(sf::IntRect(0, 0, x_shift, windowSize.height), sf::Color(40, 40, 40), "leftbar");
    addElement(sf::IntRect(x_shift, 0, windowSize.width - x_shift, 50), sf::Color(60, 60, 60), "topbar");
    sf::Vector2u selectionButtonSize(50, 25);
    addElement(sf::IntRect(windowSize.width - selectionButtonSize.x - 10,
                           windowSize.height - selectionButtonSize.y - 10,
                           selectionButtonSize.x,
                           selectionButtonSize.y), sf::Color(60, 60, 60), "selectionbutton");
    selectionButtonText = sf::Text();
    selectionButtonText.setFont(font);
    selectionButtonText.setString("OK");
    sf::Vector2f pos = elements["selectionbutton"].getPosition();
    selectionButtonText.setPosition(pos.x + 15, pos.y + 3);
    selectionButtonText.setCharacterSize(15);

    for (const auto & UIAsset : UIAssets) {
        sf::Texture texture;
        std::filesystem::path filename(UIAsset);
        texture.loadFromFile(UIAsset);
        assets[filename.stem().string()] = texture;
    }
}

void Orca::setVideoMode(const sf::VideoMode &mode)
{
    windowSize = mode;
}

void Orca::setFontPath(const std::string &fontPath)
{
    if (std::filesystem::exists(fontPath))
        font.loadFromFile(fontPath);
}
