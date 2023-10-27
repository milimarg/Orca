#include <filesystem>
#include <iostream>
#include "../includes/fileElement.hpp"

fileElement::fileElement(sf::Vector2f &pos, const sf::Color &color, std::string name, sf::Font &font)
{
    data.setString(name);
    data.setFont(font);
    data.setCharacterSize(15);
    data.setPosition(pos.x, pos.y);
    data.setFillColor(color);
    data.setOutlineColor(color);
    background.setPosition(data.getPosition());
    background.setSize(sf::Vector2f(650, 20)); // set constant values
    background.setOutlineColor(sf::Color::Blue); // set constant values
    background.setFillColor(sf::Color::Blue); // set constant values
}

void fileElement::setIcon(fileElement::Type _type, std::unordered_map <std::string, sf::Texture> &assets)
{
    type = _type;
    if (type == DIRECTORY) {
        icon = sf::Sprite(assets["directory"]);
    }
    if (type == REGULAR) {
        icon = sf::Sprite(assets["file"]);
    }
    icon.setPosition(data.getPosition().x - 30.0f, data.getPosition().y);
}

void fileElement::draw(sf::RenderWindow *window)
{
    if (clicked) {
        window->draw(background);
    }
    window->draw(icon);
    window->draw(data);
}

void fileElement::onClick(sf::RenderWindow *window)
{
    const bool state = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    sf::FloatRect rect(background.getPosition(), background.getSize()); // don't recreate a rect each time
    sf::Vector2f test((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y); // how to static_cast?
    clicked = state && rect.contains(test);
}
