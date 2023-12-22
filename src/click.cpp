#include <iostream>
#include <filesystem>
#include "../includes/orca.hpp"

void Orca::doubleClick(fileElement &file)
{
    static bool antiSpam = false;
    static int keyNumber = 0;
    static sf::Int32 last = 0;
    static int lastIndex = 0;
    sf::Int32 current = clock->getElapsedTime().asMilliseconds();
    int diff = current - last;

    if (file.getIndex() != lastIndex && keyNumber != 0) {
        keyNumber = 0;
        antiSpam = false;
    }
    if (diff > 50 && diff < 500 && !antiSpam && keyNumber < 2) {
        antiSpam = true;
        keyNumber++;
    }
    if (!(diff > 50 && diff < 500) && antiSpam) {
        antiSpam = false;
    }
    if (keyNumber >= 2) {
        keyNumber = 0;
        antiSpam = false;
        last = 0;
        std::filesystem::current_path(std::string(file.getText().getString()));
        getCurrentPath();
        readCurrentPath();
        selected.clear();
    }
    last = current;
    lastIndex = file.getIndex();
}

int Orca::onClick(fileElement &file)
{
    const bool click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    const bool maj = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    const bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);

    if (!file.onHover(window) && click) {
        return (1);
    }
    if (!(file.onHover(window) && click)) {
        return (0);
    }
    if (!maj && !ctrl) {
        selected.clear();
        selected.push_back(file);
        if (selected.size() == 1 && file.getType() == fileElement::Type::DIRECTORY)
            doubleClick(file);
    }
    if (ctrl) {
        selected.push_back(file);
    }
    if (maj) {
        fileElement &a = selected.size() > 0 ? selected.at(0) : files.at(0);
        int difference = a.getIndex() - file.getIndex();
        int differenceAbs = abs(difference);
        int differenceIsPos = difference >= 0;
        for (int i = (differenceIsPos ? -1 : 1); i < (differenceAbs + !differenceIsPos); i++) {
            selected.push_back(files.at(file.getIndex() + (differenceIsPos ? i : -i)));
        }
    }
    return (0);
}
