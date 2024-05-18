#ifndef ORCA_ORCA_HPP
    #define ORCA_ORCA_HPP
    #include "FileElement.hpp"

    /* ELEMENTS NUMBER */
    #define UI_ELEMENTS_NUMBER 3
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
            Orca(const sf::VideoMode &videoMode, const std::string &fontPath);
            ~Orca() = default;
            std::vector<FileElement> &open();
        private:
            sf::RenderWindow window;
            sf::Clock clock;
            sf::VideoMode windowSize;
            sf::VideoMode minScreenSize;
            std::unordered_map<std::string, sf::RectangleShape> elements;
            int allowDisplay = 1;
            std::string currentPath;
            std::vector<FileElement> files;
            sf::Font font;
            std::unordered_map<std::string, sf::Texture> assets;
            std::vector<FileElement> selected;
            sf::Text selectionButtonText;
            bool _quit;

            void runEvent(sf::Event &event);
            void addElement(sf::IntRect rect, sf::Color color, std::string name);
            void checkIfAllowDisplay();
            // path
            void getCurrentPath();
            void readCurrentPath();
            void appendFile(std::string filename, std::string filepath, FileElement::Type type, int &index);
            // click
            int onClick(const FileElement &element);
            bool doubleClick(const FileElement &element);
    };

#endif //ORCA_ORCA_HPP
