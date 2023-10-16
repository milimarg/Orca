#include <filesystem>
#include <string>
#include <iostream>
#include <unistd.h>
#include "../includes/orca.hpp"

void Orca::getCurrentPath()
{
    std::filesystem::path name = std::filesystem::current_path();


}

void Orca::readCurrentPath()
{
    for (const auto &entry : std::filesystem::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}
