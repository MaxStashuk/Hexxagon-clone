#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Colors.h"

enum class PAWN {
    RED,
    BLUE,
    NONE,
    UNACTIVE
};

class Hex {
private:
    sf::CircleShape body;
    std::pair<int, int> coord;
    sf::Color outlineCol;
    PAWN pawn;
public:
    Hex();
    void draw(sf::RenderWindow *window);

    void setCoords(int x, int y);

    void setPawn(PAWN p);

    void setPosition(sf::Vector2f position);

    PAWN getPawn();

    sf::Vector2f coordsToPos();

    sf::Vector2f getPosition();

    sf::CircleShape drawPawn();

    bool isClickable(sf::Vector2i& mousePosition, bool toMove);

    void update(sf::Color c);

    void setDefaultOutline();

    sf::Vector3i offsetToCube(sf::Vector2i offset);

    int distance(Hex hex);

    std::pair<int, int> getCoords();

    bool isClickable(sf::Vector2i &mousePosition);
};
