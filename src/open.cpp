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
            for(const auto &element : this->elements) {
                this->window->draw(element);
            }
            for(const auto &file : this->files) {
                this->window->draw(file.data);
                this->window->draw(file.icon);
            }
        }
        this->window->display();
    }
}
