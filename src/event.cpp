#include "../includes/orca.hpp"

void Orca::checkIfAllowDisplay()
{
    static int allowDisplayHasChanged = 0;

    allowDisplay = windowSize.x >= minScreenSize.width &&
                   windowSize.y >= minScreenSize.height;
    if (!allowDisplay && !allowDisplayHasChanged) {
        allowDisplayHasChanged = 1;
        window->setTitle("Orca: window size too small (< 800x600)");
    }
    if (allowDisplay && allowDisplayHasChanged) {
        allowDisplayHasChanged = 0;
        window->setTitle("Orca");
    }
}

void Orca::runEvent(sf::Event &event, sf::RenderWindow *window, int &quit)
{
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || quit) {
            window->close();
        }
        if (event.type == sf::Event::Resized) {
            sf::Vector2u size = window->getSize();
            if (size.x != windowSize.x || size.y != windowSize.y) {
                windowSize = window->getSize();
            }
        }
    }
    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*window));
    if (elements["selectionbutton"].getGlobalBounds().contains(pos) &&
    sf::Mouse::isButtonPressed(sf::Mouse::Left) && selected.size() > 0) {
        quit = 1;
    }
    checkIfAllowDisplay();
}
