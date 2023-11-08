#include <iostream>
#include "../includes/orca.hpp"

void Orca::checkIfAllowDisplay()
{
    static int allowDisplayHasChanged = 0;

    this->allowDisplay = this->windowSize.x >= this->minScreenSize.width &&
                         this->windowSize.y >= this->minScreenSize.height;
    if (!this->allowDisplay && !allowDisplayHasChanged) {
        allowDisplayHasChanged = 1;
        this->window->setTitle("Orca: window size too small (< 800x600)");
    }
    if (this->allowDisplay && allowDisplayHasChanged) {
        allowDisplayHasChanged = 0;
        this->window->setTitle("Orca");
    }
}

void Orca::runEvent(sf::Event &event, sf::RenderWindow *window)
{
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::Resized) {
            sf::Vector2u size = this->window->getSize();
            if (size.x != this->windowSize.x || size.y != this->windowSize.y) {
                this->windowSize = this->window->getSize();
            }
        }
    }
    checkIfAllowDisplay();
}
