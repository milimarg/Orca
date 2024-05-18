#include <iostream>
#include "../includes/orca.hpp"

std::vector<fileElement> &Orca::open()
{
    sf::Event event;
    static int quit = 0;

    getCurrentPath();
    readCurrentPath();
    while (window->isOpen()) {
        window->clear();
        runEvent(event, window, quit);
        if (allowDisplay && !quit) {
            for (const auto &element : elements) {
                window->draw(element.second);
            }
            for (auto &selected : selected) {
                window->draw(selected._background);
            }
            int output = 1;
            for (auto &file : files) {
                int v = onClick(file);
                if (v == 2)
                    break;
                output = output && v;
                file.draw(window);
            }
            if (output == 1 && selected.size() > 0) {
                selected.clear();
            }
            window->draw(selectionButtonText);
        }
        window->display();
    }
    return selected;
}
