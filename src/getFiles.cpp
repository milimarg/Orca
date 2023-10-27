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
    for (const auto &entry : std::filesystem::directory_iterator(currentPath)) {
        std::string filename = entry.path().filename().string();

        if (filename.at(0) != '.') {
            sf::Vector2f pos = {
                elements["leftbar"].getSize().x + LEN_BETWEEN_LEFT_FILE_ICON,
                elements["topbar"].getSize().y + 10.0f + index++ * LEN_BETWEEN_FILES
            };
            fileElement::Type type;
            if (std::filesystem::is_regular_file(entry)) {
                type = fileElement::REGULAR;
            }
            if (std::filesystem::is_directory(entry)) {
                type = fileElement::DIRECTORY;
            }
            fileElement file(pos, sf::Color::White, filename, font);
            file.setIcon(type, assets);
            files.push_back(file);
        }
    }
}
