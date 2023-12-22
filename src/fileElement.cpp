#include <iostream>
#include "../includes/fileElement.hpp"

fileElement::fileElement(sf::Vector2f &pos,
                         const sf::Color &color,
                         std::string name,
                         std::string _path,
                         sf::Font &font)
{
    path = _path;
    data.setString(name);
    data.setFont(font);
    data.setCharacterSize(15);
    data.setPosition(pos.x, pos.y);
    data.setFillColor(color);
    data.setOutlineColor(color);
    background.setPosition(data.getPosition());
    background.setSize(sf::Vector2f(650, 20));
    background.setOutlineColor(sf::Color::Blue);
    background.setFillColor(sf::Color::Blue);
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
    window->draw(icon);
    window->draw(data);
}

bool fileElement::onHover(sf::RenderWindow *window)
{
    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*window));
    sf::FloatRect rect(background.getPosition(), background.getSize());
    return rect.contains(pos);
}

fileElement::Type fileElement::getType()
{
    return type;
}

sf::Text &fileElement::getText()
{
    return data;
}

int fileElement::getIndex()
{
    return index;
}

void fileElement::setIndex(int index)
{
    if (index < 0) {
        std::cerr << "fileElement index out of range" << std::endl;
        return;
    }
    this->index = index;
}
