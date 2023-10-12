#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "../includes/include.hpp"

void open_orca()
{
    sf::Event event;
    sf::VideoMode minScreen(800, 600);
    sf::VideoMode windowSize = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Orca");
    sf::RectangleShape sideBar(sf::Vector2f(150, window.getSize().y));
    sf::RectangleShape toolBar(sf::Vector2f(window.getSize().x - sideBar.getSize().x, 50));

    toolBar.setPosition(sideBar.getSize().x, 0);
    toolBar.setFillColor(sf::Color::Blue);
    toolBar.setOutlineColor(sf::Color::Blue);
    if (windowSize.width < minScreen.width || windowSize.height < minScreen.height) {

    }
    while (window.isOpen()) {
        window.clear();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.draw(sideBar);
        window.draw(toolBar);
        window.display();
    }
}
