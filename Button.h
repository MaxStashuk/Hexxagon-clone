#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Colors.h"
#include <iostream>

class Button {
private:
    sf::RectangleShape body;

    sf::Text text;
public:
    Button();
    Button(sf::Vector2f bodySize, sf::Vector2f position,
           sf::Font& font, const std::string& text, int charSize);
    Button(sf::Vector2f bodySize, sf::Vector2f position, const std::string &text, int charSize);

    void draw(sf::RenderWindow *window);

    bool isClickable(const sf::Vector2i &mousePosition);
};
