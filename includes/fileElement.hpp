#ifndef ORCA_FILEELEMENT_HPP
    #define ORCA_FILEELEMENT_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>

    class fileElement {
        public:
            enum Type {
                REGULAR,
                DIRECTORY
            };
            fileElement(sf::Vector2f &pos, const sf::Color &color, std::string name, sf::Font &font);
            void setIcon(fileElement::Type _type, std::unordered_map<std::string, sf::Texture> &assets);
            void draw(sf::RenderWindow *window);
            void onClick(sf::RenderWindow *window);
        private:
            sf::Text data;
            sf::Sprite icon;
            Type type;
            sf::RectangleShape background;
            bool clicked;
    };

#endif //ORCA_FILEELEMENT_HPP
