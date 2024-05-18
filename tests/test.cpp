#include <iostream>
#include "../includes/Orca.hpp"

int main(void)
{
    Orca orca;

    orca.setFontPath("./assets/fonts/Roboto-Regular.ttf");

    std::vector<FileElement> &result = orca.open();

    for (auto &element : result)
        std::cout << std::string(element.getString()) << std::endl;
    return 0;
}
