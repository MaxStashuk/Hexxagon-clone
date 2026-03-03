#pragma once
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Button.h"
#include "Hex.h"
#include "HexGrid.h"
#include "Colors.h"
#include <chrono>
#include <thread>
#include "BestGame.h"
#include <fmt/ranges.h>
class Controller;
class BestGame;

class Game {
private:

    sf::RenderWindow* window;
    sf::Font font;
    HexGrid gameGrid;
    Button exitToMenu;
    bool toMove;
    sf::Clock clock;
    int clockTime;
    int baseTime;
    bool paused;
public:
    Game(sf::RenderWindow* window);

    void eventHandler(Controller& c, BestGame& bestGame);

    void draw();

    void exitGame(Controller &c, BestGame& bestGame);

    void nextMove();

    bool getMove();

    void initFont();

    void restart();

    std::string clockToStr();

    void gameover(std::string text, sf::Color c);

    bool isEnded();

    void setMove(bool& move);

    void setClock(int& time);

    void setState(std::vector<std::vector<char>>& state);

    void initButton();
};

