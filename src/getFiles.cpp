#include <filesystem>
#include <string>
#include <iostream>
#include "../includes/orca.hpp"

void Orca::getCurrentPath()
{
    currentPath = std::filesystem::current_path().string();
}

void Orca::appendFile(std::string &filename, fileElement::Type type, int &index)
{
    sf::Vector2f pos = {
            elements["leftbar"].getSize().x + LEN_BETWEEN_LEFT_FILE_ICON,
            elements["topbar"].getSize().y + 10.0f + index * LEN_BETWEEN_FILES
    };

    fileElement file(pos, sf::Color::White, filename, font);
    file.setIcon(type, assets);
    file.index = index;
    file.data.setString(file.data.getString());
    files.push_back(file);
    index++;
}

void Orca::readCurrentPath()
{
    int index = 0;
    fileElement::Type type;
    std::string filename;

    files.clear();
    type = fileElement::DIRECTORY;
    filename = std::string("..");
    appendFile(filename, type, index);
    for (const auto &entry : std::filesystem::directory_iterator(currentPath)) {
        filename = entry.path().filename().string();
        if (std::filesystem::is_regular_file(entry)) {
            type = fileElement::REGULAR;
        }
        if (std::filesystem::is_directory(entry)) {
            type = fileElement::DIRECTORY;
        }
        if (filename.at(0) == '.') {
            continue;
        }
        appendFile(filename, type, index);
    }
}
