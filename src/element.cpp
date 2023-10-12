#include "../includes/orca.hpp"

void Orca::addElement(const sf::IntRect rect, const sf::Color color)
{
    if (this->elementIndex == ELEMENTS_NUMBER) {
        std::cerr << "Orca: cannot add new element: array is full" << std::endl;
        return;
    }
    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));

    shape.setPosition(rect.left, rect.top);
    shape.setFillColor(color);
    shape.setOutlineColor(color);
    this->elements[this->elementIndex++] = shape;
}
