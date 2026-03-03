#pragma once
#include <SFML/Graphics.hpp>
#include "Colors.h"
#include <string>

class TextBox {
private:
    sf::RectangleShape body;
    sf::Text text;
public:
    TextBox();
    TextBox(sf::Vector2f bodySize, sf::Vector2f pos, std::string input, sf::Font& font, int chSize);
    void draw(sf::RenderWindow* window);

    void setString(std::string str);

    std::string getString();
};

