#include <filesystem>
#include <string>
#include "../includes/orca.hpp"

void Orca::getCurrentPath()
{
    this->currentPath = std::filesystem::current_path().string();
}

void Orca::readCurrentPath()
{
    int index = 0;

    this->files.clear();
    for (const auto &entry : std::filesystem::directory_iterator(this->currentPath)) {
        std::string filename = entry.path().filename().string();

        if (filename.at(0) != '.') {
            fileElement file;
            file.data.setString(filename);
            file.data.setFont(this->font);
            file.data.setCharacterSize(15);
            file.data.move(150.0f + 10.0f, 50.0f + 10.0f); // get values from ui elements lengths
            file.data.move(30.0f, index * 20.0f); // register constants
            if (std::filesystem::is_directory(entry)) {
                file.icon = sf::Sprite(this->categoriesIcon.at(0));
            }
            if (std::filesystem::is_regular_file(entry)) {
                file.icon = sf::Sprite(this->categoriesIcon.at(1));
            }
            file.icon.setScale(0.0625f, 0.0625); // register constants
            file.icon.setPosition(150.0f + 10.0f, 50.0f + 10.0f + index * 20.0f); // register constants
            this->files.push_back(file);
            index++;
        }
    }
}
