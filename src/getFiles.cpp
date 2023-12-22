#include <filesystem>
#include <string>
#include <iostream>
#include <typeinfo>
#include "../includes/orca.hpp"

void Orca::getCurrentPath()
{
    currentPath = std::filesystem::current_path().string();
}

void Orca::appendFile(std::string filename,
                      std::string filepath,
                      fileElement::Type type,
                      int &index)
{
    sf::Vector2f pos = {
            elements["leftbar"].getSize().x + LEN_BETWEEN_LEFT_FILE_ICON,
            elements["topbar"].getSize().y + 10.0f + index * LEN_BETWEEN_FILES
    };

    fileElement file(pos, sf::Color::White, filename, filepath, font);
    file.setIcon(type, assets);
    file.setIndex(index);
    file.getText().setString(file.getText().getString());
    files.push_back(file);
    index++;
}

void Orca::readCurrentPath()
{
    int index = 0;
    fileElement::Type type;

    files.clear();
    type = fileElement::DIRECTORY;
    appendFile("..", currentPath, type, index);
    for (const auto &entry : std::filesystem::directory_iterator(currentPath)) {
        if (std::filesystem::is_regular_file(entry)) {
            type = fileElement::REGULAR;
        }
        if (std::filesystem::is_directory(entry)) {
            type = fileElement::DIRECTORY;
        }
        if (entry.path().filename().string().at(0) == '.') {
            continue;
        }
        appendFile(entry.path().filename().string(), entry.path().string(), type, index);
    }
}
