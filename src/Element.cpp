#include <iostream>
#include "../includes/Orca.hpp"

void Orca::addElement(sf::IntRect rect, sf::Color color, std::string name)
{
    if (elements.size() == UI_ELEMENTS_NUMBER) {
        std::cerr << "Orca: cannot add new element: array is full" << std::endl;
        return;
    }
    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));

    shape.setPosition(rect.left, rect.top);
    shape.setFillColor(color);
    shape.setOutlineColor(color);
    elements[name] = shape;
}
