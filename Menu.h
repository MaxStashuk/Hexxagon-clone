#pragma once
#include "Controller.h"
#include "Button.h"

class Controller;


class Menu{
    sf::RenderWindow* window;
    sf::Font font;
    Button playVsFriend;
    Button loadGame;
    Button bestGame;
    Button exitMenu;

public:
    Menu(sf::RenderWindow* window, sf::Font font);

    void eventHandler(Controller& c);

    void draw();
};

