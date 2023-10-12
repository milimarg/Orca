#include "../includes/orca.hpp"

Orca::Orca(const sf::VideoMode &videoMode)
{
    this->window = new sf::RenderWindow(videoMode, "Orca");
    this->windowSize = this->window->getSize();
    this->minScreenSize = sf::VideoMode(800, 600);
    this->elementIndex = 0;
    int x_shift = 150;
    this->addElement(sf::IntRect(0, 0, x_shift, this->window->getSize().y),
    sf::Color(40, 40, 40));
    this->addElement(sf::IntRect(x_shift, 0, this->window->getSize().x - x_shift, 50),
    sf::Color(60, 60, 60));
}

Orca::~Orca()
{
    delete this->window;
}
