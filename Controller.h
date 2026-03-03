#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Game.h"
#include "Menu.h"
#include "BestGame.h"
#include "LoadGame.h"

enum class STATE {
    MENU,
    GAME_VS_BOT,
    GAME_VS_FRIEND,
    LOAD_GAME,
    BEST_GAME
};

class Controller {
private:
    sf::RenderWindow* window;
    sf::Font font;
    STATE state;
public:
    Controller();
    void initWindow();
    void initFont();
    virtual void run();
    void setState(STATE s);
};
