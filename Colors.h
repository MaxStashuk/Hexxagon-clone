#pragma once
#include <SFML/Graphics.hpp>

class Colors {
public:
    //UI COLORS
    inline static const sf::Color Background = sf::Color(25, 21, 61);
    inline static const sf::Color ButtonBody = sf::Color(145, 1, 138);
    inline static const sf::Color SelectedButtonBody = sf::Color(145, 1, 138, 180);
    inline static const sf::Color Sign = sf::Color::White;
    inline static const sf::Color SelectedSign = sf::Color(255, 255, 255, 180);

    //HEX COLORS
    inline static const sf::Color HexBody = sf::Color(101, 7, 130);
    inline static const sf::Color HexOutline = sf::Color(255, 153, 211);

    //PAWN COLORS
    inline static const sf::Color BluePawn = sf::Color(0, 204, 255);
    inline static const sf::Color RedPawn = sf::Color(255, 102, 102);

};

