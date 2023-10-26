#ifndef ORCA_ORCA_HPP
    #define ORCA_ORCA_HPP
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #define UI_ELEMENTS_NUMBER 2
    #define FILE_CATEGORIES_NUMBER 2

typedef struct {
    sf::Text data;
    sf::Sprite icon;
} fileElement;

class Orca {
    public:
        Orca(const sf::VideoMode &videoMode, const std::string &fontName);
        ~Orca();
        void open();
    private:
        sf::RenderWindow *window;
        sf::Vector2u windowSize;
        sf::VideoMode minScreenSize;
        std::array<sf::RectangleShape, UI_ELEMENTS_NUMBER> elements;
        unsigned int elementIndex;
        int allowDisplay;
        std::string currentPath;
        std::vector<fileElement> files;
        sf::Font font;
        std::array<sf::Texture, FILE_CATEGORIES_NUMBER> categoriesIcon;
        void runEvent(sf::Event &event, sf::RenderWindow *window);
        void addElement(sf::IntRect rect, sf::Color color);
        void checkIfAllowDisplay();
        void getCurrentPath();
        void readCurrentPath();
};

#endif //ORCA_ORCA_HPP
