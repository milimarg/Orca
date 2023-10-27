#include <filesystem>
#include "../includes/orca.hpp"

Orca::Orca(const sf::VideoMode &videoMode, const std::string &fontName)
{
    window = new sf::RenderWindow(videoMode, "Orca");
    windowSize = window->getSize();
    minScreenSize = sf::VideoMode(800, 600);
    font.loadFromFile(fontName);
    static const int x_shift = 150;
    addElement(sf::IntRect(0, 0, x_shift, windowSize.y), sf::Color(40, 40, 40), "leftbar");
    addElement(sf::IntRect(x_shift, 0, windowSize.x - x_shift, 50), sf::Color(60, 60, 60), "topbar");

    for (int i = 0; i < FILE_CATEGORIES_NUMBER; i++) {
        sf::Texture texture;
        std::filesystem::path filename(UIAssets[i]);
        texture.loadFromFile(UIAssets[i]);
        assets[filename.stem().string()] = texture;
    }
}

Orca::~Orca()
{
    delete this->window;
}
