#include <iostream>
#include "../includes/orca.hpp"

int main(void)
{
    Orca orca(sf::VideoMode(800, 600), "./assets/fonts/Roboto-Regular.ttf");

    std::vector<fileElement> result = orca.open();

    for (auto &element : result) {
        std::cout << std::string(element.getString()) << std::endl;
    }
    return 0;
}
