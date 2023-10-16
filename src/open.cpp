#include "../includes/orca.hpp"

void Orca::open()
{
    sf::Event event;

    getCurrentPath();
    readCurrentPath();
    std::cout << this->currentPath << std::endl;
    while (this->window->isOpen()) {
        this->window->clear();
        this->runEvent(event, this->window);
        if (this->allowDisplay) {
            for(const auto &element : this->elements) {
                this->window->draw(element);
            }
        }
        this->window->display();
    }
}
