#ifndef ORCA_ORCA_HPP
    #define ORCA_ORCA_HPP
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>
    #define ELEMENTS_NUMBER 2

class Orca {
    public:
        Orca(const sf::VideoMode &videoMode = sf::VideoMode(800, 600));
        ~Orca();
        void open();
    private:
        sf::RenderWindow *window;
        sf::Vector2u windowSize;
        sf::VideoMode minScreenSize;
        std::array<sf::RectangleShape, 2> elements;
        unsigned int elementIndex;
        int allowDisplay;
        void runEvent(sf::Event &event, sf::RenderWindow *window);
        void addElement(sf::IntRect rect, sf::Color color);
        void checkIfAllowDisplay();
};

#endif //ORCA_ORCA_HPP
