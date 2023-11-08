#include <iostream>
#include "../includes/orca.hpp"

void Orca::open()
{
    sf::Event event;

    getCurrentPath();
    readCurrentPath();
    while (this->window->isOpen()) {
        this->window->clear();
        this->runEvent(event, this->window);
        if (this->allowDisplay) {
            for (const auto &element : this->elements) {
                this->window->draw(element.second);
            }
            for (auto &selected : this->selected) {
                window->draw(selected.background);
            }
            for (auto &file : this->files) {
                onClick(file);
                file.draw(window);
            }
        }
        this->window->display();
    }
}
