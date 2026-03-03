#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Colors.h"
#include "Controller.h"
#include "Button.h"
#include <string>
#include <fstream>
#include <vector>

class Controller;

class BestGame {
private:
    sf::RenderWindow* window;
    sf::Font font;
    Button goToMenu;
public:
    BestGame(sf::RenderWindow* window);
    void initFont();

    void draw();

    void eventHandler(Controller &c);

    void exitBestGame(Controller &c);

    void initScore();

    std::pair<int, int> evaluateScore(std::vector<std::vector<char>> gridArray);

    void updateScore(int time, std::vector<std::vector<char>> gridArray);

    std::pair<std::vector<int>, std::vector<int>> getScore();

    std::string timeToStr(int seconds);
};


