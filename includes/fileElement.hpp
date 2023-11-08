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
            bool onHover(sf::RenderWindow *window);
            sf::Text data;
            sf::RectangleShape background;
            int fileIndex;
        private:
            sf::Sprite icon;
            Type type;
    };

#endif //ORCA_FILEELEMENT_HPP
