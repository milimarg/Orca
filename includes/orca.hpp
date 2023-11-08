#ifndef ORCA_ORCA_HPP
    #define ORCA_ORCA_HPP
    #include "fileElement.hpp"

    /* ELEMENTS NUMBER */
    #define UI_ELEMENTS_NUMBER 2
    #define FILE_CATEGORIES_NUMBER 2

    /* LENGTHS */
    #define LEN_BETWEEN_FILES 25 // in pixels
    #define LEN_BETWEEN_LEFT_FILE_ICON 40 // in pixels

    const std::string UIAssets[FILE_CATEGORIES_NUMBER] = {
            "./assets/images/directory.png",
            "./assets/images/file.png"
    };

    class Orca {
        public:
            Orca(const sf::VideoMode &videoMode, const std::string &fontName);
            ~Orca();
            void open();
        private:
            sf::RenderWindow *window;
            sf::Clock *clock;
            sf::Vector2u windowSize;
            sf::VideoMode minScreenSize;
            std::unordered_map<std::string, sf::RectangleShape> elements;
            int allowDisplay;
            std::string currentPath;
            std::vector<fileElement> files;
            sf::Font font;
            std::unordered_map<std::string, sf::Texture> assets;
            std::vector<fileElement> selected;
            void runEvent(sf::Event &event, sf::RenderWindow *window);
            void addElement(sf::IntRect rect, sf::Color color, std::string name);
            void checkIfAllowDisplay();
            // path
            void getCurrentPath();
            void readCurrentPath();
            // click
            void onClick(fileElement &element);
            void doubleClick(fileElement &element);
    };

#endif //ORCA_ORCA_HPP
