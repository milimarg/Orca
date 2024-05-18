#include <filesystem>
#include <iostream>
#include "../includes/Orca.hpp"

Orca::Orca(const sf::VideoMode &videoMode, const std::string &fontPath)
    : _quit(false)
{
    window.setSize(sf::Vector2u(videoMode.width, videoMode.height));
    windowSize = videoMode;
    minScreenSize = sf::VideoMode(800, 600);

    if (std::filesystem::exists(fontPath))
        font.loadFromFile(fontPath);
    static const int x_shift = 150;
    addElement(sf::IntRect(0, 0, x_shift, windowSize.height), sf::Color(40, 40, 40), "leftbar");
    addElement(sf::IntRect(x_shift, 0, windowSize.width - x_shift, 50), sf::Color(60, 60, 60), "topbar");
    sf::Vector2u selectionButtonSize(50, 25);
    addElement(sf::IntRect(windowSize.width - selectionButtonSize.x - 10,
                           windowSize.height - selectionButtonSize.y - 10,
                           selectionButtonSize.x,
                           selectionButtonSize.y), sf::Color(60, 60, 60), "selectionbutton");
    selectionButtonText.setFont(font);
    selectionButtonText.setString("OK");
    sf::Vector2f pos = elements["selectionbutton"].getPosition();
    selectionButtonText.setPosition(pos.x + 15, pos.y + 3);
    selectionButtonText.setCharacterSize(15);

    for (const auto & UIAsset : UIAssets) {
        sf::Texture texture;
        std::filesystem::path filename(UIAsset);
        texture.loadFromFile(UIAsset);
        assets[filename.stem().string()] = texture;
    }
}

std::vector<FileElement> &Orca::open()
{
    sf::Event event{};

    window.create(windowSize, "Orca");
    getCurrentPath();
    readCurrentPath();
    while (window.isOpen()) {
        window.clear();
        runEvent(event);
        if (allowDisplay && !_quit) {
            for (const auto &element : elements)
                window.draw(element.second);
            for (auto &selectedChild : selected)
                window.draw(selectedChild._background);
            int output = 1;
            for (auto &file : files) {
                int v = onClick(file);
                if (v == 2)
                    break;
                output = output && v;
                file.draw(window);
            }
            if (output == 1 && !selected.empty()) {
                selected.clear();
            }
            window.draw(selectionButtonText);
        }
        window.display();
    }
    return selected;
}


void Orca::checkIfAllowDisplay()
{
    static int allowDisplayHasChanged = 0;

    allowDisplay = windowSize.width >= minScreenSize.width &&
                   windowSize.height >= minScreenSize.height;
    if (!allowDisplay && !allowDisplayHasChanged) {
        allowDisplayHasChanged = 1;
        window.setTitle("Orca: window size too small (< 800x600)");
    }
    if (allowDisplay && allowDisplayHasChanged) {
        allowDisplayHasChanged = 0;
        window.setTitle("Orca");
    }
}

void Orca::runEvent(sf::Event &event)
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || _quit)
            window.close();
        if (event.type == sf::Event::Resized) {
            sf::Vector2u size = window.getSize();
            if (size.x != windowSize.width || size.y != windowSize.height) {
                windowSize.width = window.getSize().x;
                windowSize.height = window.getSize().y;
            }
        }
    }
    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window));
    if (((elements["selectionbutton"].getGlobalBounds().contains(pos) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) &&
        !selected.empty())
        _quit = true;
    checkIfAllowDisplay();
}

bool Orca::doubleClick(const FileElement &file)
{
    static bool antiSpam = false;
    static int keyNumber = 0;
    static sf::Int32 last = 0;
    static int lastIndex = 0;
    sf::Int32 current = clock.getElapsedTime().asMilliseconds();
    int diff = current - last;

    if (file.getIndex() != lastIndex && keyNumber != 0) {
        keyNumber = 0;
        antiSpam = false;
    }
    if (diff > 50 && diff < 500 && !antiSpam && keyNumber < 2) {
        antiSpam = true;
        keyNumber++;
    }
    if (!(diff > 50 && diff < 500) && antiSpam)
        antiSpam = false;
    if (keyNumber >= 1) {
        keyNumber = 0;
        antiSpam = false;
        last = 0;
        std::filesystem::current_path(std::string(file.getString()));
        getCurrentPath();
        readCurrentPath();
        selected.clear();
        return true;
    }
    last = current;
    lastIndex = file.getIndex();
    return false;
}

int Orca::onClick(const FileElement &file)
{
    const bool click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    const bool maj = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    const bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);

    if (!file.onHover(window) && click)
        return 1;
    if (!(file.onHover(window) && click))
        return 0;
    if (!maj && !ctrl) {
        selected.clear();
        selected.push_back(file);
        if (selected.size() == 1 && file.getType() == FileElement::Type::DIRECTORY)
            if (doubleClick(file))
                return 2;
        return 0;
    }
    if (ctrl) {
        if (std::find(selected.begin(), selected.end(), file) != selected.end())
            return 0;
        selected.push_back(file);
        return 0;
    }
    // maj
    const FileElement &a = !selected.empty() ? selected.at(0) : files.at(0);
    int difference = a.getIndex() - file.getIndex();
    int differenceAbs = abs(difference);
    int differenceIsPos = difference >= 0;
    for (int i = (differenceIsPos ? -1 : 1); i < (differenceAbs + !differenceIsPos); i++)
        selected.push_back(files.at(file.getIndex() + (differenceIsPos ? i : -i)));
    return 0;
}

void Orca::setVideoMode(const sf::VideoMode &mode)
{
    windowSize = mode;
}

void Orca::setFontPath(const std::string &fontPath)
{
    if (std::filesystem::exists(fontPath))
        font.loadFromFile(fontPath);
}


void Orca::getCurrentPath()
{
    currentPath = std::filesystem::current_path().string();
}

void Orca::appendFile(std::string filename,
                      std::string filepath,
                      FileElement::Type type,
                      int &index)
{
    sf::Vector2f pos = {
            elements["leftbar"].getSize().x + LEN_BETWEEN_LEFT_FILE_ICON,
            elements["topbar"].getSize().y + 10.0f + index * LEN_BETWEEN_FILES
    };

    FileElement file(pos, sf::Color::White, filename, filepath, font);
    file.setIcon(type, assets);
    file.setIndex(index);
    file.setString(file.getString());
    files.push_back(file);
    index++;
}

void Orca::readCurrentPath()
{
    int index = 0;
    FileElement::Type type;

    files.clear();
    type = FileElement::Type::DIRECTORY;
    appendFile("..", currentPath, type, index);
    for (const auto &entry : std::filesystem::directory_iterator(currentPath)) {
        if (std::filesystem::is_regular_file(entry)) {
            type = FileElement::Type::REGULAR;
        }
        if (std::filesystem::is_directory(entry)) {
            type = FileElement::Type::DIRECTORY;
        }
        if (entry.path().filename().string().at(0) == '.') {
            continue;
        }
        appendFile(entry.path().filename().string(), entry.path().string(), type, index);
    }
}

void Orca::addElement(sf::IntRect rect, sf::Color color, std::string name)
{
    if (elements.size() == UI_ELEMENTS_NUMBER) {
        std::cerr << "Orca: cannot add new element: array is full" << std::endl;
        return;
    }
    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));

    shape.setPosition(rect.left, rect.top);
    shape.setFillColor(color);
    shape.setOutlineColor(color);
    elements[name] = shape;
}
