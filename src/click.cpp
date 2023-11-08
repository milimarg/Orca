#include <SFML/Config.hpp>
#include <iostream>
#include <filesystem>
#include "../includes/orca.hpp"

void Orca::doubleClick(fileElement &file)
{
    static bool antiSpam = false;
    static int keyNumber = 0;
    static sf::Int32 last = 0;
    static int lastFileIndex = 0;
    sf::Int32 current = clock->getElapsedTime().asMilliseconds();
    int diff = current - last;

    if (file.fileIndex != lastFileIndex && keyNumber != 0) {
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
        std::cout << "double-click! - " << current - last << std::endl;
        std::filesystem::current_path("..");
        getCurrentPath();
        readCurrentPath();
    }
    last = current;
    lastFileIndex = file.fileIndex;
}

void Orca::onClick(fileElement &file)
{
    const bool click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    const bool maj = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    const bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);

    if (file.onHover(window) && click) {
        if (!maj && !ctrl) {
            selected.clear();
            selected.push_back(file);
            doubleClick(file);
        }
        if (ctrl) {
            selected.push_back(file);
        }
        if (maj) {
            fileElement &a = selected.size() > 0 ? selected.at(0) : files.at(0); // test when size == 0
            int difference = a.fileIndex - file.fileIndex;
            int differenceAbs = abs(difference);
            int differenceIsPos = difference >= 0;
            for (int i = (differenceIsPos ? -1 : 1); i < (differenceAbs + !differenceIsPos); i++) {
                selected.push_back(files.at(file.fileIndex + (differenceIsPos ? i : -i)));
            }
        }

    }
}
