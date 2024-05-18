#include <iostream>
#include "../includes/FileElement.hpp"

FileElement::FileElement(sf::Vector2f &pos,
                         const sf::Color &color,
                         const std::string &name,
                         const std::string &path,
                         const sf::Font &font)
    : _path(path)
{
    _data.setString(name);
    _data.setFont(font);
    _data.setCharacterSize(15);
    _data.setPosition(pos.x, pos.y);
    _data.setFillColor(color);
    _data.setOutlineColor(color);
    _background.setPosition(_data.getPosition());
    _background.setSize(sf::Vector2f(650, 20));
    _background.setOutlineColor(sf::Color::Blue);
    _background.setFillColor(sf::Color::Blue);
}

void FileElement::setIcon(FileElement::Type type, std::unordered_map <std::string, sf::Texture> &assets)
{
    _type = type;
    if (type == Type::DIRECTORY)
        _icon = sf::Sprite(assets["directory"]);
    if (type == Type::REGULAR)
        _icon = sf::Sprite(assets["file"]);
    _icon.setPosition(_data.getPosition().x - 30.0f, _data.getPosition().y);
}

void FileElement::draw(sf::RenderWindow &window)
{
    window.draw(_icon);
    window.draw(_data);
}

bool FileElement::onHover(sf::RenderWindow &window) const
{
    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
    sf::FloatRect rect(_background.getPosition(), _background.getSize());
    return rect.contains(pos);
}

FileElement::Type FileElement::getType() const
{
    return _type;
}

std::string FileElement::getString() const
{
    return _data.getString();
}

void FileElement::setString(const std::string &name)
{
    _data.setString(name);
}

int FileElement::getIndex() const
{
    return _index;
}

void FileElement::setIndex(int index)
{
    if (index < 0) {
        std::cerr << "FileElement index out of range" << std::endl;
        return;
    }
    _index = index;
}

bool FileElement::operator==(const FileElement &other)
{
    return _type == other.getType() &&
           _data.getString() == other.getString() &&
           _index == other.getIndex();
}
