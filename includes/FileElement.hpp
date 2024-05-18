#ifndef ORCA_FILEELEMENT_HPP
    #define ORCA_FILEELEMENT_HPP
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>

    class FileElement {
        public:

        enum class Type {
                REGULAR,
                DIRECTORY
            };
            FileElement(sf::Vector2f &pos,
                        const sf::Color &color,
                        const std::string &name,
                        const std::string &path,
                        const sf::Font &font);
            void setIcon(FileElement::Type _type, std::unordered_map<std::string, sf::Texture> &assets);
            void draw(sf::RenderWindow &window);
            bool onHover(sf::RenderWindow &window) const;
            FileElement::Type getType() const;
            std::string getString() const;
            void setString(const std::string &name);
            int getIndex() const;
            void setIndex(int index);
            sf::RectangleShape _background;

            bool operator==(const FileElement &other);
        private:
            sf::Sprite _icon;
            Type _type;
            sf::Text _data;
            int _index;
            const std::string &_path;
    };

#endif //ORCA_FILEELEMENT_HPP
