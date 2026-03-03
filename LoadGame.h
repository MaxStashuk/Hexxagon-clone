#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Controller.h"
#include "TextBox.h"
#include <fstream>

class Game;

class LoadGame {
private:
    sf::RenderWindow* window;
    sf::Font font;
    Button goToMenu;
    Button startGame;
    std::string input;
    TextBox textBox;
public:
    LoadGame(sf::RenderWindow* window);

    void initFont();

    void eventHandler(Controller &c, Game& game);

    void exitLoadGame(Controller &c);

    void draw();

    bool isSaveExists(std::string savePath);

    std::pair<bool, std::pair <int, std::vector<std::vector<char>>>> parseFile(std::string fileName);

    void constructGame(bool move, int clockTime, std::vector<std::vector <char>> state);
};



