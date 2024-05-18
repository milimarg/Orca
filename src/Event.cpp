#include "../includes/Orca.hpp"

void Orca::checkIfAllowDisplay()
{
    static int allowDisplayHasChanged = 0;

    allowDisplay = windowSize.width >= minScreenSize.width &&
                   windowSize.height >= minScreenSize.height;
    if (!allowDisplay && !allowDisplayHasChanged) {
        allowDisplayHasChanged = 1;
        window.setTitle("Orca: window size too small (< 800x600)");
    }
    if (allowDisplay && allowDisplayHasChanged) {
        allowDisplayHasChanged = 0;
        window.setTitle("Orca");
    }
}

void Orca::runEvent(sf::Event &event)
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || _quit)
            window.close();
        if (event.type == sf::Event::Resized) {
            sf::Vector2u size = window.getSize();
            if (size.x != windowSize.width || size.y != windowSize.height) {
                windowSize.width = window.getSize().x;
                windowSize.height = window.getSize().y;
            }
        }
    }
    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
    if (elements["selectionbutton"].getGlobalBounds().contains(pos) &&
    sf::Mouse::isButtonPressed(sf::Mouse::Left) && !selected.empty())
        _quit = true;
    checkIfAllowDisplay();
}
