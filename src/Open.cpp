#include <iostream>
#include "../includes/Orca.hpp"

std::vector<FileElement> &Orca::open()
{
    sf::Event event{};

    window.create(windowSize, "Orca");
    getCurrentPath();
    readCurrentPath();
    while (window.isOpen()) {
        window.clear();
        runEvent(event);
        if (allowDisplay && !_quit) {
            for (const auto &element : elements)
                window.draw(element.second);
            for (auto &selectedChild : selected)
                window.draw(selectedChild._background);
            int output = 1;
            for (auto &file : files) {
                int v = onClick(file);
                if (v == 2)
                    break;
                output = output && v;
                file.draw(window);
            }
            if (output == 1 && !selected.empty()) {
                selected.clear();
            }
            window.draw(selectionButtonText);
        }
        window.display();
    }
    return selected;
}
