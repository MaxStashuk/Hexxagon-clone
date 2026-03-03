#pragma once
#include "Hex.h"

class Game;

class HexGrid {
private:

    Hex grid[9][9];
    std::pair<int, int> selectedHex;
    std::vector<std::pair<int,int>> oneDistance;
    std::vector<std::pair<int,int>> twoDistance;
public:
    HexGrid();
    HexGrid(std::vector<std::vector<char>> state);
    void setPos();

    void draw(sf::RenderWindow *window);

    void draw(sf::RenderWindow *window, sf::Font font);

    std::string tmp(int i, int j);

    void checkIfClicked(sf::Vector2i &mousePos, bool toMove);

    void select();

    void unselect();

    void moveHex(Hex selected, Hex moveTo);

    std::vector<std::vector<char>> gridToArray();

    void eatNeighbors(std::pair<int, int> hexCoords);

    bool isEatable(std::pair<int, int> hex, std::pair<int, int> direction);

    sf::Vector3i countPawns();

    std::vector<std::pair<int, int>> allPossibleMoves(std::pair<int, int> hex);

    void setPawn(std::pair<int, int> hex, PAWN p);
};

