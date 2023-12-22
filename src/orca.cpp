#include <filesystem>
#include "../includes/orca.hpp"

Orca::Orca(const sf::VideoMode &videoMode, const std::string &fontPath)
{
    window = new sf::RenderWindow(videoMode, "Orca");
    windowSize = window->getSize();
    minScreenSize = sf::VideoMode(800, 600);
    clock = new sf::Clock();
    font.loadFromFile(fontPath);
    static const int x_shift = 150;
    addElement(sf::IntRect(0, 0, x_shift, windowSize.y), sf::Color(40, 40, 40), "leftbar");
    addElement(sf::IntRect(x_shift, 0, windowSize.x - x_shift, 50), sf::Color(60, 60, 60), "topbar");
    sf::Vector2u selectionButtonSize(50, 25);
    addElement(sf::IntRect(windowSize.x - selectionButtonSize.x - 10,
                           windowSize.y - selectionButtonSize.y - 10,
                           selectionButtonSize.x,
                           selectionButtonSize.y), sf::Color(60, 60, 60), "selectionbutton");
    selectionButtonText = sf::Text();
    selectionButtonText.setFont(font);
    selectionButtonText.setString("OK");
    sf::Vector2f pos = elements["selectionbutton"].getPosition();
    selectionButtonText.setPosition(pos.x + 15, pos.y + 3);
    selectionButtonText.setCharacterSize(15);

    for (int i = 0; i < FILE_CATEGORIES_NUMBER; i++) {
        sf::Texture texture;
        std::filesystem::path filename(UIAssets[i]);
        texture.loadFromFile(UIAssets[i]);
        assets[filename.stem().string()] = texture;
    }
}

Orca::~Orca()
{
    delete window;
    delete clock;
}
